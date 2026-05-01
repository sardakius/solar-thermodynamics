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
    // shells[0].pressure = SOLAR_CORE_PRESSURE;
    // shells[0].temperature = SOLAR_CORE_TEMPERATURE;
    // shells[0].density = SOLAR_CORE_DENSITY;

    // shells[0].energy_generation_rate = epsilon(shells[0].temperature, shells[0].density);
    // shells[0].absorption = kappa(shells[0].radius);

    // shells[0].mass =  4.0f / 3.0f * PI * pow(shells[0].radius, 3) * shells[0].density;
    // shells[0].luminosity = dL(shells[0].mass, shells[0].energy_generation_rate);

    // initialize surface
    shells[NUM_SHELLS - 1].xi = xi_1;
    shells[NUM_SHELLS - 1].y = y_1;
    shells[NUM_SHELLS - 1].theta = theta_1;

    shells[NUM_SHELLS - 1].radius = SOLAR_RADIUS;
    // shells[NUM_SHELLS - 1].mass = SOLAR_MASS;
    shells[NUM_SHELLS - 1].temperature = SOLAR_CORE_TEMPERATURE*theta_1; // in Kelvin
    shells[NUM_SHELLS - 1].density = SOLAR_CORE_DENSITY*pow(theta_1, 3); // in kg/m^3
    shells[NUM_SHELLS - 1].pressure = SOLAR_CORE_DENSITY*pow(theta_1, 4);
};

void sun::simulate() {
    for (int i = 1; i <= (NUM_SHELLS - 1) ; i++) {
        shell p = shells[i - 1];

        shells[i].density = rho(shells[i].radius);

        float deltaM = dM(shells[i].radius, shells[i].density);
        shells[i].energy_generation_rate = epsilon(p.temperature, shells[i].density);
        shells[i].absorption = kappa(shells[i].radius);

        shells[i].mass = p.mass + deltaM;
        shells[i].luminosity = p.luminosity + dL(deltaM, shells[i].energy_generation_rate);

        shells[i].pressure =  p.pressure + dP(shells[i].mass, shells[i].radius, shells[i].density);

        shells[i].temperature = p.temperature + dT(shells[i].luminosity, shells[i].radius, p.temperature, shells[i].absorption, shells[i].density);
    //     cout << "dP=" << shells[i].pressure - p.pressure 
    //  << " dT=" << shells[i].temperature - p.temperature 
    //  << " dL=" << shells[i].luminosity - p.luminosity << endl;
    //     cout << shells[i].luminosity << " " << shells[i].radius << " " << shells[i].temperature << " " << shells[i].absorption << " " << shells[i].density << " " << shells[i].pressure <<endl;


        if (shells[i].temperature < 0 || shells[i].pressure < 0 || shells[i].density < 0) {
            cout << "Simulation diverged at shell " << i << endl;
            break;
        }
    }
};

void sun::simulate_eddington() {
    for (int i = NUM_SHELLS - 2; i >= 0 ; i -= 1) {
        shell p = shells[i + 1];

        shells[i].xi = xi(shells[i].radius);
        double d_xi = p.xi - shells[i].xi;

        shells[i].y = fmax(p.y + dy(p.xi, d_xi, p.theta), 0);
        shells[i].theta = fmin(p.theta + d_theta(p.xi, d_xi, p.y), 1);

        shells[i].temperature = fmax(SOLAR_CORE_TEMPERATURE*shells[i].theta, 0.0); // in Kelvin
        shells[i].density = SOLAR_CORE_DENSITY*pow(shells[i].theta, 3); // in kg/m^3
        shells[i].pressure = SOLAR_CORE_PRESSURE*pow(shells[i].theta, 4);
    }

    // now use standard physics equations to calculate luminosity and energy generation rate for each shell
    float deltaM = dM(shells[0].radius, shells[0].density);
    shells[0].energy_generation_rate = epsilon(shells[0].temperature, shells[0].density);
    shells[0].absorption = kappa(shells[0].radius);

    shells[0].mass = deltaM;
    shells[0].luminosity = dL(deltaM, shells[0].energy_generation_rate);
    for (int i = 1; i <= (NUM_SHELLS - 1) ; i++) {

        float deltaM = dM(shells[i].radius, shells[i].density);
        shells[i].energy_generation_rate = epsilon(shells[i].temperature, shells[i].density);
        shells[i].absorption = kappa(shells[i].radius);

        shells[i].mass = shells[i - 1].mass + deltaM;
        shells[i].luminosity = shells[i - 1].luminosity + dL(deltaM, shells[i].energy_generation_rate);
    }   
};

shell* sun::get_shells() {
    return shells;
};