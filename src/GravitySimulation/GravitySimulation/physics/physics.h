#ifndef PHYSICS_H
#define PHYSICS_H

#include <SFML/Graphics.hpp>

#include <vector>
#include <thread>

#include "particle.h"
#include "../grid/grid.h"
#include "../utils/double_vector_ops.h"
#include "../quadtree/quadtree.h"

void update_positions(Grid& optim_grid, sf::RenderWindow& window);

void update_gravity_range(Grid& optim_grid, int start, int end);

void update_gravity(Grid& optim_grid);

void update_gravity_quadtree(sf::RenderWindow& window);

void check_cells_collision(Cell& cell_1, Cell& cell_2);

void update_collisions_range(Grid& optim_grid, int start, int stride);

void update_collisions(Grid& optim_grid);

void update_trails();
#endif
