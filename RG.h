#pragma once

#include<vector>


#define MS_DO_ITERATION WM_USER + 1

class RG
{
private:
	double x;
	double y;
	double y_;
	double e_betta;
	double e_alpha;
	int e_iter;

	double h;

	int counter = 0;
	int m_size;
protected:
	inline double RG::F(double pot);
	inline double RG::q(double pot);
	inline double RG::r(double pot);

	inline void EulerForward();
	inline void RG::EulerBackward();
public:
	void SetH(double h);
	void test1();
	void test2();
	std::vector<double>keys, valsY, prevVals, valsOut, a, b;
	double psy0;
	double na;
	double L;
	std::vector<double> RG::MakeStartVals();
	bool stop = false;
	double Na;
	double N0;
	double fi0;
	double Ld;
	double diff(std::vector<double>& left, std::vector<double>& right);
	HWND parent;
};