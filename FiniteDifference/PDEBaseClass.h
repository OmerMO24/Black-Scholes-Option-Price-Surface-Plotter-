#pragma once
#include "Option.h"

class PDEBase
{
public:
	//PDE Coefficients
	virtual double diffCoefficient(double t, double x) const = 0;
	virtual double convCoefficient(double t, double x) const = 0;
	virtual double zeroCoefficient(double t, double x) const = 0;
	virtual double sourceCoefficient(double t, double x) const = 0;

	//Boundary Conditions 
	virtual double leftBoundary(double t, double x) const = 0;
	virtual double rightBoundary(double t, double x) const = 0;
	virtual double initCondition(double x) const = 0;

};

class BlackScholesPDE : public PDEBase
{
public:

	Option* option;
	BlackScholesPDE(Option* _option);

	double diffCoefficient(double t, double x) const;
	double convCoefficient(double t, double x) const;
	double zeroCoefficient(double t, double x) const;
	double sourceCoefficient(double t, double x) const;

	double leftBoundary(double t, double x) const;
	double rightBoundary(double t, double x) const;
	double initCondition(double x) const;
};