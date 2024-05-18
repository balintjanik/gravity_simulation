#ifndef UTILS_H
#define UTILS_H

#include <SFML/Graphics.hpp>
#include <vector>
#include "particle.h"
#include "grid.h"

sf::Color hsv_to_rgb(float H, float S, float V);

sf::Color map_forces_to_color(float all_forces);

float generate_random_float(float min_value, float max_value);

float v2f_distance(sf::Vector2f v1, sf::Vector2f v2);

float map_value(float value, float min_input, float max_input, float min_output, float max_output);

std::vector<Particle> generate_particles(float min_x, float max_x, float min_y, float max_y);

void init_collision_grid(std::vector<Particle>& particles, Grid& collision_grid);

int get_idx_by_id(std::vector<Particle>& particles, int id);

#endif
