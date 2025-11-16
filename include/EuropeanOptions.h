//
//  EuropeanOptions.hpp
//  Group A
//
//  Created by O.G on 6/11/21.
//

#ifndef EuropeanOptions_hpp
#define EuropeanOptions_hpp

#include <iostream>
#include <string>
#include <vector>

class EuropeanOption
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
    EuropeanOption();   // default constructor
    EuropeanOption(const EuropeanOption& option);   // copy constructor
    virtual ~EuropeanOption();  // destructor
    
    // operators
    EuropeanOption& operator=(const EuropeanOption& option);    // assignment operator
    
    // cumulative/probability normal distribution approximator
    double n(double x) const;   // standard pdf
    double N(double x) const;   // standard cdf
    
    // current option pricing + sensitivities
    double Price(double U) const;   // option pricing
    double Delta(double U) const;   // sensitivities
    
    // call + put price + sensitivities functions
    double CallPrice(double U) const;   // call price function
    double PutPrice(double U) const;    // put price function
    double CallDelta(double U) const;   // call delta function
    double PutDelta(double U) const;    // put delta function
    double CallPutGamma(double K, double S, double T, double r, double b, double sig) const;   // call/put gamma
    
    // put + call parity
    double ParityPrice(double U) const; // put + call parity prices
    bool isParity(double callPrice, double putPrice) const;  // checks if parity satisfies
    
    // vector + matrix pricing function
    std::vector<double> Price(const std::vector<double>& vector) const;   // vector pricing function
    std::vector<double> Price(const std::vector<std::vector<double>>& matrix) const;    // matrix pricing function
};

#endif /* EuropeanOptions_hpp */



