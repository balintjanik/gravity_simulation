#ifndef PHYSICS_H
#define PHYSICS_H

#include <SFML/Graphics.hpp>

#include <vector>
#include <thread>

#include "particle.h"
#include "../grid/grid.h"
#include "../utils/double_vector_ops.h"
#include "../quadtree/quadtree.h"

// Gravity with quadtree

void update_gravity_quadtree_range(QuadTree& gravity_tree, int start, int end);

void update_gravity_quadtree(sf::RenderWindow& window);

// Gravity with static grid - UNUSED FOR NOW
// Note: when added option to switch between quadtree and static grid
//		 gravity calculation, the performance of the quadtree decreased
//		 when switched to grid and then back to quadtree. Could not find
//		 the source of problem, so removed this option for now

void update_gravity_range(Grid& optim_grid, int start, int end);

void update_gravity(Grid& optim_grid);

// Discrete collision with static grid

void check_cells_collision(Cell& cell_1, Cell& cell_2);

void update_collisions_range(Grid& collision_grid, int start, int stride);

void update_collisions(Grid& collision_grid);

// Trails

void update_trails();

// Overall update

void update_positions(Grid& collision_grid, sf::RenderWindow& window);

#endif
