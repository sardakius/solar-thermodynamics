#include <iostream>
#include <fstream>
#include <simulation/physics.h>
#include <simulation/sun.h>
#include <simulation/shell.h>

using namespace std; 

void write_data(shell* shells, string filename) {
    ofstream fout;
    fout.open(filename);

    // write the headers
    if (fout.is_open()) {
        fout << "radius,xi,mass,luminosity,pressure,temperature,density,egr,theta,y\n";
        for (int i = 0; i <= NUM_SHELLS - 1; i++) {
            fout << shells[i].radius << "," << shells[i].xi << "," << shells[i].mass << "," << shells[i].luminosity << "," << shells[i].pressure << "," << shells[i].temperature << "," << shells[i].density << "," << shells[i].energy_generation_rate << "," << shells[i].theta << "," << shells[i].y << "\n";    
        }
        cout << "Data written to " << filename << endl;
        fout.close();
    } else {
        cout << "Failed to open file for writing" << endl;
    }
}

int main()
{
    sun Sun_Euler = sun();
    Sun_Euler.simulate_eddington_euler();
    shell* shells_euler = Sun_Euler.get_shells();

    sun Sun_RK4 = sun();
    Sun_RK4.simulate_eddington_rk4();
    shell* shells_rk4 = Sun_RK4.get_shells();

    write_data(shells_euler, "data/data_euler.csv");
    write_data(shells_rk4, "data/data_rk4.csv");
}