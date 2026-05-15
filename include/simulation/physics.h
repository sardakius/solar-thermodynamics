#ifndef PHYSICS_H
#define PHYSICS_H

// non-eddington
double dP(double M_r, double r, double rho);
double dT(double L_r, double r, double T, double kappa, double rho);
double rho_approx(double radius);
double rho(double T, double P);
double epsilon(double T, double rho);
double kappa(double rho, double T);
double dM(double r, double rho);
double dL(double dM, double epsilon);

//eddington model
double d_theta(double xi, double d_xi, double y);
double dy(double xi, double d_xi, double theta, double n);
double xi(double radius, double a);



#endif // PHYSICS_H