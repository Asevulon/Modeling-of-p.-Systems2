#pragma once

#include<vector>


#define MS_DO_ITERATION WM_USER + 1

class RG
{
private:
	double x;
	double y;
	double z;
	double z_;
	double y_;
	double e_betta;
	double e_alpha;
	int e_iter;

	double h;

	int counter = 0;
protected:
	inline double f(double x, double y, double z);
	inline double g(double x, double y, double z);
	inline double z__(double x, double y, double dy);
	inline double y_z(double z);

	inline double EulerF(double x, double f_alpha, int i);
	inline double EulerB(double x, double f_y, int i);
	inline double RG::EulerBZ(double x, double f_y, double z_, int i);
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

	void EulerForward();
	void RG::EulerBackward();

	std::vector<double>keys, valsY, valsZ, prevVals, alpha, betta, valsOut;

	double psy0;
	double na;
	double L;
	std::vector<double> RG::MakeStartVals();
	double dy;
	double dyb;
	double yb;

	bool stop = false;


	double Na;
	double N0;
	double fi0;
	double Ld;
	double diff(std::vector<double>& left, std::vector<double>& right);

	HWND parent;
};