import matplotlib.pyplot as plt
import numpy as np
import csv

# This file contains the code to read in the data from the C++ program and plot it

if __name__ == "__main__":
    with open('data/data.csv', mode='r') as file:
        reader = csv.DictReader(file)
        for row in reader:
            plt.plot(float(row['xi'])/(6.897), float(row['luminosity']), 'o')

        plt.xlabel('Radius (solar radii)')
        plt.ylabel('Luminosity (W)')
        plt.savefig('data/profiles/Radius_Luminosity.png')
        plt.show()