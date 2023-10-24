#pragma once
#include "PayOff.h"

class Option
{
public:
	PayOff* pay_off;
	
	double K;
	double r;
	double T;
	double sigma;
	
	Option();
	Option(double _K, double _r, double _T, double _sigma, PayOff* _pay_off);
};