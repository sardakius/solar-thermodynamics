#ifndef SHELL_H
#define SHELL_H

struct shell
{
    // non-eddington
    double radius;
    double energy_generation_rate;
    double absorption;
    double mass;
    double luminosity;
    double pressure;
    double temperature;
    double density;
    
    // eddington model
    double xi;
    double theta;
    double y;
};

#endif // SHELL_H