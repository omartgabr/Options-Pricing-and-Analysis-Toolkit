#pragma once
// Options.h
/*
This header file contains declarations for option pricing models using OOP principles including polymorphism and inheritance.
*/

#include <iostream>

/****************** OPTIONS CLASS (ABSTRACT) ******************/
// The option class is an abstract base class that other option types will inherit from like American and European types
class Option {
protected:
	// interest rate, asset price, strike price, time to expiry, volatility, cost of carry, and option type
	double r, S, K, T, sig, b;
	std::string optionType;	// put or call types
public:
	// virtual keyword allows for polymorphism and proper clean up
	// careful that constructors are not virtual since virtual requires an object to exist, but constructors are called before the object exists
	virtual ~Option() = default;
	Option(double r, double S, double K, double T, double sig, double b, const std::string& optionType)
		: r(r), S(S), K(K), T(T), sig(sig), b(b), optionType(optionType) {}

	// getter functions are intended to be inherited by option types
	// not virtual since it can add vtables unnecessarily, increases object size, and adds runtime dispatch overhead, when the values are already identical for every derived type and contain no polymorphic logic
	double getR() const { return r; }
	double getS() const { return S; }
	double getK() const { return K; }
	double getT() const { return T; }
	double getSig() const { return sig; }
	double getB() const { return b; }
	std::string getOptType() const { return optionType; }

	// all options share these pricing and sensitivies behavior
	// virtual functions allow for dynamic dispatching
	virtual double Price(double U) const = 0;	// theo of option given underlying price
	virtual double Delta(double U) const = 0;	// roc of option price wrt underlying price
	virtual double Gamma(double U) const = 0;	// second derivative of delta wrt underlying price
};



/****************** EUROPEAN OPTIONS CLASS ******************/
// European options class is derived from options
class EuropeanOption : public Option {
protected:
	// what is the purpose of protected, and does this context require any?
public:
	// no need to declare destructor for derived class since the base destructor is virtual
	EuropeanOption(double r, double S, double K, double T, double sig, double b, std::string optionType) : Option(r, S, K, T, sig, b, optionType) {}	   // base constructor call
};



/****************** AMERICAN OPTIONS CLASS ******************/
// Similar to European options, this is a derived class for Options
class AmericanOption : public Option {
protected:
public:
	// no destructor needed
	AmericanOption(double r, double S, double K, double T, double sig, double b, std::string optionType) : Option(r, S, K, T, sig, b, optionType) {}
};