#include <include/constants.h>
#include <include/simulation/shell.h>
#include <cmath>

using namespace std;

class sun {
    public: 
        shell shells[NUM_SHELLS + 1];

        sun();
        void simulate();

        shell* get_shells() {
            return shells;
        };
};

sun::sun() {
    // initialize the shells
    for (int i = 0; i <= NUM_SHELLS; i++) {
        shells[i].radius = dr * i;
        shells[i].mass = 0.0f;
        shells[i].luminosity = 0.0f;
        shells[i].temperature = 0.0f;
        shells[i].density = 0.0f;
        shells[i].pressure = 0.0f;
    }

    // initialize the core
    shells[0].radius = 0.0f;
    shells[0].temperature = SOLAR_CORE_TEMPERATURE;
    shells[0].density = SOLAR_CORE_DENSITY;
    shells[0].pressure = SOLAR_CORE_PRESSURE;

    shells[0].mass = (4.0f / 3.0f) * PI * pow(dr, 3) * shells[0].density;
}