/* THIS WOULD GO IN THE MAIN.CPP FILE CORRESPONDING TO THIS CLASS ONLY FOR TEST

//
//  main.cpp
//  Group A
//
//  Created by O.G on 6/11/21.
//

#include "EuropeanOptions.hpp"
#include <iostream>
#include <vector>
#include <numeric>

// price mesher for Part (c)
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
    // ****************************** EXACT SOLUTIONS OF ONE-FACTOR PLAIN OPTIONS ******************************
    // *************** PARTS (A) + (B) ***************

    // test values for option pricing:
    // Batch 1: T = 0.25, K = 65, sig = 0.30, r = 0.08, S = 60 (then C = 2.13337, P = 5.84628).
    EuropeanOption Batch1;
    Batch1.optionType = "C";
    Batch1.T = 0.25;    // expiry in 4 months
    Batch1.K = 65;  // strike price at $65
    Batch1.sig = 0.30;  // volatility at 0.30
    Batch1.r = 0.08;    // interest rate at 8%
    Batch1.S = 60;  // stock price at $60
    std::cout << "Batch #1:" << std::endl;
    std::cout << "\tOption Type: " << Batch1.optionType << std::endl;   // output: C
    std::cout << "\t\tOption Price: $" << Batch1.Price(2.13337) << std::endl;   // output: $0
    std::cout << "\t\tParity Put Price is: $" << Batch1.ParityPrice(2.13337) << std::endl;  // output: $57.9089
    Batch1.optionType = "P";    // change to put option
    std::cout << "\tOption Type: " << Batch1.optionType << std::endl;   // output: P
    std::cout << "\t\tOption Price: $" << Batch1.Price(5.84628) << std::endl;   // output: $57.9824
    std::cout << "\t\tParity Call Price is: $" << Batch1.ParityPrice(5.84628) << std::endl;  // output: $3.71291
    std::cout << Batch1.isParity(2.13337, 5.84628) << "\n" << std::endl;

    // Batch 2: T = 1.0, K = 100, sig = 0.2, r = 0.0, S = 100 (then C = 7.96557, P = 7.96557).
    EuropeanOption Batch2;
    Batch2.optionType = "C";    // call option
    Batch2.T = 1.0;    // expiry in 1 year
    Batch2.K = 100;  // strike price at $100
    Batch2.sig = 0.2;  // volatility at 0.2
    Batch2.r = 0.0;    // interest free rate
    Batch2.S = 100;  // stock price at $100
    std::cout << "Batch #2:" << std::endl;
    std::cout << "\tOption Type: " << Batch2.optionType << std::endl;   // output: C
    std::cout << "\t\tOption Price: $" << Batch2.Price(7.96557) << std::endl;   // output: $0
    std::cout << "\t\tParity Put Price is: $" << Batch2.ParityPrice(7.96557) << std::endl;  // output: $92.0344
    Batch2.optionType = "P";    // change to put option
    std::cout << "\tOption Type: " << Batch2.optionType << std::endl;   // output: P
    std::cout << "\t\tOption Price: $" << Batch2.Price(7.96557) << std::endl;   // output: $92.0344
    std::cout << "\t\tParity Call Price is: $" << Batch2.ParityPrice(7.96557) << std::endl;  // output: $0
    std::cout << Batch2.isParity(7.96557, 7.96557) << "\n" << std::endl;

    // Batch 3: T = 1.0, K = 10, sig = 0.50, r = 0.12, S = 5 (C = 0.204058, P = 4.07326)
    EuropeanOption Batch3;
    Batch3.optionType = "C";    // call option
    Batch3.T = 1.0;    // expiry in 1 year
    Batch3.K = 10;  // strike price at $10
    Batch3.sig = 0.50;  // volatility at 0.50
    Batch3.r = 0.12;    // interest rate at 12%
    Batch3.S = 5;  // stock price at $5
    std::cout << "Batch #3:" << std::endl;
    std::cout << "\tOption Type: " << Batch3.optionType << std::endl;   // output: C
    std::cout << "\t\tOption Price: $" << Batch3.Price(0.204058) << std::endl;   // output: *approximately* $0
    std::cout << "\t\tParity Put Price is: $" << Batch3.ParityPrice(0.204058) << std::endl;  // output: $4.81902
    Batch3.optionType = "P";    // change to put option
    std::cout << "\tOption Type: " << Batch3.optionType << std::endl;   // output: P
    std::cout << "\t\tOption Price: $" << Batch3.Price(4.07326) << std::endl;   // output: $5.29627
    std::cout << "\t\tParity Call Price is: $" << Batch3.ParityPrice(4.07326) << std::endl;  // output: $3.90893
    std::cout << Batch3.isParity(0.204058, 4.07326) << "\n" << std::endl;

    // Batch 4: T = 30.0, K = 100.0, sig = 0.30, r = 0.08, S = 100.0 (C = 92.17570, P = 1.24750).
    EuropeanOption Batch4;
    Batch4.optionType = "C";    // call option
    Batch4.T = 30.0;    // expiry in 30 years
    Batch4.K = 100.0;  // strike price at $100
    Batch4.sig = 0.30;  // volatility at 0.30
    Batch4.r = 0.08;    // interest rate at 8%
    Batch4.S = 100;  // stock price at $100
    std::cout << "Batch #4:" << std::endl;
    std::cout << "\tOption Type: " << Batch4.optionType << std::endl;   // output: C
    std::cout << "\t\tOption Price: $" << Batch4.Price(92.17570) << std::endl;   // output: $4.78155
    std::cout << "\t\tParity Put Price is: $" << Batch4.ParityPrice(92.17570) << std::endl;  // output: $96.4196
    Batch4.optionType = "P";    // change to put option
    std::cout << "\tOption Type: " << Batch4.optionType << std::endl;   // output: P
    std::cout << "\t\tOption Price: $" << Batch4.Price(1.24750) << std::endl;   // output: $8.96009
    std::cout << "\t\tParity Call Price is: $" << Batch4.ParityPrice(1.24750) << std::endl;  // output: -$90.9267
    std::cout << Batch4.isParity(92.17570, 1.24750) << "\n" << std::endl;


    // *************** PART C ***************
    // create a price mesh from 10 to 50 in int
    std::vector<double> mesh_array = PriceMesh(10.0, 50.0, 40.0);
    std::cout << mesh_array[2] << std::endl;

    // create a vector of Batch 1
    std::vector<double> Batch1_mesh;
    Batch1_mesh = Batch1.Price(mesh_array);
    //std::cout << "Batch 1 prices are now: \n" << Batch1_mesh << std::endl;


    // *************** PART D ***************




    // ****************************** OPTION SENSITIVITIES ******************************
    // *************** PART A ***************
    // creating option type to calculate call/put delta and gamma
    EuropeanOption Option1;
    std::cout << "The gamma/delta option is: " << Option1.CallPutGamma(100, 105, 0.5, 0.10, 0, 0.36) << std::endl;   // output: 0.0134938 std::endl;
    std::cout << "The call delta is: " << Option1.CallDelta(0.5946) << std::endl;   // output: 1
    std::cout << "The put delta is: " << Option1.PutDelta(0.3566) << std::endl; // output: 0

    // *************** PART B ***************
    std::vector<double> delta_price = PriceMesh(10.0, 50.0, 40.0);
    // invoke call delta on vector
    //std::vector<double> delta_put =

    // *************** PART C ***************
    // create a matrix of optiom parameters and receive a matrix of delta/gamma



    // *************** PART D ***************
    // use divided differences to approximate option sesnitivities
    double h = 0.05;
    std::cout << "The call delta for divided differences is: " << Option1.CallDelta(h) << std::endl;   // output: 1
    std::cout << "The put delta for dividided differences is: " << Option1.PutDelta(h) << std::endl; // output: 0
}






*/