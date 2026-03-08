#include <iostream>
#include <vector>
#include "Equations.h"
#include "LinearSys.h"
#include <sstream>
using namespace std;



int main() {

    cout << "Enter number of equations: ";
    int n;
    cin >> n;
    cout << "Enter equations: " << endl;
    cin.ignore();

    vector<string> inputs(n);
    int maxVar = 0;

    // First read equations to detect number of variables
    for (int i = 0; i < n; i++) {
        getline(cin, inputs[i]);
        for (int j = 0; j < inputs[i].length(); j++) {
            if (inputs[i][j] == 'x') {
                int var = inputs[i][j + 1] - '0';
                maxVar = max(maxVar, var);
            }
        }
    }

    LinearSys operation(maxVar);

    for (int i = 0; i < n; i++)
        operation.addEquation(inputs[i]);

    string command;

    while (cin >> command) {
        if (command == "quit") break;

        if (command == "num_vars") {
            operation.num_vars();
        }
            

        else if (command == "equation") {
            int i;
            cin >> i;
            operation.printEquation(i);
        }

        else if (command == "column") {
            string var;
            cin >> var;
            int v = var[1] - '0';
            operation.column(v);
        }

        else if (command == "add") {
            int a, b;
            cin >> a >> b;
            operation.add(a, b);
        }

        else if (command == "subtract") {
            int a, b;
            cin >> a >> b;
            operation.subtract(a, b);
        }

        else if (command == "substitute") {
            string var;
            int eqIndex, sourceEq;
            cin >> var >> eqIndex >> sourceEq;
            int v = var[1] - '0';
            operation.substitute(v, eqIndex, sourceEq);
        }

        else if (command == "D") {
            // Peek at the rest of the line to check if a variable follows
            string peek;
            if (cin.peek() != '\n' && cin >> peek && !peek.empty()) {
                // D x1, D x2, etc.
                int v = peek[1] - '0';
                operation.D_var(v);
            }
            else {
                operation.D();
            }
        }

        else if (command == "solve")
            operation.solve();
    }

    return 0;
}