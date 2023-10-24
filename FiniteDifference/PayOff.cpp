#include "PayOff.h"

PayOff :: PayOff() {}


//PayOffCall implementation

PayOffCall::PayOffCall(const double& _K) { K = _K; }

//overriden operator method which turns the payoffcall into a functor
double PayOffCall::operator() (const double& S) const
{
	return std::max(S - K, 0.0); //standard european call payoff
}


//PayOffPut implementation 

PayOffPut::PayOffPut(const double& _K) { K = _K; }

//overriden operator method which turns the payoffcall into a functor
double PayOffPut::operator() (const double& S) const
{
	return std::max(K - S, 0.0); //standard european put payoff
}

