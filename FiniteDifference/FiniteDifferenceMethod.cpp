#include "FiniteDifferenceMethod.h"
#include <fstream>


FiniteDifferenceMethod::FiniteDifferenceMethod(double _xDomain, unsigned long _J, double _tDomain, unsigned long _N, PDEBase* _pde):
	xDomain(_xDomain), J(_J), tDomain(_tDomain), N(_N), pde(_pde) {}

ExplicitEuler::ExplicitEuler(double _xDomain, unsigned long _J, double _tDomain, unsigned long _N, PDEBase* _pde) : FiniteDifferenceMethod(_xDomain, _J, _tDomain, _N, _pde)
{
	calcStepSizes();
	setInitCond();
}

void ExplicitEuler::calcStepSizes()
{
	dx = xDomain / static_cast<double>(J - 1);
	dt = tDomain / static_cast<double>(N - 1);
}
	
void ExplicitEuler::setInitCond()
{
	double currSpot = 0.0;

	oldResult.resize(J, 0.0);
	newResult.resize(J, 0.0);
	xVals.resize(J, 0.0);

	for (unsigned long j = 0; j < J; j++)
	{
		currSpot = static_cast<double>(j) * dx;
		oldResult[j] = pde->initCondition(currSpot);
		xVals[j] = currSpot;

	}

	//Temporal Settings 
	prevT = 0.0;
	currT = 0.0;

}

void ExplicitEuler::calcBoundConds()
{
	newResult[0] = pde->leftBoundary(prevT, xVals[0]);
	newResult[J - 1] = pde->rightBoundary(prevT, xVals[J - 1]);
}

void ExplicitEuler::calcInnerDomain()
{
	//only use inner result indices (1 to J-2)
	for (unsigned long j = 1; j < J - 1; j++)
	{
		//temporary variables used throughout, not ideal for performance but it is not a priority here 
		double dtSig = dt * (pde->diffCoefficient(prevT, xVals[j]));
		double dtSig2 = dt * dx * 0.5 * (pde->convCoefficient(prevT, xVals[j]));

		//Differencing Coefficients: alpha, beta, gamma
		alpha = dtSig - dtSig2;
		beta = dx * dx - (2.0 * dtSig) + (dt * dx * dx * (pde->zeroCoefficient(prevT, xVals[j])));
		gamma = dtSig + dtSig2;

		//update inner values of spatial discretisation grid (explicit euler method)

		newResult[j] = ((alpha * oldResult[j - 1]) + (beta * oldResult[j]) + (gamma * oldResult[j])) / (dx * dx) - (dt * (pde->sourceCoefficient(prevT, xVals[j])));

	}

}

void ExplicitEuler::stepMarch()
{
	std::ofstream FiniteDifferenceMethod_out("FiniteDifferenceMethod.csv");

	while (currT < tDomain)
	{
		currT = prevT + dt;
		calcBoundConds();
		calcInnerDomain();
		for (int j = 0; j < J; j++)
		{
			FiniteDifferenceMethod_out << xVals[j] << " " << prevT << " " << newResult[j] << std::endl;
		}

		oldResult = newResult;
		prevT = currT;
	}

	FiniteDifferenceMethod_out.close();
}


