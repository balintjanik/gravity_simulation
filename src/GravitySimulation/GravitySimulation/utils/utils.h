#ifndef UTILS_H
#define UTILS_H

#include <SFML/Graphics.hpp>
#include <random>
#include <vector>
#include "../globals/globals.h"
#include "../physics/particle.h"
#include "../globals/settings.h"

class Grid;
class QuadTree;

sf::Color hsv_to_rgb(double H, double S, double V);

sf::Color map_forces_to_color(double all_forces);

double generate_random_double(double min_value, double max_value);

double v2f_distance(sf::Vector2f v1, sf::Vector2f v2);

double map_value(double value, double min_input, double max_input, double min_output, double max_output);

std::vector<Particle> generate_particles(double min_x, double max_x, double min_y, double max_y);

void add_singularity(Grid& collision_grid);

void init_optim_grid(Grid& grid);

int get_idx_by_id(int id);

void handle_move(sf::Vector2f start_position, sf::Vector2f end_position);

void draw_particles(sf::RenderWindow& window, Grid& collision_grid);

void draw_borders(sf::RenderWindow& window);

void draw_quadtree(sf::RenderWindow& window, QuadTree& tree);

#endif
