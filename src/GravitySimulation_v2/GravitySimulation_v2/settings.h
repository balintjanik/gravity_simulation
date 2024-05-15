#ifndef SETTINGS_H
#define SETTINGS_H

#include <SFML/Graphics.hpp>

// width and height of screen
const int WIDTH = 1920;
const int HEIGHT = 1080;

// timestep (speed of animation)
const float TIMESTEP = 0.1f;

// number of particles
const int N = 500;

// properties of particles
const int RADIUS = 2;
const float MASS = 1;

// max force to expect per particle (for coloring purposes only)
const float MAX_FORCES = 0.9f;

// bounce back from edges of screen
const bool HAS_BORDERS = true;

// trail settings
const bool HAS_TRAIL = false;
const int TRAIL_SIZE = 50;
const float TRAIL_RADIUS = 1;
const sf::Color TRAIL_COLOR = sf::Color(40,40,40);

// small damping to avoid uncontrollable velocities
const float DAMPING_COEFF = 0.1f;


#endif
