#ifndef PHYSICS_H
#define PHYSICS_H

#include <SFML/Graphics.hpp>

#include <vector>

#include "particle.h"
#include "grid.h"
#include "double_vector_ops.h"

void update_positions(Grid& optim_grid);

void update_gravity(Grid& optim_grid);

void check_cells_collision(Cell& cell_1, Cell& cell_2);

void update_collisions(Grid& optim_grid);

void update_trails();
#endif
