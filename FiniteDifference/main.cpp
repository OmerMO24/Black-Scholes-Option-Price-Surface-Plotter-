#include "PayOff.h"
#include "FiniteDifferenceMethod.h"
#include "Option.h"
#include "PDEBaseClass.h"
#include <iostream>



void main()
{
	double K = 0.5; //strike price
	double r = 0.05; //riskl free rate
	double v = 0.2; //volatility of the underlying asset
	double T = 1.00; //time to expiry

	//std::cout << "Strike Price: ";
	//std::cin >>  K;

	//std::cout << "Risk Free Interest RoR: ";
	//std::cin >> r;

	//std::cout << "Volatility of the Underlying Asset: ";
	//std::cin >> v;

	//std::cout << "Time until Option Expiry: ";
	//std::cin >> T;


	//FDM discretisation parameters have been pre determined 
	double xDomain = 1.0;
	unsigned long J = 20;
	double tDomain = T;
	unsigned long N = 20;

	///create the payoff and option objects
	PayOff* payOffCall = new PayOffCall(K);
	Option* callOption = new Option(K, r, T, v, payOffCall);


	//create the PDE and Finite Difference Method objects
	BlackScholesPDE* BS_PDE = new BlackScholesPDE(callOption);
	ExplicitEuler expEuler(xDomain, J, tDomain, N, BS_PDE);

	//run the solver
	expEuler.stepMarch();

	//free up some memory
	delete BS_PDE;
	delete callOption;
	delete payOffCall;


}