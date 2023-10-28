#include"pch.h"
#include"RG.h"
using namespace std;


void RG::SetH(double H)
{
	h = H;
}




vector<double> RG::MakeStartVals()
{
	vector<double>res;
	int size = round(L / h) + 1;
	for (int i = 0; i < size; i++)
	{
		double temp = i * h;
		res.push_back(-psy0 * temp / L + psy0);
	}
	valsOut.resize(size);
	valsY.resize(size);
	keys.resize(size);
	a.resize(size);
	b.resize(size);
	m_size = size;
	return res;
}
double RG::diff(vector<double>& left, vector<double>&right)
{
	double res = 0;
	for (int i = 0; i < left.size(); i++)
	{
		res += (left[i] - right[i]) * (left[i] - right[i]);
	}
	return sqrt(res / left.size());
}


void RG::test1()
{
	if (h < 0)h = -h;
	e_iter = 1;
	a[0] = 0;
	b[0] = psy0;
	while (e_iter < m_size)
	{
		EulerForward();
	}
}
void RG::test2()
{
	x = L;
	y = 0;
	counter = e_iter - 2;
	y_ = -b[m_size - 1] / a[m_size - 1];

	keys[m_size - 1] = x * Ld;
	valsY[m_size - 1] = y_;
	valsOut[m_size - 1] = 0;

	while (counter > 0)
	{
		EulerBackward();
	}
	for (int i = 0; i < m_size; i++)valsOut[i] = a[i] * valsY[i] + b[i];

	double differance = diff(valsOut, prevVals);
	if (differance < 1e-8)stop = true;;
	prevVals = valsOut;
	
	if (isnan(differance))
	{
		MessageBox(parent, L"NAN has been lockated", L"ERROR", MB_ICONERROR);
		stop = true;
	}
}

double RG::F(double f_y)
{
	return -na * (1.0 - exp(f_y));
}

double RG::q(double f_y)
{
	return -na * exp(f_y);
}

double RG::r(double f_y)
{
	return  F(f_y) + q(f_y) * f_y;
}

void RG::EulerForward()
{
	b[e_iter] = b[e_iter - 1] + h * (a[e_iter - 1] * b[e_iter - 1] * q(prevVals[e_iter - 1]) - e_alpha * r(prevVals[e_iter - 1]));
	a[e_iter] = a[e_iter - 1] + h * (a[e_iter - 1] * a[e_iter - 1] * q(prevVals[e_iter - 1]) + 1);
	e_iter++;
}
void RG::EulerBackward()
{
	double cy = y;
	y -= y_ * h;
	valsY[counter] = valsY[counter + 1] - (r(prevVals[counter + 1]) - q(prevVals[counter + 1]) * (a[counter + 1] * valsY[counter + 1] + b[counter + 1])) * h;
	x -= h;

	keys[counter] = x * Ld;
	counter--;

}


