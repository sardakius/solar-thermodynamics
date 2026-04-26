#ifndef SUN_H
#define SUN_H

#include "shell.h"
#include "constants.h"

class sun {
    public:
        shell shells[NUM_SHELLS];

        sun();
        void simulate();
        void simulate_eddington();

        shell* get_shells();
};

#endif // SUN_H