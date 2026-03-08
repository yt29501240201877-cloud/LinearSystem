#pragma once
#ifndef LINEARSYS_H_
#define LINEARSYS_H_
#include <vector>
#include "Equations.h"
#include <iostream>
using namespace std;

class LinearSys : public Equations
{
public:
    vector<Equations> equations;
    int numVars;

public:
    LinearSys(int nVars);

    void addEquation(string input);

    void num_vars();

    void printEquation(int i);

    void column(int varIndex);

    void add(int a, int b);

    void subtract(int a, int b);

    void substitute(int xVar, int eqIndex, int sourceEq);

    void D();

    void D_var(int xVar);

    void solve();

};

#endif
