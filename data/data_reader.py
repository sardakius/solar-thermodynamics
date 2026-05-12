import csv
import math

import pygame as pg
import sys

import argparse

import matplotlib.pyplot as plt
import numpy as np

def get_mpl_color(value, cmap_name='inferno'):
    """
    value: 0.0 to 1.0
    Returns: (R, G, B) tuple for Pygame
    """
    cmap = plt.get_cmap(cmap_name)
    rgba = cmap(value) # Returns (r, g, b, a) in 0.0-1.0 range
    return tuple(int(c * 255) for c in rgba[:3])

def parseargs():
    parser = argparse.ArgumentParser()

    parser.add_argument('-t', '--temperature', action='store_true')
    parser.add_argument('-d', '--density', action='store_true')
    parser.add_argument('-p', '--pressure', action='store_true')
    parser.add_argument('-e', '--egr', action='store_true')

    args = parser.parse_args()

    mapping = {
        "temperature": "Temperature",
        "density": "Density",
        "pressure": "Pressure",
        "egr": "Energy Generation Rate"
    }

    active_args = [name for name, value in vars(args).items() if value]

    if len(active_args) == 1:
        data_name = mapping[active_args[0]]
    else:
        data_name = "Temperature"

    return data_name

def draw_plot(n, radius, rk4_data, euler_data, color, data_name):
    plt.figure(n)
    plt.plot(radius, rk4_data, label='RK4', color=color, linestyle='solid')
    plt.plot(radius, euler_data, label='Euler', color=color, linestyle='dashed')
    plt.xlabel('Radius (R⊙)')
    plt.ylabel(data_name)
    plt.title(f'Radius vs {data_name}')
    plt.legend()
    plt.savefig(f'data/profiles/radius_{data_name.lower().replace(" ", "_")}.png')

# This file contains the code to read in the data from the C++ program and plot them while also drawing a cross section of the Sun
# CONSTANTS (SSM)
R_solar = 6.96e8
xi_1 = 6.897
M_solar = 1.989e30
L_solar = 3.828e26
P_core = 2.5e16
T_core = 1.57e7
rho_core = 1.62e5 

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

    # Plotting
    draw_plot(0, radius, rk4_density, euler_density, "orange", "Density")
    draw_plot(1, radius, rk4_pressure, euler_pressure, "blue", "Pressure")
    draw_plot(2, radius, rk4_temperature, euler_temperature, "red", "Temperature")
    draw_plot(3, radius, rk4_mass, euler_mass, "green", "Mass")
    draw_plot(4, radius, rk4_luminosity, euler_luminosity, "purple", "Luminosity")
    draw_plot(5, radius, rk4_egr, euler_egr, "pink", "Energy Generation Rate")

    # Xi vs Theta, Y   
    plt.figure(6)
    plt.plot(xi, rk4_theta, label='θ(ξ) RK4', linestyle='solid', color = 'cyan')
    plt.plot(xi, rk4_y, label='y(ξ) RK4', linestyle='solid', color = 'magenta')

    plt.plot(xi, euler_theta, label='θ(ξ) Euler', linestyle='dashed', color = 'cyan')
    plt.plot(xi, euler_y, label='y(ξ) Euler', linestyle='dashed', color = 'magenta')

    plt.xlabel('ξ/ξ₁')
    plt.ylabel('θ(ξ), y(ξ)')
    plt.title('ξ vs θ(ξ), y(ξ)')
    plt.legend()

    plt.savefig('data/profiles/xi_theta_y.png')
    
pg.init()

screen_size = (1100, 800)
screen = pg.display.set_mode(screen_size)
pg.display.set_caption("The Sun")


data_name = parseargs()

data_set = rk4_temperature if data_name == "Temperature" else rk4_density if data_name == "Density" else rk4_pressure if data_name == "Pressure" else rk4_egr if data_name == "Energy Generation Rate" else rk4_temperature

BLACK = (0, 0, 0)
WHITE = (255, 255, 255)

center_x, center_y = screen_size[0] // 2, screen_size[1] // 2

k = 1.5 # scaling factor to fit the circles within the window
cnv_rad = 1.0 * 500/k # convective zone radius in pixels
rad_rad = 0.7 * 500/k # radiative zone radius in pixels
core_rad = 0.25 * 500/k # core radius in pixels

sun_font = pg.font.SysFont("Cambria", 85, bold=False, italic=False)
sun_surf = sun_font.render("The Sun", False, WHITE)
sun_rect = sun_surf.get_rect(bottomleft=(15, 770))

data_font = pg.font.SysFont("Cambria", 40, bold=False, italic=False)
data_surf = data_font.render(f"{data_name} (RK4)", False, WHITE)
data_rect = data_surf.get_rect(bottomleft=(15, 795))

running = True
while running:
    for event in pg.event.get():
        if event.type == pg.QUIT:
            running = False

    screen.fill(BLACK)

    # text
    screen.blit(sun_surf, sun_rect)
    screen.blit(data_surf, data_rect)

    for radius in range(1, 501):
        pg.draw.circle(screen, get_mpl_color(data_set[radius-1]/data_set[0]), (center_x, center_y), radius/1.5, width=1)

    pg.draw.circle(screen, WHITE, (center_x, center_y), core_rad, width=2)
    pg.draw.circle(screen, WHITE, (center_x, center_y), rad_rad, width=2)
    pg.draw.circle(screen, WHITE, (center_x, center_y), cnv_rad, width=2)
    pg.display.flip()

# 7. Quit pg properly
pg.quit()
sys.exit()