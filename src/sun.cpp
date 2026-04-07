#include <constants.h>
#include <simulation/shell.h>
#include <simulation/sun.h>
#include <simulation/physics.h>
#include <math.h>
#include <iostream>

using namespace std;

sun::sun() {
    // initialize the shells
    for (int i = 1; i <= NUM_SHELLS; i++) {
        shells[i - 1].radius = dr * i;
        shells[i - 1].energy_generation_rate = 0.0f;
        shells[i - 1].absorption = 0.0f;
        shells[i - 1].mass = 0.0f;
        shells[i - 1].luminosity = 0.0f;
        shells[i - 1].pressure = 0.0f;
        shells[i - 1].temperature = 0.0f;
        shells[i - 1].density = 0.0f;
    }

    // initialize the core
    shells[0].pressure = SOLAR_CORE_PRESSURE;
    shells[0].temperature = SOLAR_CORE_TEMPERATURE;
    shells[0].density = SOLAR_CORE_DENSITY;

    shells[0].energy_generation_rate = epsilon(shells[0].temperature, shells[0].density);
    shells[0].absorption = kappa(shells[0].radius);

    shells[0].mass =  4.0f / 3.0f * PI * pow(shells[0].radius, 3) * shells[0].density;
    shells[0].luminosity = dL(shells[0].mass, shells[0].energy_generation_rate);
};

void sun::simulate() {
    for (int i = 1; i <= NUM_SHELLS - 1; i++) {
        shell p = shells[i - 1];

        shells[i].density = rho(shells[i].radius);

        float deltaM = dM(shells[i].radius, shells[i].density);
        shells[i].energy_generation_rate = epsilon(p.temperature, shells[i].density);
        shells[i].absorption = kappa(shells[i].radius);

        shells[i].mass = p.mass + deltaM;
        shells[i].luminosity = p.luminosity + dL(deltaM, shells[i].energy_generation_rate);

        shells[i].pressure =  p.pressure + dP(shells[i].mass, shells[i].radius, shells[i].density);

        shells[i].temperature = p.temperature + dT(shells[i].luminosity, shells[i].radius, p.temperature, shells[i].absorption, shells[i].density);
        cout << "dP=" << shells[i].pressure - p.pressure 

     << " dT=" << shells[i].temperature - p.temperature 
     << " dL=" << shells[i].luminosity - p.luminosity << endl;
        cout << shells[i].luminosity << " " << shells[i].radius << " " << shells[i].temperature << " " << shells[i].absorption << " " << shells[i].density << " " << shells[i].pressure <<endl;

        if (shells[i].temperature < 0 || shells[i].pressure < 0 || shells[i].density < 0) {
            cout << "Simulation diverged at shell " << i << endl;
            break;
        }
    }
}

shell* sun::get_shells() {
    return shells;
}