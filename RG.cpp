#include"pch.h"
#include"RG.h"
using namespace std;

void RG::SetXYZ(double X, double Y, double Z)
{
	x = X;
	y = Y;
	z = Z;

	

	

}
double RG::GetX()
{
	return x;
}
double RG::GetY()
{
	return y;
}
double RG::GetZ()
{
	return z;
}

void RG::SetH(double H)
{
	h = H;
}

void RG::reset()
{
	keys.clear();
	valsY.clear();
	counter = 0;
}
int RG::ChangeDirection()
{
	h = -h;
	return (h > 0) ? 1 : -1;
}

// за альфа выступает Y, за бетта Z
double RG::f(double X, double Y, double Z)
{
	int temp = X / h;
	double val = 0;
	if (fabs(X - h * temp) > 0.25 * h) val = (prevVals[temp] + prevVals[temp + 1]) / 2.;
	else val = prevVals[temp];
	return -Y * Y - na * val * exp(val);
}
double RG::g(double X, double Y, double Z)
{
	int temp = X / h;
	double val = 0;
	if (fabs(X - h * temp) > 0.25 * h) val = (prevVals[temp] + prevVals[temp + 1]) / 2.;
	else val = prevVals[temp];
	return -Y * Z - na * (1 - exp(val)) + na * val * val * exp(val);
}
void RG::DoRGStepForward()
{
	if (h < 0)h = -h;
	double cx = x;
	double cy = y;
	double cz = z;


	double k1 = f(cx, cy, cz);
	double q1 = g(cx, cy, cz);

	double k2 = f(cx + h / 2., cy + h * k1 / 2., cz + h * q1 / 2.);
	double q2 = g(cx + h / 2., cy + h * k1 / 2., cz + h * q1 / 2.);

	double k3 = f(cx + h / 2., cy + h * k2 / 2., cz + h * q2 / 2.);
	double q3 = g(cx + h / 2., cy + h * k2 / 2., cz + h * q2 / 2.);

	double k4 = f(cx + h, cy + h * k3, cz + h * q3);
	double q4 = g(cx + h, cy + h * k3, cz + h * q3);


	y = cy + (k1 + 2 * k2 + 2 * k3 + k4) * h / 6.;
	z = cz + (q1 + 2 * q2 + 2 * q3 + q4) * h / 6.;

	counter++;
	x = counter * h;

	keys.push_back(x);
}

double RG::z__(double X, double Y, double DY)
{
	//double res = 0;
	/*res += Y * (-na * prevVals[counter] * (1 + prevVals[counter]));
	res += -na * (1 - (1 + prevVals[counter]));
	res+= na * prevVals[counter] * prevVals[counter] * (1 + prevVals[counter]);*/
	int temp = -X / h;
	double vala = 0;
	double valb = 0;
	if (fabs(X + h * temp) > -0.25 * h)
	{
		vala = (alpha[temp] + alpha[temp + 1]) / 2.;
		valb = (betta[temp] + betta[temp + 1]) / 2.;
	}
	else
	{
		vala = alpha[temp];
		valb = betta[temp];
	}

	return  vala * Y + valb;
}
double RG::y_z(double Z)
{
	return Z;
}
void RG::DoRGStepBack()
{
	if (h > 0)h = -h;
	double cx = x;
	double cy = y;
	double cz = z;


	double k1 = y_z(cz);
	double q1 = z__(cx, cy, cz);

	double k2 = y_z(cz + h * q1 / 2.);
	double q2 = z__(cx + h / 2., cy + h * k1 / 2., cz + h * q1 / 2.);

	double k3 = y_z(cz + h * q2 / 2.);
	double q3 = z__(cx + h / 2., cy + h * k2 / 2., cz + h * q2 / 2.);

	double k4 = y_z(cz + h * q3);
	double q4 = z__(cx + h, cy + h * k3, cz + h * q3);


	y = cy - (k1 + 2 * k2 + 2 * k3 + k4) * h / 6.;
	z = cz - (q1 + 2 * q2 + 2 * q3 + q4) * h / 6.;
	
	counter--;
	x = -counter * h;

	keys.push_back(x);
	valsY.push_back(y);
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
void RG::DoMainJob()
{
		
	
}


void RG::test1()
{
	if (h < 0)h = -h;
	e_iter = 0;
	e_alpha = 0;
	e_betta = psy0;
	x = 0;
	while (x < L)
	{
		EulerForward();
	}
}
void RG::test2()
{
	x = L;
	y = 0;
	counter = e_iter - 1;
	h = -h;
	y_ = -e_betta / e_alpha;
	z = y_;
	keys.clear();
	valsY.clear();
	valsOut.clear();

	valsOut.push_back(y * fi0);
	keys.push_back(x * Ld);
	valsY.push_back(y);
	while (counter > 0)
	{
		EulerBackward();
	}
	double differance = diff(valsY, prevVals);
	if (differance < 1e-8)stop = true;;
	prevVals = valsY;
	
	if (isnan(differance))
	{
		MessageBox(parent, L"NAN has been lockated", L"ERROR", MB_ICONERROR);
		stop = true;
	}
}


void RG::EulerForward()
{
	e_betta += EulerF(x, e_alpha, e_iter) * h;
	e_alpha += h;
	x += h;
	e_iter++;
}
double RG::EulerF(double x, double f_alpha, int i)
{
	return -f_alpha * (-na + na * exp(prevVals[i]) - na * prevVals[i] * exp(prevVals[i]));
}

double RG::EulerBZ(double x, double f_y, double f_z, int i)
{
	return na * f_y * exp(prevVals[i]) - na + na * exp(prevVals[i]) - na * prevVals[i] * exp(prevVals[i]) / f_z;
}
void RG::EulerBackward()
{
	/*double cy = y;
	y += y_ * h;
	y_ += EulerB(x, cy, counter) * h;*/
	double cy = y;
	double cz = z;

	y += cz * h;
	z += EulerBZ(x, cy, cz, counter) * h;


	x += h;
	counter--;

	valsOut.insert(valsOut.begin(), y * fi0);
	valsY.insert(valsY.begin(), y);
	keys.insert(keys.begin(), x * Ld);
}
double RG::EulerB(double x, double f_y, int i)
{
	return na * f_y * exp(prevVals[i]) - na + na * exp(prevVals[i]) - na * prevVals[i] * exp(prevVals[i]);
}


/*
y' = z(y)
y'' = z'(y)*z(y)


*/