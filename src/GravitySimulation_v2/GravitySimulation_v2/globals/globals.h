#ifndef GLOBALS_H
#define GLOBALS_H

#include <vector>
#include "../physics/particle.h"

class Grid;

extern std::vector<Particle> particles;

extern Settings settings;
extern Settings current_settings;

extern Grid optim_grid;

#endif
