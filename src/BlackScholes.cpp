// main.cpp
// Author: Omar Gabr
// 1/3/2022
/* this file computes a European vanilla call/put option using a BS model */

// preprocessor macros
#define _USE_MATH_DEFINES

// dependencies
#include <iostream>
#include <cmath>		// std::pow, std::exp,

// standard normal prob density function
// return normalized distribution
double normal_pdf(const double& x)
{
	return (1.0 / (std::pow(2 * M_PI, 0.5))) * std::exp(-0.5 * x * x);
}

// approximation to cumulative distribution function
// for the standard normal distribution
double normal_cdf(const double& x)
{
	double k = 1.0 / (1.0 + 0.2316419 * x);
	double k_sum = k * (0.319381530 + k * (-0.356563782 + k * (1.781477937 + k * (-1.821255978 + 1.330274429 * k))));

	// make sure x is positive by the following:
	// base case
	if (x >= 0.0)
	{
		return (1.0 - normal_pdf(x)*k_sum);
	}
	// recursive case
	else
	{
		return 1.0 - normal_cdf(-x);
	}
}

// finds d_j for j in {1,2} in BS model
// this is found in the closed form soln of a call/put
double d_j(const int& j, const double& S, const double& K, const double& r, const double& v, const double& T)
{
	return (std::log(S/K)+(r+ (std::pow(-1, j-1))*0.5*v*v)*T) / (v*std::pow(T, 0.5));
}

/*** European Vanilla Option Pricing **/
// call option
double BSCall(const double& S, const double& K, const double& r, const double& v, const double& T)
{
	return (S * normal_cdf(d_j(1, S, K, r, v, T))) - (K * std::exp(-r * T) * normal_cdf(d_j(2, S, K, r, v, T)));
}
// put option
double BSPut(const double& S, const double& K, const double& r, const double& v, const double& T)
{
	return (-S * normal_cdf(-d_j(1, S, K, r, v, T))) + (K * std::exp(-r * T) * normal_cdf(-d_j(2, S, K, r, v, T)));
}

int main()
{
	// Initialize parameters from user
	double S, K, r, v, T;
	std::cout << "Underlying Price, S: ";
	std::cin >> S;
	std::cout << "Strike Price, K: ";
	std::cin >> K;
	std::cout << "Risk-Free Rate, r: ";
	std::cin >> r;
	std::cout << "Volatility, v: ";
	std::cin >> v;
	std::cout << "Maturity, T: ";
	std::cin >> T;

	// compute call/put options using BS model
	double call = BSCall(S, K, r, v, T);
	double put = BSPut(S, K, r, v, T);

	// output parameter and price values
	std::cout << "\nUnderlying: " << S << std::endl;
	std::cout << "Strike: " << K << std::endl;
	std::cout << "Risk-Free Rate: " << r << std::endl;
	std::cout << "Volatility: " << v << std::endl;
	std::cout << "Maturity: " << T << std::endl;

	std::cout << "Calll Price: " << call << std::endl;
	std::cout << "Put Price: " << put << std::endl;

	return 0;
}
