#include "Equations.h"


Equations::Equations(int vars) {
    coefficients.resize(vars, 0);
    con = 0;
}
