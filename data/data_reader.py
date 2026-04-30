import matplotlib.pyplot as plt
import numpy as np
import csv

# This file contains the code to read in the data from the C++ program and plot it

if __name__ == "__main__":
    with open('data/data.csv', mode='r') as file:
        reader = csv.DictReader(file)
        for row in reader:
            plt.plot(float(row['xi'])/(6.897), float(row['mass'])/(1.989e30), 'o')
            plt.xlabel('radius (solar radii)')
            plt.ylabel('mass (solar masses)')
            plt.savefig('data/profiles/mass_radius.png')
    plt.show()
