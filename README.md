# Options Pricing Models in C++

This project explores how core derivatives pricing models can be implemented efficiently in C++.  

I built these models to deepen my understanding of quantitative finance while improving my ability to translate mathematical formulas into clean, modular code.

This repository contains C++ implementations of three fundamental derivatives pricing models:

- **Black–Scholes**
- **European Options**
- **American Options**

Each model is organized using a header file, source file, and main file to demonstrate clear object-oriented design.

---

## Skills Used
- Object-oriented programming in C++ (classes, abstraction, modular structure)  
- Mathematical and numerical computation for financial models  
- Use of standard C++ libraries (`<cmath>`, `<vector>`, `<iostream>`) for calculations, utilities, and testing  

---

## What I Learned
- How to build reusable C++ classes for financial models  
- How different option styles require different pricing approaches  
- Practical experience applying quantitative finance concepts in code

---

## Future Suggestions

An improvement for the project would be to add a Monte Carlo simulation module.  
Right now, the project uses **deterministic, closed-form formulas**, meaning each option price is computed directly from a fixed equation with no randomness or simulation. This creates two limitations:

- **It cannot model randomness in asset prices** — real markets follow stochastic processes, but closed-form formulas assume a perfect mathematical world, so the current code cannot handle path-dependent or more realistic payoffs.
- **It does not exploit C++ low latency** — closed-form formulas require almost no computation, so the project doesn’t demonstrate C++ strengths like fast numerical loops, efficient memory handling, or parallel execution.

Adding a Monte Carlo module directly fixes these issues by introducing simulated random price paths and giving the project a natural place to showcase high-performance C++ techniques (`<random>`, optimized loops, and optional multithreading).

