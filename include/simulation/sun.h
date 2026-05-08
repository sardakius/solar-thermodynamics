#ifndef SUN_H
#define SUN_H

#include "shell.h"
#include "constants.h"

class sun {
    public:
        shell shells[NUM_SHELLS];

        sun();
        void simulate_ssm();
        void simulate_eddington_euler();
        void simulate_eddington_rk4();
        void simulate_eddition_convection();

        shell* get_shells();
};

#endif // SUN_H