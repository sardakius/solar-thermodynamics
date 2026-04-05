#ifndef CONSTANTS_H
#define CONSTANTS_H

// simulation parameters
const int NUM_SHELLS = 5000;
const float TIME_STEP = 1e5f; // in seconds

// Dimensions
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;
const unsigned int RADIUS = 250;
const unsigned int DEPTH = RADIUS / NUM_SHELLS; // in pixels, thickness of each shell in the visualization

// Solar properties
const float SOLAR_RADIUS = 6.96e8f; // in meters
const float SOLAR_MASS = 1.989e30f; // in kilograms
const float SOLAR_LUMINOSITY = 3.828e26f; // in watts
const float SOLAR_CORE_TEMPERATURE = 1.5e7f; // in Kelvin
const float SOLAR_CORE_DENSITY = 1.62e5f; // in kg/m^3
const float SOLAR_CORE_PRESSURE = 2.5e16f; // in Pascals

const float mu = 0.61f; // mean molecular weight for fully ionized gas
const float dr = SOLAR_RADIUS / NUM_SHELLS; // thickness of each shell in meters

// Physical constants
const float G = 6.67430e-11f; // gravitational constant in m^3 kg^-1 s^-2
const float k_b = 1.380649e-23f; // Boltzmann constant in J/K
const float m_H = 1.6735575e-27f; // mass of hydrogen in kg
const float a = 7.5657e-16f; // radiation density constant in J m^-3 K^-4
const float PI = 3.14159265358979323846f; // value of pi


#endif // CONSTANTS_H