#include "LinearSys.h"
#include <iostream>
#include <vector>
#include <sstream>
using namespace std;

LinearSys::LinearSys(int variables) {
    numVars = variables;
}

//Parses a string linear equation into Equations
//Stores the result into vector
void LinearSys::addEquation(string input) {
    Equations eq(numVars);

    int pos = input.find('=');
    string left = input.substr(0, pos);
    string right = input.substr(pos + 1);

    eq.con = atof(right.c_str());

    string term;
    stringstream ss(left);

    while (getline(ss, term, '+')) {
        int xPos = term.find('x');
        float coef = atof(term.substr(0, xPos).c_str());
        int varIndex = atoi(term.substr(xPos + 1).c_str());
        eq.coefficients[varIndex - 1] = coef;
    }
    equations.push_back(eq);
}

void LinearSys::num_vars() {
    cout << "Number of variables: " << numVars << endl;
}

//It store term separation with + signs
void LinearSys::printEquation(int i) {
    Equations eq = equations[i - 1];
    for (int j = 0; j < numVars; j++) {
        if (j > 0 && eq.coefficients[j] >= 0) { 
            cout << "+"; 
        }
        cout << eq.coefficients[j] << "x" << j + 1;
    }
    cout << "=" << eq.con << endl;
}

//extract and print the coefficient
//displays a vertical column
void LinearSys::column(int varIndex) {
    for (auto& eq : equations)
        cout << eq.coefficients[varIndex - 1] << endl;
}

//Sum Equations
void LinearSys::add(int a, int b) {
    Equations e1 = equations[a - 1];
    Equations e2 = equations[b - 1];

    for (int i = 0; i < numVars; i++) {
        float val = e1.coefficients[i] + e2.coefficients[i];
        if (i > 0 && val >= 0) { 
            cout << "+"; 
        }
        cout << val << "x" << i + 1;
    }
    cout << "=" << e1.con + e2.con << endl;
}

//difference between two  equations by subtracting coefficients
void LinearSys::subtract(int a, int b) {
    Equations e1 = equations[a - 1];
    Equations e2 = equations[b - 1];

    for (int i = 0; i < numVars; i++) {
        float val = e1.coefficients[i] - e2.coefficients[i];
        if (i > 0 && val >= 0) { 
            cout << "+"; 
        }
        cout << val << "x" << i + 1;
    }
    cout << "=" << e1.con - e2.con << endl;
}

void LinearSys::substitute(int xVar, int eqIndex, int sourceEq) {
    Equations& eq = equations[eqIndex - 1];
    Equations& src = equations[sourceEq - 1];

    float srcCoef = src.coefficients[xVar - 1];
    if (srcCoef == 0) {
        cout << "Cannot substitute: variable x" << xVar
            << " has coefficient 0 in equation " << sourceEq << endl;
        return;
    }

    // ratio = coefficient of xVar in target equation / coefficient of xVar in source equation
    float ratio = eq.coefficients[xVar - 1] / srcCoef;

    // Build result equation
    Equations result(numVars);
    for (int j = 0; j < numVars; j++) {
        result.coefficients[j] = eq.coefficients[j] - ratio * src.coefficients[j];
    }
    result.con = eq.con - ratio * src.con;

    // Print the resulting equation (skip zero-coefficient terms)
    bool firstPrinted = true;
    for (int j = 0; j < numVars; j++) {
        float c = result.coefficients[j];
        if (c == 0) continue;
        if (!firstPrinted && c >= 0) {
            cout << "+";
        }
        cout << c << "x" << j + 1;
        firstPrinted = false;
    }
    cout << "=" << result.con << endl;
}

//Print the Cramer's coefficient matrix
void LinearSys::D() {
    int n = equations.size();
    for (int i = 0; i < n; i++) {
        cout << "| ";
            for (int j = 0; j < numVars; j++) {
                cout << equations[i].coefficients[j];
                    if (j < numVars - 1) { 
                        cout << "\t";
                    }
            }
        cout << " |" << endl;
    }
}

void LinearSys::D_var(int xVar) {
    int n = equations.size();
    for (int i = 0; i < n; i++) {
        cout << "| ";
        for (int j = 0; j < numVars; j++) {
            // Replace the target variable's column with the constants
            if (j == xVar - 1)
                cout << equations[i].con;
            else
                cout << equations[i].coefficients[j];

            if (j < numVars - 1) cout << "\t";
        }
        cout << " |" << endl;
    }
}

void LinearSys::solve() {
    int n = equations.size();

    vector<vector<float>> mattrix(n, vector<float>(numVars + 1));

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < numVars; j++)
            mattrix[i][j] = equations[i].coefficients[j];

        mattrix[i][numVars] = equations[i].con;
    }

    // Gaussian Elimination
    for (int i = 0; i < n; i++) {
        if (mattrix[i][i] == 0) {
            cout << "No Solution" << endl;
            return;
        }

        for (int j = i + 1; j < n; j++) {
            float ratio = mattrix[j][i] / mattrix[i][i];
            for (int k = 0; k <= numVars; k++) {
                mattrix[j][k] -= ratio * mattrix[i][k];
            }
        }
    }

    vector<float> solution(numVars);

    for (int i = n - 1; i >= 0; i--) {
        solution[i] = mattrix[i][numVars];
        for (int j = i + 1; j < numVars; j++) {
            solution[i] -= mattrix[i][j] * solution[j];
        }
        solution[i] /= mattrix[i][i];
    }

    for (int i = 0; i < numVars; i++) {
        cout << "x" << i + 1 << "=" << solution[i] << endl;
    }
}