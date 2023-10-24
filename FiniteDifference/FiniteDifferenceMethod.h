#pragma once
#include "PDEBaseClass.h"
#include <vector>

class FiniteDifferenceMethod
{
protected:
	PDEBase* pde;

	//space discretisation 
	double xDomain; //spatial extent [0.0, xDomain]
	unsigned long J; //Number of spatial differencing points
	double dx; //spatial step size (calulated from above)
	std::vector<double> xVals; //stores the coordiantes of the x dimenssion


	//Time discretisation 
	double tDomain; //Temporal exten [0.0, tDomain]
	unsigned long N; //number of temporal differencing points
	double dt; //temporal step size (calulated from above)
	

	//time marching 
	double prevT, currT; // current and previous times

	//differencing coefficients 
	double alpha, beta, gamma;

	//storage
	std::vector<double> newResult; //new solution, beocmes N+1
	std::vector<double> oldResult; ///old solutios, stays as N


	//Constructor

	FiniteDifferenceMethod(double _xDomain, unsigned long _J, double _tDomain, unsigned long _N, PDEBase* _pde);


	//Override the following virtual methods in the implementation file for specific techniques used in FDM
	//Some of these techniques include Crank-Nicolson, Explicit Euler, etc

	virtual void calcStepSizes() = 0;
	virtual void setInitCond() = 0;
	virtual void calcBoundConds() = 0;
	virtual void calcInnerDomain() = 0;


public:
	//does the actual time stepping
	virtual void stepMarch() = 0;


};


class ExplicitEuler : public FiniteDifferenceMethod
{
protected:
	void calcStepSizes();
	void setInitCond();
	void calcBoundConds();
	void calcInnerDomain();

public:
	ExplicitEuler(double _xDomain, unsigned long _J, double _tDomain, unsigned long _N, PDEBase* pde);

	void stepMarch();

};

