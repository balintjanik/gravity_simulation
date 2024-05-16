#ifndef SETTINGS_H
#define SETTINGS_H

#include <SFML/Graphics.hpp>
#include "setup_type.h"

// Width and height of screen
const int WIDTH = 1900;
const int HEIGHT = 1100;

// Timestep (speed of animation)
const float TIMESTEP = 0.005f;

// Setup type
const PlacementType PLACEMENT_TYPE = PlacementType::Circular;
const SpeedType SPEED_TYPE = SpeedType::Angular;

// Number of particles
const int N = 500;

// Properties of particles
const int RADIUS = 1;
const float MASS = 2;

// Max force to expect per particle (for coloring purposes only)
const float MAX_FORCES = 3.0f;

// Bounce back from edges of screen
const bool HAS_BORDERS = true;

// Trail settings
const bool HAS_TRAIL = false;
const int TRAIL_SIZE = 50;
const float TRAIL_RADIUS = 0.5f;
const sf::Color TRAIL_COLOR = sf::Color(40,40,40);

// Collision settings (to fully turn off collision set both to false)
const bool HAS_OVERLAPCHECK = true; // Turns on/off overlap avoidance
const bool HAS_BOUNCEOFF = true; // Turns on/off bounce off when collide (conservation of momentum)
const float COLLISION_THRESHOLD = 0.5f; // Amount of space left between particles

// Small damping to avoid uncontrollable velocities (first dampens the angular velocity, then the final calculated velocity again)
// THESE SETTINGS ARE CAREFULLY SET AND NOT ADVISED TO BE CHANGED
const float DAMPING_COEFF = MASS * TIMESTEP / 10;
const float DAMPING_DIST = 2.0f;

// for collision optimization
static int id_counter = 0;
const int COLLISION_CELL_SIZE = 50; // WARNING: this const must be a divisor of both WIDTH and HEIGHT otherwise program crashes

#endif
