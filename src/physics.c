#include <simulation/physics.h>
#include <constants.h>
#include <math.h>

double dP(float M_r, float r, float rho) {
    // return (-G*M_r*rho*dr)/(pow(r, 2));
    return (-G*M_r*rho*dr)/(r*r);
};

double dT(float L_r, float r, float T, float kappa, float rho) {
    return -fmin((3*kappa*rho*L_r*dr)/(16*PI*a*c*T*T*T*r*r), 0.1f*T);
};

double rho(float radius) {
    float r_p = radius/SOLAR_RADIUS; // radius as a fracion of solar radius
    return fmax((519*pow(r_p, 4) - 1630*pow(r_p, 3) + 1844*pow(r_p, 2) - 889*r_p + 155)*1e3f, 1e-7f);
}; 

double epsilon(float T, float rho) {
    return epsilon_0*rho*pow(T/1e6f, 4);
    //return 1.07e-7f;
};

double kappa(float radius) {
    if (radius < 0.2*SOLAR_RADIUS) { return 0.34; }
    else if (radius < 0.7*SOLAR_RADIUS) { return 0.1; }
    else { return 0.02; }
    // return 0.1;
};

double dM(float r, float rho) {
    return 4*PI*pow(r, 2)*dr*rho;
};

double dL(double dM, double epsilon) {
    return dM*epsilon;
};