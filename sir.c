#include "sir.h"

SIR sir_novy(SIR stary, double b, double y){
    SIR novy;
    // S(d) = S(d-1) - b * S(d-1) * I(d-1)
    novy.susceptible = stary.susceptible - (b * stary.susceptible * stary.infected);
    // I(d) = I(d-1) + b * S(d-1) * I(d-1) - y * I(d-1)
    novy.infected = stary.infected + (b * stary.susceptible * stary.infected) - (y * stary.infected);
    // R(d) = R(d-1) + y * I(d-1)
    novy.recovered = stary.recovered + (y * stary.infected);

    return novy;
}

