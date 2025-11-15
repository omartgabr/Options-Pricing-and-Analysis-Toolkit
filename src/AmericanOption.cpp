//
//  AmericanOption.cpp
//  Group B
//
//  Created by O.G on 6/13/21.
//

#include "AmericanOption.hpp"

// default constructor
AmericanOption::AmericanOption()
{
    
};
// copy constructor
AmericanOption::AmericanOption(const AmericanOption& option)
{
    r = option.r;
    S = option.S;
    K = option.K;
    T = option.T;
    sig = option.sig;
    b = option.b;
    optionType = option.optionType;
};
// destructor
AmericanOption::~AmericanOption()
{
    
};

// operators
// assignment operator
AmericanOption& AmericanOption::operator=(const AmericanOption &option)
{
    r = option.r;
    S = option.S;
    K = option.K;
    T = option.T;
    sig = option.sig;
    b = option.b;
    optionType = option.optionType;
    return (*this);
};


// perpetual call/put pricing
// perpetual call pricing
double AmericanOption::PerpetualCall() const
{
    double y1 = 0.5 - b / (sig * sig) + sqrt((b / (sig * sig) - 0.5) * (b / (sig * sig) - 0.5) + 2 * r / (sig * sig));
        
    return K / (y1 - 1.0) * pow(((y1 - 1.0) / y1 * S / K), y1);
};
// perpetual put pricing
double AmericanOption::PerpetualPut() const
{
    double y2 = 0.5 - b / (sig * sig) - sqrt((b / (sig * sig) - 0.5)*(b / (sig * sig) - 0.5) + 2 * r / (sig * sig));
        
    return K / (1.0 - y2) * pow(((y2 - 1.0) / y2 * S / K), y2);
};
// perpetual call pricing
double AmericanOption::PerpetualCall(double U) const
{
    double y1 = 0.5 - b / (sig * sig) + sqrt((b / (sig * sig) - 0.5) * (b / (sig * sig) - 0.5) + 2 * r / (sig * sig));
        
    return K / (y1 - 1.0) * pow(((y1 - 1.0) / y1 * S / K), y1);
};
// perpetual put pricing
double AmericanOption::PerpetualPut(double U) const
{
    double y2 = 0.5 - b / (sig * sig) - sqrt((b / (sig * sig) - 0.5)*(b / (sig * sig) - 0.5) + 2 * r / (sig * sig));
        
    return K / (1.0 - y2) * pow(((y2 - 1.0) / y2 * S / K), y2);
};



// vector perpetual call/put pricing
// perpetual americal call pricing
std::vector<double> AmericanOption::PerpetualCall(const std::vector<double>& vector)
{
    std::vector<double> callOption;

    // iterate through each element in vector
    for (int i = 0; i < vector.size(); i++)
    {
        // calculate perpetual call option for each element
        callOption.push_back(PerpetualCall());
    }
    // return call vector
    return callOption;
};
// perpetual americal put pricing
std::vector<double> AmericanOption::PerpetualPut(const std::vector<double>& vector)
{
    std::vector<double> putOption;
    // iterate through each element in vector
    for (int i = 0; i < vector.size(); i++)
    {
        // calculate perpetual put option for each element
        putOption.push_back(PerpetualPut());
    }
    // return put vector
    return putOption;
};


