#ifndef PHYSICS_H
#define PHYSICS_H

double dP(float M_r, float r, float rho);
double dT(float L_r, float r, float T, float kappa, float rho);
double rho(float P, float T);
double epsilon(float T, float rho);
double kappa(float T, float rho);
double dM(float r, float rho);
double dL(double dM, double epsilon);



#endif // PHYSICS_H