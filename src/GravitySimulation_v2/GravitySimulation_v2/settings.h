#ifndef SETTINGS_H
#define SETTINGS_H

#include <SFML/Graphics.hpp>

// width and height of screen
const int width = 1200;
const int height = 800;

// timestep (speed of animation)
const float timestep = 0.05f;

// number of particles
const int n = 200;

// properties of particles
const int radius = 2;
const float mass = 1;

// max force to expect per particle (for coloring purposes only)
const float max_forces = 0.9f;

// bounce back from edges of screen
const bool has_borders = true;

// trail settings
const bool has_trail = true;
const int trail_size = 50;
const float trail_radius = 1;
const sf::Color trail_color = sf::Color(40,40,40);

#endif
