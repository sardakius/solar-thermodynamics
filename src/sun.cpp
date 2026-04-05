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
    shells[0].absorption = kappa(shells[0].temperature, shells[0].density);

    shells[0].mass = dM(shells[0].radius, shells[0].density);
    shells[0].luminosity = dL(shells[0].mass, shells[0].energy_generation_rate);
};

void sun::simulate() {
    for (int i = 1; i <= NUM_SHELLS - 1; i++) {
        shell p = shells[i - 1];\

        shells[i].density = rho(p.pressure, p.temperature);

        float deltaM = dM(shells[i].radius, shells[i].density);

        shells[i].mass = p.mass + deltaM;
        shells[i].luminosity = p.luminosity + dL(deltaM, p.energy_generation_rate);

        cout << p.luminosity << " " << dL(deltaM, p.energy_generation_rate) << " " << p.temperature << " " << dT(shells[i].luminosity, shells[i].radius, p.temperature, p.absorption, p.density) << " " << shells[i].radius << endl;

        shells[i].pressure =  p.pressure + dP(shells[i].mass, shells[i].radius, shells[i].density);
        shells[i].temperature = p.temperature + dT(shells[i].luminosity, shells[i].radius, p.temperature, p.absorption, shells[i].density);

        shells[i].energy_generation_rate = epsilon(shells[i].temperature, shells[i].density);
        shells[i].absorption = kappa(shells[i].temperature, shells[i].density);
    }
}

shell* sun::get_shells() {
    return shells;
}