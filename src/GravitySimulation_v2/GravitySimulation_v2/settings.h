#ifndef SETTINGS_H
#define SETTINGS_H

#include <SFML/Graphics.hpp>
#include "setup_type.h"

// Width and height of screen
const int WIDTH = 1920;
const int HEIGHT = 1080;

// Timestep (speed of animation)
const float TIMESTEP = 0.005f;

// Setup type
const PlacementType PLACEMENT_TYPE = PlacementType::Fullscreen;
const SpeedType SPEED_TYPE = SpeedType::Zero;

// Number of particles
const int N = 500;

// Properties of particles
const int RADIUS = 1;
const float MASS = 1;

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
const float DAMPING_COEFF = MASS * TIMESTEP / 4;
const float DAMPING_DIST = 2.0f;

#endif
