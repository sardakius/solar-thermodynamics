import matplotlib.pyplot as plt
import numpy as np
import csv

# This file contains the code to read in the data from the C++ program and plot it

# CONSTANTS
R_solar = 6.96e8
xi_1 = 6.897
M_solar = 1.989e30
L_solar = 3.828e26
P_core = 2.5e16
T_core = 1.57e7
rho_core = 1.62e5 

if __name__ == "__main__":
    with open('data/data.csv', mode='r') as file:
        reader = csv.DictReader(file)

        radius = []
        xi = []
        mass = []
        luminosity = []
        pressure = []
        temperature = []
        density = []
        energy_generation_rate = []
        theta = []
        y = []

        
        for row in reader:
            radius.append(float(row['radius'])/R_solar)
            xi.append(float(row['xi'])/xi_1)
            mass.append(float(row['mass']))
            luminosity.append(float(row['luminosity']))
            pressure.append(float(row['pressure']))
            temperature.append(float(row['temperature']))
            density.append(float(row['density']))
            energy_generation_rate.append(float(row['egr']))
            theta.append(float(row['theta']))
            y.append(float(row['y']))
        
        # Plotting
        plt.figure(0)
        # Radius vs Density
        plt.plot(radius, density)
        plt.xlabel('Radius (R⊙)')   
        plt.ylabel('Density (kg/m^3)')
        plt.title('Radius vs Density')

        plt.savefig('data/profiles/radius_density.png')

        plt.figure(1)
        # Radius vs Pressure
        plt.plot(radius, pressure)
        plt.xlabel('Radius (R⊙)')
        plt.ylabel('Pressure (Pa)')
        plt.yscale('log')
        plt.title('Radius vs Pressure')

        plt.savefig('data/profiles/radius_pressure.png')

        plt.figure(2)
        # Radius vs Temperature
        plt.plot(radius, temperature)
        plt.xlabel('Radius (R⊙)')
        plt.ylabel('Temperature (K)')
        plt.yscale('log')
        plt.title('Radius vs Temperature')
        
        plt.savefig('data/profiles/radius_temperature.png')

        plt.figure(3)
        # Radius vs Mass
        plt.plot(radius, mass)
        plt.xlabel('Radius (R⊙)')
        plt.ylabel('Mass (kg)')
        plt.title('Radius vs Mass')

        plt.savefig('data/profiles/radius_mass.png')

        plt.figure(4)
        # Radius vs Luminosity
        plt.plot(radius, luminosity)
        plt.xlabel('Radius (R⊙)')
        plt.ylabel('Luminosity (W)')
        plt.title('Radius vs Luminosity')

        plt.savefig('data/profiles/radius_luminosity.png')

        plt.figure(5)
        # Radius vs Energy Generation Rate
        plt.plot(radius, energy_generation_rate)
        plt.xlabel('Radius (R⊙)')
        plt.ylabel('Energy Generation Rate (W/kg)')
        plt.title('Radius vs Energy Generation Rate')

        plt.savefig('data/profiles/radius_egr.png')

        plt.figure(6)
        # Xi vs Theta, Y   
        plt.plot(xi, theta, label='θ(ξ)')
        plt.plot(xi, y, label='y(ξ)')  
        plt.xlabel('ξ/ξ₁')
        plt.ylabel('θ(ξ), y(ξ)')
        plt.title('ξ vs θ(ξ), y(ξ)')
        plt.legend()

        plt.savefig('data/profiles/xi_theta_y.png')

        plt.show()
