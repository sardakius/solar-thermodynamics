#include <simulation/physics.h>
#include <constants.h>
#include <math.h>

double dP(float M_r, float r, float rho) {
    // return (-G*M_r*rho*dr)/(pow(r, 2));
    return (-G*M_r*rho*dr)/(r*r);
};

double dT(float L_r, float r, float T, float kappa, float rho) {
    return (-3*kappa*rho*L_r*dr)/(16*PI*a*c*T*T*T*r*r);
};

double rho(float P, float T) {
    return (P*mu*m_H)/(T*k_b);
};

double epsilon(float T, float rho) {
    return epsilon_0*pow(X, 2)*rho*pow(T/1e6f, 4);
};

double kappa(float T, float rho) {
    return 0.34;
    // return kappa_0*pow(rho, 1)*pow(T, -3.5f);
};

double dM(float r, float rho) {
    return 4*PI*pow(r, 2)*dr*rho;
};

double dL(double dM, double epsilon) {
    return dM*epsilon;
};