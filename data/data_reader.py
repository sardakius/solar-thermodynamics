import csv
import math

import pygame as pg
import sys

import argparse

import matplotlib.pyplot as plt
import numpy as np

from data_reader_util import *

# This file contains the code to read in the data from the C++ program and plot them while also drawing a cross section of the Sun

# CONSTANTS (SSM)
R_solar = 6.96e8
xi_1 = 6.897

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
            add_to_arrs(row, euler_mass, euler_luminosity, euler_pressure, euler_temperature, euler_density, euler_egr, euler_theta, euler_y)

    with open('data/data_rk4.csv', mode='r') as file:
        reader = csv.DictReader(file)
        for row in reader:
            add_to_arrs(row, rk4_mass, rk4_luminosity, rk4_pressure, rk4_temperature, rk4_density, rk4_egr, rk4_theta, rk4_y)

    # Plotting
    draw_plot(plt, 0, radius, rk4_density, euler_density, "orange", "Density", "kg/m³", True)
    draw_plot(plt, 1, radius, rk4_pressure, euler_pressure, "blue", "Pressure", "Pa", True)
    draw_plot(plt, 2, radius, rk4_temperature, euler_temperature, "red", "Temperature", "K", False)
    draw_plot(plt, 3, radius, rk4_mass, euler_mass, "green", "Mass", "kg", False)
    draw_plot(plt, 4, radius, rk4_luminosity, euler_luminosity, "purple", "Luminosity", "W", False)
    draw_plot(plt, 5, radius, rk4_egr, euler_egr, "pink", "Energy Generation Rate", "W/kg", False)

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

data_name = parseargs(argparse)
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

    # draw cross-section shells with colors based on the data values
    for radius in range(1, 501):
        pg.draw.circle(screen, get_mpl_color(plt, data_set[radius-1]/data_set[0]), (center_x, center_y), radius/1.5, width=1)

    # core, radiative zone, convective zone boundaries
    pg.draw.circle(screen, WHITE, (center_x, center_y), core_rad, width=2)
    pg.draw.circle(screen, WHITE, (center_x, center_y), rad_rad, width=2)
    pg.draw.circle(screen, WHITE, (center_x, center_y), cnv_rad, width=2)
    pg.display.flip()

pg.quit()
sys.exit()