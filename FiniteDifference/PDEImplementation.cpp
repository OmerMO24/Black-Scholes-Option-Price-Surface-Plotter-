#include "PDEBaseClass.h"
#include <math.h>

BlackScholesPDE :: BlackScholesPDE(Option* _option): option(_option) {}

//diffusion coefficient 
double BlackScholesPDE::diffCoefficient(double t, double x) const
{
	double vol = option->sigma;
	return 0.5 * vol * vol * x * x; 

}

//convection coefficient 
double BlackScholesPDE::convCoefficient(double t, double x) const
{
	return (option->r)*x; 
}

//zero term coefficient 
double BlackScholesPDE::zeroCoefficient(double t, double x) const
{
	return -(option->r);
}

//source coefficient 
double BlackScholesPDE::sourceCoefficient(double t, double x) const
{
	return 0.0;
}

//left boundary condition 
double BlackScholesPDE::leftBoundary(double t, double x) const
{
	return 0.0; //specifically for a CALL option
}

//right boundary condition 
double BlackScholesPDE::rightBoundary(double t, double x) const
{
	//this is via put-call parity and workms for a call option
	return (x - (option->K) * exp(-(option->r) * ((option->T) - t)));
}

//Initial condition
double BlackScholesPDE::initCondition(double x) const
{
	return option->pay_off->operator()(x);
}


