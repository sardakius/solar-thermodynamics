def add_to_arrs(row, mass, luminosity, pressure, temperature, density, egr, theta, y):
    mass.append(float(row['mass']))
    luminosity.append(float(row['luminosity']))
    pressure.append(float(row['pressure']))
    temperature.append(float(row['temperature']))
    density.append(float(row['density']))
    egr.append(float(row['egr']))
    theta.append(float(row['theta']))
    y.append(float(row['y']))

def get_mpl_color(plt, value, cmap_name='inferno'):
    """
    value: 0.0 to 1.0
    Returns: (R, G, B) tuple for Pygame
    """
    cmap = plt.get_cmap(cmap_name)
    rgba = cmap(value) # Returns (r, g, b, a) in 0.0-1.0 range
    return tuple(int(c * 255) for c in rgba[:3])

def parseargs(argparse):
    parser = argparse.ArgumentParser()

    parser.add_argument('-t', '--temperature', action='store_true')
    parser.add_argument('-d', '--density', action='store_true')
    parser.add_argument('-p', '--pressure', action='store_true')
    parser.add_argument('-e', '--egr', action='store_true')
    parser.add_argument('-m', '--mass', action='store_true')
    parser.add_argument('-l', '--luminosity', action='store_true')
    
    args = parser.parse_args()

    mapping = {
        "temperature": ["Temperature", 0, False],
        "density": ["Density", 0, False],
        "pressure": ["Pressure", 0, False],
        "egr": ["Energy Generation Rate", 0, False],
        "mass": ["Mass", 499, True],
        "luminosity": ["Luminosity", 499, True]
    }

    active_args = [name for name, value in vars(args).items() if value]

    if len(active_args) == 1:
        data_name = mapping[active_args[0]][0]
        data_index = mapping[active_args[0]][1]
        differential = mapping[active_args[0]][2]
    else:
        data_name = "Temperature"
        data_index = 0
        differential = False

    return data_name, data_index, differential

def draw_plot(plt, n, radius, rk4_data, euler_data, ssm_data, color, data_name, unit, logscale):
    plt.figure(n)
    plt.plot(radius, rk4_data, label='RK4', color=color, linestyle='solid')
    plt.plot(radius, euler_data, label='Euler', color=color, linestyle='dashed')
    # plt.plot(radius, ssm_data, label='SSM', color=color, linestyle='dotted')
    plt.xlabel('Radius (R⊙)')
    plt.ylabel(f'{data_name} ({unit})')
    plt.title(f'Radius vs {data_name}')
    if logscale:
        plt.yscale('log')
    plt.legend()
    plt.savefig(f'data/profiles/radius_{data_name.lower().replace(" ", "_")}.png')