#include <simulation/physics.h>
#include <constants.h>
#include <math.h>

float dP(float M_r, float r, float rho) {
    return (-G*M_r*rho)/(pow(r, 2));
};

float dT(float L_r, float r, float T, float kappa, float rho) {
    return (-3*kappa*rho*L_r)/(4*a*c*pow(T, 3)*4*PI*pow(r, 2));
};

float rho(float P, float T) {
    return (P*mu*m_H)/(T*k_b);
};

float epsilon(float T, float rho) {
    return epsilon_0*rho*pow(T, 4);
};

float kappa(float T, float rho) {
    return kappa_0*(1 + X)*(Z + 0.001)*rho*pow(T, -3.5);
};

float dM(float r, float rho) {
    return 4*PI*pow(r, 2)*dr*rho;
};

float dL(float dM, float epsilon) {
    return dM*epsilon;
};