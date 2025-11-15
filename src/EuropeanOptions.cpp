//
//  EuropeanOptions.cpp
//  Group A
//
//  Created by O.G on 6/11/21.
//

#include "EuropeanOptions.hpp"


// *************** CONSTRUCTOR(S) + DESTRUCTOR ***************
// default constructor
EuropeanOption::EuropeanOption(): r(0), S(0), K(0), T(0), sig(0), b(0)
{
    
};
// copy constructor
EuropeanOption::EuropeanOption(const EuropeanOption& option)
{
    // assign option input data to member data
    r = option.r;
    S = option.S;
    K = option.K;
    T = option.T;
    sig = option.sig;
    optionType = option.optionType;
};
// destructor
EuropeanOption::~EuropeanOption()
{
    
};


// *************** OPERATORS ***************
// assignment operator
EuropeanOption& EuropeanOption::operator=(const EuropeanOption& option)
{
    // assign option input data to member data
    r = option.r;
    S = option.S;
    K = option.K;
    T = option.T;
    sig = option.sig;
    optionType = option.optionType;
    return (*this); // return because return type EuropeanOption&
};


// *************** CUMULATIVE/PROBABILITY NORMAL DISTRIBUTION ***************
// n(x)
double EuropeanOption::n(double x) const
{
    double A = 1.0/sqrt(2.0 * 3.1415);
    return A * exp(-x * x * 0.5);
};
// N(x)
double EuropeanOption::N(double x) const
{
    double a1 = 0.4361836;
    double a2 = -0.1201676;
    double a3 = 0.9372980;
    double k = 1.0/(1.0 + (0.33267 * x));
    
    if (x >= 0.0)
    {
        return 1.0 - n(x) * (a1 * k + (a2 * k * k) + (a3 * k * k * k));
    }
    else
    {
        return 1.0 - N(-x);
    };
};


// *************** OPTION PRICING/DELTA ***************
// option pricing implementation
double EuropeanOption::Price(double U) const
{
    // need to check if the option type is the same
    // if option type is call
    if (optionType == "C")
    {
        // return a function that calls price with input U
        return CallPrice(U);
    }
    else
    {
        // otherwise return a function that puts price with input U
        return PutPrice(U);
    };
};
// sensitivities
double EuropeanOption::Delta(double U) const
{
    // need to check if the option type is the same
    // if option type is call
    if (optionType == "C")
    {
        std::cout << "Calling a call option." << std::endl;
        // return a function that calls delta with input U
        return CallDelta(U);
    }
    else
    {
        std::cout << "Calling a put option." << std::endl;
        // otherwise return a function that puts delta with input U
        return PutDelta(U);
    };
};


// *************** CALL + PUT PRICE/DELTA FUNCTIONS ***************
// call price
double EuropeanOption::CallPrice(double U) const
{
    double temp = sig * sqrt(T);
    double d1 = (log(U / K) + (b + (sig * sig) * 0.5) * T) / temp;
    double d2 = d1 - temp;
    
    // return call price value
    return (U * exp((b - r) * T) * N(d1)) - (K * exp(-r * T) * N(d2));
};
// put price
double EuropeanOption::PutPrice(double U) const
{
    double temp = sig * sqrt(T);
    double d1 = (log(U / K) + (b + (sig * sig) * 0.5) * T) / temp;
    double d2 = d1 - temp;
    // return put price value
    return (K * exp(-r * T) * N(-d2)) - (U * exp((b-r) * T) * N(-d1));
};
// call delta
double EuropeanOption::CallDelta(double U) const
{
    double temp = sig * sqrt(T);
    double d1 = (log(U / K) + (b + (sig * sig) * 0.5) * T) / temp;
    // return call delta value
    return exp((b - r) * T) * N(d1);
};
// put delta
double EuropeanOption::PutDelta(double U) const
{
    double temp = sig * sqrt(T);
    double d1 = (log(U / K) + (b + (sig * sig) * 0.5) * T) / temp;
    // return put delta value
    return exp((b - r) * T) * (N(d1) - 1.0);
};
// call/put gamma
double EuropeanOption::CallPutGamma(double K, double S, double T, double r, double b, double sig) const
{
    double d1 = (log(S/K) + (b + (sig*sig)*0.5) * T) / (sig * sqrt(T));
        
    return (n(d1) * exp((b-r)*T)) / (S* sig * sqrt(T));
};


// *************** PUT + CALL PARITY FUNCTIONS ***************
// put + call parity price
double EuropeanOption::ParityPrice(double U) const
{
    if (optionType == "C")
    {
        // returns put price + stock price - strike * exponential
        return (PutPrice(U) + S) - K * exp(-r * T);
    }
    else
    {
        return (CallPrice(U) + K * exp(-r * T)) - S;
    };
};
// put + call parity checker
bool EuropeanOption::isParity(double callPrice, double putPrice) const
{
    // condition if ParityPrice(double U) executes
    if (ParityPrice(callPrice) || ParityPrice(putPrice))
    {
        std::cout << "This price satisfies the put/call parity." << std::endl;
    }
    // otherwise state that the relationship does not satisfy
    else
    {
        std::cout << "This price does not satisfy the put/call parity." << std::endl;
    };
    // return the boolean condition
    return (abs(Price(callPrice) - ParityPrice(callPrice)) < 0);
};


// *************** VECTOR/MATRIX PRICING FUNCTIONS ***************
// vector pricing function
std::vector<double> EuropeanOption::Price(const std::vector<double>& vector) const
{
    // create temp vector with same size as input vector
    std::vector<double> vector1(vector.size());
    // create if/else depending on option type
    // if option is call
    if (optionType == "C")
    {
        // for loop to call price on each vector element
        for (int i = 0; i < vector.size(); i++)
        {
            // assign each temp vector element to a call price function on input vector
            vector1[i] = CallPrice(vector[i]);
        };
    }
    // if option is put
    else
    {
        // for loop to put price on each vector element
        for (int j = 0; j < vector1.size(); j ++)
        {
            // assign each temp vector element to a put price function on input vector
            vector1[j] = PutPrice(vector[j]);
        };
    };
    // return temp vector
    return vector1;
};
// maxtric pricing function
std::vector<double> EuropeanOption::Price(const std::vector<std::vector<double>>& matrix) const
{
    std::vector<double> vector;
    return vector;
};

