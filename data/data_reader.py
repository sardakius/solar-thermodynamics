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

euler = True
rk4 = True

if __name__ == "__main__":
    radius = []
    xi = []

    euler_mass = []
    euler_luminosity = []
    euler_pressure = []
    euler_temperature = []
    euler_density = []
    euler_egr = []
    euler_theta = []
    euler_y = []

    rk4_mass = []
    rk4_luminosity = []
    rk4_pressure = []
    rk4_temperature = []
    rk4_density = []
    rk4_egr = []
    rk4_theta = []
    rk4_y = []

    conv_mass = []
    conv_luminosity = []
    conv_pressure = []
    conv_temperature = []
    conv_density = []
    conv_egr = []
    conv_theta = []
    conv_y = []

    with open('data/data_euler.csv', mode='r') as file:
        reader = csv.DictReader(file)
        for row in reader:
            radius.append(float(row['radius'])/R_solar)
            xi.append(float(row['xi'])/xi_1)
            euler_mass.append(float(row['mass']))
            euler_luminosity.append(float(row['luminosity']))
            euler_pressure.append(float(row['pressure']))
            euler_temperature.append(float(row['temperature']))
            euler_density.append(float(row['density']))
            euler_egr.append(float(row['egr']))
            euler_theta.append(float(row['theta']))
            euler_y.append(float(row['y']))
    
    with open('data/data_rk4.csv', mode='r') as file:
        reader = csv.DictReader(file)
        for row in reader:
            rk4_mass.append(float(row['mass']))
            rk4_luminosity.append(float(row['luminosity']))
            rk4_pressure.append(float(row['pressure']))
            rk4_temperature.append(float(row['temperature']))
            rk4_density.append(float(row['density']))
            rk4_egr.append(float(row['egr']))
            rk4_theta.append(float(row['theta']))
            rk4_y.append(float(row['y']))

    with open('data/data_convection.csv', mode='r') as file:
        reader = csv.DictReader(file)
        for row in reader:
            conv_mass.append(float(row['mass']))
            conv_luminosity.append(float(row['luminosity']))
            conv_pressure.append(float(row['pressure']))
            conv_temperature.append(float(row['temperature']))
            conv_density.append(float(row['density']))
            conv_egr.append(float(row['egr']))
            conv_theta.append(float(row['theta']))
            conv_y.append(float(row['y']))
        
    # Plotting
    plt.figure(0)
    # Radius vs Density
    plt.plot(radius, rk4_density, label='RK4', linestyle='dashed', color = 'orange')
    plt.plot(radius, conv_density, label='Convection', linestyle='solid', color = 'orange')
    plt.xlabel('Radius (R⊙)')   
    plt.ylabel('Density (kg/m^3)')
    plt.title('Radius vs Density')
    plt.legend()

    plt.savefig('data/profiles/radius_density.png')

    plt.figure(1)
    # Radius vs Pressure
    plt.plot(radius, rk4_pressure, label='RK4', linestyle='dashed', color = 'blue')
    plt.plot(radius, conv_pressure, label='Convection', linestyle='solid', color = 'blue')
    plt.xlabel('Radius (R⊙)')
    plt.ylabel('Pressure (Pa)')
    plt.yscale('log')
    plt.title('Radius vs Pressure')
    plt.legend()

    plt.savefig('data/profiles/radius_pressure.png')

    plt.figure(2)
    # Radius vs Temperature
    plt.plot(radius, rk4_temperature, label='RK4', linestyle='dashed', color = 'red')
    plt.plot(radius, conv_temperature, label='Convection', linestyle='solid', color = 'red')
    plt.xlabel('Radius (R⊙)')
    plt.ylabel('Temperature (K)')
    plt.yscale('log')
    plt.title('Radius vs Temperature')
    plt.legend()

    plt.savefig('data/profiles/radius_temperature.png')

    plt.figure(3)
    # Radius vs Mass
    plt.plot(radius, rk4_mass, label='RK4', linestyle='dashed', color = 'green')
    plt.plot(radius, conv_mass, label='Convection', linestyle='solid', color = 'green')
    plt.xlabel('Radius (R⊙)')
    plt.ylabel('Mass (kg)')
    plt.title('Radius vs Mass')
    plt.legend()

    plt.savefig('data/profiles/radius_mass.png')

    plt.figure(4)
    # Radius vs Luminosity
    plt.plot(radius, rk4_luminosity, label='RK4', linestyle='dashed', color = 'purple')
    plt.plot(radius, conv_luminosity, label='Convection', linestyle='solid', color = 'purple')
    plt.xlabel('Radius (R⊙)')
    plt.ylabel('Luminosity (W)')
    plt.title('Radius vs Luminosity')
    plt.legend()

    plt.savefig('data/profiles/radius_luminosity.png')

    plt.figure(5)
    # Radius vs Energy Generation Rate
    plt.plot(radius, rk4_egr, label='RK4', linestyle='dashed', color = 'brown')
    plt.plot(radius, conv_egr, label='Convection', linestyle='solid', color = 'brown')
    plt.xlabel('Radius (R⊙)')
    plt.ylabel('Energy Generation Rate (W/kg)')
    plt.title('Radius vs Energy Generation Rate')
    plt.legend()

    plt.savefig('data/profiles/radius_egr.png')

    plt.figure(6)
    # Xi vs Theta, Y   
    plt.plot(xi, rk4_theta, label='θ(ξ) RK4', linestyle='solid', color = 'cyan')
    plt.plot(xi, rk4_y, label='y(ξ) RK4', linestyle='solid', color = 'magenta')

    plt.xlabel('ξ/ξ₁')
    plt.ylabel('θ(ξ), y(ξ)')
    plt.title('ξ vs θ(ξ), y(ξ)')
    plt.legend()

    plt.savefig('data/profiles/xi_theta_y.png')

    plt.show()

