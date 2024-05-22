#ifndef SETTINGS_H
#define SETTINGS_H

#include <SFML/Graphics.hpp>
#include "simple_button.h"
#include "setup_type.h"

// We will automatically set width and height when the app starts
extern int WIDTH, HEIGHT, CANVAS_WIDTH;
const int MENU_WIDTH = 500;

// Timestep (speed of animation)
const double TIMESTEP = 0.1;

// Setup type
const PlacementType PLACEMENT_TYPE = PlacementType::Circular;
const SpeedType SPEED_TYPE = SpeedType::Angular;
const int SPAWN_MARGIN = 50; // avoids spawning particles at edge of screen
extern int R; // radius of circle in case of PlacementType::Circular (automatically set)

// Number of particles
const int N = 700;

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
const bool VISUALIZE_SPATIAL_GRID = true; // draw grid
const bool VISUALIZE_PARTICLE_CELL = false; // color particle based on position in optimization grid (instead of the forces acting on it)
const bool VISUALIZE_CELL_MASS = true; // color cells based on their mass [ONLY WORKS WITH VISUALIZE_SPATIAL_GRID ON]
const bool VISUALIZE_COM = true; // visualize center of mass of cells [ONLY WORKS WITH VISUALIZE_SPATIAL_GRID ON]
static int id_counter = 0; // DO NOT MODIFY
const int COLLISION_CELL_SIZE = 50; // WARNING: this const must be a divisor of both WIDTH and HEIGHT otherwise program crashes


// Button settings
extern sf::Font FONT;
extern float FONT_SIZE;
const int MARGIN_TOP = 50;
const int MARGIN_LEFT = 20;
const int MARGIN_BOTTOM = 50;
const int MARGIN_RIGHT = 20;
const int MARGIN_BETWEEN = 10;
const int BTN_HEIGHT = 60;

// Buttons
extern RectButton ONOFF_BTN;
extern RectButton EXIT_BTN;
#endif
