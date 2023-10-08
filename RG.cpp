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
	valsZ.clear();
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
	alpha.push_back(y);
	betta.push_back(z);
}

double RG::z_(double X, double Y, double DY)
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
	double q1 = z_(cx, cy, cz);

	double k2 = y_z(cz + h * q1 / 2.);
	double q2 = z_(cx + h / 2., cy + h * k1 / 2., cz + h * q1 / 2.);

	double k3 = y_z(cz + h * q2 / 2.);
	double q3 = z_(cx + h / 2., cy + h * k2 / 2., cz + h * q2 / 2.);

	double k4 = y_z(cz + h * q3);
	double q4 = z_(cx + h, cy + h * k3, cz + h * q3);


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
double diff(vector<double>& left, vector<double>right)
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
		keys.clear();
		alpha.clear();
		valsZ.clear();
		counter = 0;
		x = 0;
		y = 1;
		z = 0;
		keys.push_back(x);
		valsY.push_back(y);
		valsZ.push_back(z);
		while (x <= L)DoRGStepForward();
		dy = valsZ[valsZ.size() - 1];
		y = 0;
		x = L;
		keys.clear();
		valsY.clear();
		valsZ.clear();

		while (x >= 0)DoRGStepBack();
		if (diff(valsY, prevVals) < 1e-10)stop = true;
		prevVals = valsY;
		
}


void RG::test1()
{
	keys.clear();
	alpha.clear();
	betta.clear();
	x = 0;
	y = 10;
	z = 1;
	keys.push_back(x);
	alpha.push_back(y);
	betta.push_back(z);
	counter = 0;
	
	while (x < L)DoRGStepForward();
}
void RG::test2()
{
	//dy = -psy0 / L;
	y = z / (dyb / yb - y);
	z = y * dyb / yb;
	x = L;
	dyb = z;
	yb = y;
	keys.clear();
	valsY.clear();
	valsZ.clear();
	keys.push_back(x);
	valsY.push_back(y);
	valsZ.push_back(z);
	while (x > 0)
	{
		DoRGStepBack();
	}
	reverse(valsY.begin(), valsY.end());
	reverse(keys.begin(), keys.end());
	if (diff(valsY, prevVals) < 1e-10)stop = true;
	prevVals = valsY;
	dy = z;
}