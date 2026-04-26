#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <math.h>

// simulation parameters
const unsigned int NUM_SHELLS = 1000;
const float TIME_STEP = 1e5f; // in seconds


// Dimensions
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;
const unsigned int RADIUS = 250;
const unsigned int DEPTH = RADIUS / NUM_SHELLS; // in pixels, thickness of each shell in the visualization

// Physical constants
const float G = 6.67430e-11f; // gravitational constant in m^3 kg^-1 s^-2
const float c = 2.998e8f; // speed of light in m/s
const float k_b = 1.380649e-23f; // Boltzmann constant in J/K
const float m_H = 1.6735575e-27f; // mass of hydrogen in kg
const float alpha = 7.5657e-16f; // radiation density constant in J m^-3 K^-4
const float PI = 3.14159265358979323846f; // value of pi

// Solar properties
const float SOLAR_RADIUS = 6.96e8f; // in meters 
const float SOLAR_MASS = 1.989e30f; // in kilograms
const float SOLAR_LUMINOSITY = 3.828e26f; // in watts

// const float SOLAR_CORE_TEMPERATURE = 1.5e7f; // in Kelvin
// const float SOLAR_CORE_DENSITY = 1.62e5f; // in kg/m^3
// const float SOLAR_CORE_PRESSURE = 2.5e16f; // in Pascals

const float mu = 0.61f; // mean molecular weight for fully ionized gas
const float X = 0.7438f; // hydrogen mass fraction
const float Z = 0.0139f; // metallicity (helium and heavier elements)

const float epsilon_0 = 1.08e-12f; // energy generation rate at the core in W/kg
const float kappa_0 = 4e21f; // opacity constant in m^2/kg

// eddington solar model constants
const float xi_1 = 6.897f; // the dimensional radius of the sun
const float y_1 = 2.018f; // the dimensional mass of the sun
const float theta_1 = 0.0f; // the dimensional density at the surface

const float SOLAR_CORE_TEMPERATURE = 1.34e7f; // in Kelvin
const float SOLAR_CORE_DENSITY = 7.63e4f; // in kg/m^3
const float SOLAR_CORE_PRESSURE = 1.24e16f; // in Pascals

const float beta = 6.58e-4f; // ratio of gas pressure to total pressure, assumed constant for simplicity

const double K = 3829661955; // polytropic constant for n=3
const double a = 100771226; // constant for calculating xi in the eddington model

const float dr = SOLAR_RADIUS / NUM_SHELLS; // thickness of each shell in meters


#endif // CONSTANTS_H