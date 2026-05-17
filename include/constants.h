#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <math.h>

// simulation parameters
const unsigned int NUM_SHELLS = 500;

// Physical constants
const double G = 6.67430e-11f; // gravitational constant in m^3 kg^-1 s^-2
const double c = 2.998e8f; // speed of light in m/s
const double k_b = 1.380649e-23f; // Boltzmann constant in J/K
const double m_H = 1.6735575e-27f; // mass of hydrogen in kg
const double alpha = 7.5657e-16f; // radiation density constant in J m^-3 K^-4
const double PI = 3.14159265358979323846f; // value of pi

// Solar properties
const double SOLAR_RADIUS = 6.96e8f; // in meters 
const double SOLAR_MASS = 1.989e30f; // in kilograms
const double SOLAR_LUMINOSITY = 3.828e26f; // in watts

const double SSM_SOLAR_CORE_TEMPERATURE = 1.5e7f; // in Kelvin
const double SSM_SOLAR_CORE_DENSITY = 1.62e5f; // in kg/m^3
const double SSM_SOLAR_CORE_PRESSURE = 2.477e16f; // in Pascals

const double mu = 0.61f; // mean molecular weight for fully ionized gas
const double X = 0.7438f; // hydrogen mass fraction
const double Z = 0.0139f; // metallicity (helium and heavier elements)

const double epsilon_0 = 1.08e-12f; // energy generation rate at the core in W/kg
const double kappa_0 = 4*pow(10, 18.5); // opacity constant in m^2/kg


const double rad_dens_const = 7.56e-16f; // radiation density constant in J m^-3 K^-4

// eddington solar model constants
const double xi_1 = 6.897f; // the dimensional radius of the sun
const double y_1 = 2.018f; // the dimensional mass of the sun
const double theta_1 = 0.0f; // the dimensional temperature at the surface

const double SOLAR_CORE_TEMPERATURE = 1.34e7f; // in Kelvin
const double SOLAR_CORE_DENSITY = 7.63e4f; // in kg/m^3
const double SOLAR_CORE_PRESSURE = 1.24e16f; // in Pascals

const double beta = 6.58e-4f; // ratio of gas pressure to total pressure, assumed constant for simplicity

const double K = 3829661955; // polytropic constant for n=3
const double a = 100771226; // constant for calculating xi in the eddington model
const double n = 3.0; // polytropic index for the radiative zone

const double dr = SOLAR_RADIUS / NUM_SHELLS; // thickness of each shell in meters
const double d_xi = xi_1 / NUM_SHELLS; // step size for xi in the eddington model


#endif // CONSTANTS_H