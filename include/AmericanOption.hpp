//
//  AmericanOption.hpp
//  Group B
//
//  Created by O.G on 6/13/21.
//

#ifndef AmericanOption_hpp
#define AmericanOption_hpp

#include <iostream>
#include <vector>

class AmericanOption
{
public:
    // data members
    double r;   // interest rate
    double S;   // asset price
    double K;   // strike price
    double T;   // time to expiry
    double sig; // volatility
    double b;   // cost of carry
    std::string optionType; // put or call option
    
    // constructors + destructors
    AmericanOption();   // default constructor
    AmericanOption(const AmericanOption& option);   // copy constructor
    virtual ~AmericanOption();  // virtual destructor
    
    // operators
    AmericanOption& operator=(const AmericanOption& option);    // assignment operator
    
    // perpetual call/put pricing
    double PerpetualCall() const;   // call option no input
    double PerpetualPut() const;    // put option no input
    double PerpetualCall(double U) const;   // call option
    double PerpetualPut(double U) const;    // put option
    
    // vector of perpetual call/put pricing
    std::vector<double> PerpetualCall(const std::vector<double>& vector);
    std::vector<double> PerpetualPut(const std::vector<double>& vector);
    
};

#endif /* AmericanOption_hpp */



/* THIS WOULD GO IN THE MAIN.CPP FILE FOR ONLY THIS CLASS FOR TESTING

//
//  main.cpp
//  Group B
//
//  Created by O.G on 6/13/21.
//

#include "AmericanOption.hpp"
#include <iostream>
#include <vector>

template <typename T>
std::vector<T> PriceMesh(T begin, T end, T interval)
{
    // create price array vector
    std::vector<double> price_array;
    T temp = begin;
    // as long as temp is less than or equal to end, we should add the temp value to the vector
    while (temp <= end)
    {
        // push back temp to vector, then increment temp
        price_array.push_back(temp);
        temp = temp + interval;
    };
    // return newly adjusted vector
    return price_array;
};

int main()
{
    // ****************************** GROUP A ******************************
    // ****************************** PERPETUAL AMERICAN OPTIONS ******************************

    // *************** PART A COMPLETED IN AMERICANOPTION.HPP/CPP ***************
    // *************** PART B ***************
    // testing the following data:
    AmericanOption Option1;
    Option1.K = 100;
    Option1.sig = 0.1;
    Option1.r = 0.1;
    Option1.b = 0.02;
    Option1.S = 110;
    Option1.optionType = "C";
    std::cout << "The perpetual call option is: $" << Option1.PerpetualCall(18.5035) << std::endl;
    Option1.optionType = "P";
    std::cout << "The perpetual put option is: $" << Option1.PerpetualPut(3.03106) << std::endl;


    // *************** PART C ***************
    // invoke perpetucal call/put pricing functions on vector with input U
    std::vector<double> perpetualOption = PriceMesh(10.0, 50.0, 1.0);
    std::vector<double> PerpetualCallPrices = Option1.PerpetualCall(perpetualOption);
    std::vector<double> PerpetualPutPrices = Option1.PerpetualPut(perpetualOption);


    // *************** PART C ***************
    // invoke perpetucal call/put pricing functions on matrix with input U
    // make matrix of option parameters and return Perpetual call/put option prices



}




*/