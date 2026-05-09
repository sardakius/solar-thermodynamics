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
    shells[NUM_SHELLS - 1].temperature = SOLAR_CORE_TEMPERATURE*theta_1; // in Kelvin
    shells[NUM_SHELLS - 1].density = SOLAR_CORE_DENSITY*pow(theta_1, 3); // in kg/m^3
    shells[NUM_SHELLS - 1].pressure = SOLAR_CORE_PRESSURE*pow(theta_1, 4);
};

void sun::simulate_ssm() {
    shells[0].temperature = SSM_SOLAR_CORE_TEMPERATURE; // in Kelvin
    shells[0].density = SSM_SOLAR_CORE_DENSITY; // in kg/m^3
    shells[0].pressure = SSM_SOLAR_CORE_PRESSURE;

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
    }
};

void sun::simulate_eddington_euler() {
    for (int i = NUM_SHELLS - 2; i >= 0 ; i -= 1) {
        shell p = shells[i + 1];

        shells[i].xi = xi(shells[i].radius, a );
        double d_xi = p.xi - shells[i].xi;

        shells[i].y = fmax(p.y + dy(p.xi, d_xi, p.theta, n), 0);
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

void sun::simulate_eddington_rk4() {
    for (int i = NUM_SHELLS - 2; i >= 0 ; i -= 1) {
        shell p = shells[i + 1];

        shells[i].xi = xi(shells[i].radius, a);

        // simulate y and theta using rk4
        double k1_y = dy(p.xi, d_xi, p.theta, n);
        double k1_theta = d_theta(p.xi, d_xi, p.y);

        double k2_y = dy(p.xi + d_xi/2, d_xi, p.theta + k1_theta/2, n);
        double k2_theta = d_theta(p.xi + d_xi/2, d_xi, p.y + k1_y/2);

        double k3_y = dy(p.xi + d_xi/2, d_xi, p.theta + k2_theta/2, n);
        double k3_theta = d_theta(p.xi + d_xi/2, d_xi, p.y + k2_y/2);

        double k4_y = dy(p.xi + d_xi, d_xi, p.theta + k3_theta, n);
        double k4_theta = d_theta(p.xi + d_xi, d_xi, p.y + k3_y);

        // update y and theta using rk4
        shells[i].y = fmax(p.y + (1.0/6.0)*(k1_y + 2*k2_y + 2*k3_y + k4_y), 0);
        shells[i].theta = fmin(p.theta + (1.0/6.0)*(k1_theta + 2*k2_theta + 2*k3_theta + k4_theta), 1);

        // with y and theta, we can now calculate temperature, density, and pressure
        shells[i].temperature = fmax(SOLAR_CORE_TEMPERATURE*shells[i].theta, 0.0); // in Kelvin
        shells[i].density = SOLAR_CORE_DENSITY*pow(shells[i].theta, 3); // in kg/m^3
        shells[i].pressure = SOLAR_CORE_PRESSURE*pow(shells[i].theta, 4);

    }

    // initialize core using rk4 results
    float deltaM = dM(shells[0].radius, shells[0].density);
    shells[0].energy_generation_rate = epsilon(shells[0].temperature, shells[0].density);
    shells[0].absorption = kappa(shells[0].radius);

    shells[0].mass = deltaM;
    shells[0].luminosity = dL(deltaM, shells[0].energy_generation_rate);

    // now starting from the inside and going outwards, use standard physics equations to calculate luminosity and energy generation rate for each shell
    for (int i = 1; i <= (NUM_SHELLS - 1) ; i++) {
        shell p = shells[i - 1];

        // not differential so we don't use rk4 here
        shells[i].energy_generation_rate = epsilon(shells[i].temperature, shells[i].density);
        shells[i].absorption = kappa(shells[i].radius);

        // mass
        double k1_M = dM(p.radius, p.density);
        double k2_M = dM(p.radius + dr/2, 0.5*p.density + 0.5*shells[i].density ); // we can also use density at the midpoint for better accuracy, but for simplicity we'll just use the density at the beginning of the interval
        double k3_M = k2_M; // since dM is not a function of mass, we can just reuse k2_M for k3_M
        double k4_M = dM(p.radius + dr, p.density);

        double deltaM = (1.0/6.0)*(k1_M + 2*k2_M + 2*k3_M + k4_M);
        shells[i].mass = p.mass + deltaM;

        // luminosity
        double k1_L = dL(k1_M, p.energy_generation_rate);
        double k2_L = dL(k2_M, 0.5*p.energy_generation_rate + 0.5*shells[i].energy_generation_rate);
        double k3_L = k2_L; // since dL is not a function of luminosity, we can just reuse k2_L for k3_L
        double k4_L = dL(k4_M, epsilon(shells[i].temperature, shells[i].density));

        double deltaL = (1.0/6.0)*(k1_L + 2*k2_L + 2*k3_L + k4_L);
        shells[i].luminosity = p.luminosity + deltaL;
    }
};

shell* sun::get_shells() {
    return shells;
};