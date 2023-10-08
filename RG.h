#pragma once

#include<vector>

class RG
{
private:
	double x;
	double y;
	double z;



	

	double h;

	int counter = 0;
protected:
	inline double f(double x, double y, double z);
	inline double g(double x, double y, double z);
	inline double z_(double x, double y, double dy);
	inline double y_z(double z);

public:
	void SetXYZ(double x, double y, double z);
	double GetX();
	double GetY();
	double GetZ();

	void SetH(double h);

	void reset();
	int ChangeDirection();

	void test1();
	void test2();
	void DoRGStepForward();
	void DoRGStepBack();
	void DoMainJob();
	std::vector<double>keys, valsY, valsZ, prevVals, alpha, betta;

	double psy0;
	double na;
	double L;
	std::vector<double> RG::MakeStartVals();
	double dy;
	double dyb;
	double yb;

	bool stop = false;
};