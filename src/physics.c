#include <simulation/physics.h>
#include <constants.h>
#include <math.h>

// non-eddington
double dP(double M_r, double r, double rho) {
    // return (-G*M_r*rho*dr)/(pow(r, 2));
    return (-G*M_r*rho*dr)/(r*r);
};

double dT(double L_r, double r, double T, double kappa, double rho) {
    return -(3*kappa*rho*L_r*dr)/(16*PI*c*pow(T, 3.0)*pow(r, 2.0)*rad_dens_const);
};

double rho_approx(double radius) {
    double r_p = radius/SOLAR_RADIUS;
    return fmax((519*pow(r_p, 4) - 1630*pow(r_p, 3) + 1844*pow(r_p, 2) - 889*r_p + 155)*1e3, 1e-7);  
}; 

double rho(double T, double P) {
    return (P*mu*m_H)/(k_b*T);
};

double epsilon(double T, double rho) {
    return epsilon_0*rho*pow(T/1e6f, 4)*pow(X, 2);
    //return 1.07e-7f;
};

double kappa(double rho, double T) {
        // if (rho < 0.2*SOLAR_RADIUS) { return 0.34; }
        // else if (rho < 0.7*SOLAR_RADIUS) { return 0.1; }
        // else { return 0.02; }
    return kappa_0*rho*pow(T, -3.5f);
};

double dM(double r, double rho) {
    return 4*PI*pow(r, 2)*dr*rho;
};

double dL(double dM, double epsilon) {
    return dM*epsilon;
};

//eddington model (d_theta and dy are negative because we are integrating from the surface to the core, so we are going in the negative direction of xi)
double d_theta(double xi, double d_xi, double y) {
    return y/pow(xi, 2)*d_xi;
};
double dy(double xi, double d_xi, double theta, double n) {
    return -fmax(pow(theta, n)*pow(xi, 2), 1e-5f)*d_xi;
};
double xi(double radius, double a) {
    return fmax(radius/a, 0.01);
};
