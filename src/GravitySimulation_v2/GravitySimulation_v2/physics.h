#ifndef PHYSICS_H
#define PHYSICS_H

#include <SFML/Graphics.hpp>

#include <vector>

#include "particle.h"
#include "grid.h"
#include "utils.h"
#include "double_vector_ops.h"

void update_positions(std::vector<Particle>& particles, Grid& collision_grid);

void update_gravity(std::vector<Particle>& particles);

void check_cells_collision(std::vector<Particle>& particles, Cell& cell_1, Cell& cell_2);

void update_collisions(std::vector<Particle>& particles, Grid& collision_grid);

void update_trails(std::vector<Particle>& particles);
#endif
