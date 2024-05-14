#ifndef UTILS_H
#define UTILS_H

#include <SFML/Graphics.hpp>
#include <vector>
#include "particle.h"

sf::Color HSVtoRGB(float H, float S, float V);

sf::Color mapForcesToColor(float all_forces);

float generateRandomFloat(float min_value, float max_value);

std::vector<Particle> generateParticles(float min_x, float max_x, float min_y, float max_y);

#endif
