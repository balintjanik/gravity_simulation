#ifndef SETTINGS_H
#define SETTINGS_H

#include <SFML/Graphics.hpp>
#include "setup_type.h"

// Width and height of screen
const int WIDTH = 1920;
const int HEIGHT = 1080;

// Timestep (speed of animation)
const double TIMESTEP = 0.1;

// Setup type
const PlacementType PLACEMENT_TYPE = PlacementType::Circular;
const SpeedType SPEED_TYPE = SpeedType::Angular;
const int SPAWN_MARGIN = 50; // avoids spawning particles at edge of screen

// Number of particles
const int N = 1000;

// Properties of particles
const int RADIUS = 2;
const double MASS = 2;

// Max force to expect per particle (for coloring purposes only)
const double MAX_FORCES = 3.0;

// Bounce back from edges of screen
const bool HAS_BORDERS = true;

// Trail settings
const bool HAS_TRAIL = false;
const int TRAIL_SIZE = 50;
const double TRAIL_RADIUS = 0.5;
const sf::Color TRAIL_COLOR = sf::Color(40,40,40);

// Collision settings (to fully turn off collision set both to false)
const bool HAS_OVERLAPCHECK = true; // Turns on/off overlap avoidance
const bool HAS_BOUNCEOFF = true; // Turns on/off bounce off when collide (conservation of momentum)
const double COLLISION_THRESHOLD = 0.5; // Amount of space left between particles
const int COLLISION_ITERATIONS = 3; // Amount of collision handles per frame (higher is more accurate handling but more expensive)

// Small damping to avoid uncontrollable velocities (first dampens the angular velocity, then the final calculated velocity again)
// THESE SETTINGS ARE CAREFULLY SET AND NOT ADVISED TO BE CHANGED
const double DAMPING_COEFF = MASS * TIMESTEP / 5;
const double DAMPING_DIST = 2.0;

// Collision optimization settings
const bool VISUALIZE_SPATIAL_GRID = false; // draw grid
const bool VISUALIZE_PARTICLE_CELL = false; // color particle based on position in optimization grid (instead of the forces acting on it)
const bool VISUALIZE_CELL_MASS = false; // color cells based on their mass [ONLY WORKS WITH VISUALIZE_SPATIAL_GRID ON]
const bool VISUALIZE_COM = false; // visualize center of mass of cells [ONLY WORKS WITH VISUALIZE_SPATIAL_GRID ON]
static int id_counter = 0; // DO NOT MODIFY
const int COLLISION_CELL_SIZE = 20; // WARNING: this const must be a divisor of both WIDTH and HEIGHT otherwise program crashes

#endif
