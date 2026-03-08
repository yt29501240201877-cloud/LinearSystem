#pragma once
#ifndef EQUATIONS_H_
#define EQUATIONS_H_
#include <vector>
using namespace std;

class Equations
{
public:
    vector<float> coefficients;
    float con;
    Equations(int vars = 0);
};


#endif 
