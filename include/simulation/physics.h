#ifndef PHYSICS_H
#define PHYSICS_H

// non-eddington
double dP(float M_r, float r, float rho);
double dT(float L_r, float r, float T, float kappa, float rho);
double rho(float radius);
double epsilon(float T, float rho);
double kappa(float radius);
double dM(float r, float rho);
double dL(double dM, double epsilon);

//eddington model
double d_theta(double xi, double d_xi, double y);
double dy(double xi, double d_xi, double theta);
double xi(double radius);



#endif // PHYSICS_H