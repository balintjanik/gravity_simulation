#include "globals.h"
#include "../grid/grid.h"

std::vector<Particle> particles;

Settings settings;
Settings current_settings;

Grid optim_grid(settings.COLLISION_CELL_SIZE);