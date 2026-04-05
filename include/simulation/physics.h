#ifndef PHYSICS_H
#define PHYSICS_H

float dP(float M_r, float r, float rho);
float dT(float L_r, float r, float T, float kappa, float rho);
float rho(float P, float T);
float epsilon(float T, float rho);
float kappa(float T, float rho);
float dM(float r, float rho);
float dL(float dM, float epsilon);



#endif // PHYSICS_H