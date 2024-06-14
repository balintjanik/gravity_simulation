#ifndef SETTINGS_H
#define SETTINGS_H

#include <SFML/Graphics.hpp>
#include "simple_button.h"
#include "toggle_button.h"
#include "textbox.h"
#include "setup_type.h"

// We will automatically set width and height when the app starts
extern int WIDTH, HEIGHT, CANVAS_WIDTH;
static int MENU_WIDTH = 500;

// Button settings
extern sf::Font FONT;
const float FONT_SIZE = 15;
const int MARGIN_TOP = 20;
const int MARGIN_LEFT = 15;
const int MARGIN_BOTTOM = 30;
const int MARGIN_RIGHT = 15;
const int MARGIN_BETWEEN = 10;
const int BTN_HEIGHT = 30;

// Buttons
static sf::Text PARTICLE_NUM_TXT;
extern TextBox PARTICLE_NUM_TB;

static sf::Text PARTICLE_PROPS_TXT;
static sf::Text PARTICLE_RADIUS_TXT;
extern TextBox PARTICLE_RADIUS_TB;
static sf::Text PARTICLE_MASS_TXT;
extern TextBox PARTICLE_MASS_TB;

static sf::Text PLACEMENT_TYPE_TXT;
extern ToggleButton PLACEMENT_TYPE_FULLSCREEN_BTN;
extern ToggleButton PLACEMENT_TYPE_CIRCULAR_BTN;

static sf::Text SPEED_TYPE_TXT;
extern ToggleButton SPEED_TYPE_RANDOM_BTN;
extern ToggleButton SPEED_TYPE_ANGULAR_BTN;
extern ToggleButton SPEED_TYPE_ZERO_BTN;
extern ToggleButton SPEED_TYPE_CENTRAL_BTN;

static sf::Text BORDER_TXT;
extern ToggleButton HAS_BORDERS_BTN;

static sf::Text TRAIL_TXT;
extern ToggleButton HAS_TRAIL_BTN;

static sf::Text GRAVITY_TXT;
extern ToggleButton HAS_GRAVITY_BTN;

static sf::Text COLLISION_TXT;
extern ToggleButton HAS_OVERLAPCHECK_BTN;
extern ToggleButton HAS_BOUNCEOFF_BTN;

static sf::Text GRID_TXT;
extern ToggleButton VISUALIZE_GRID_BTN;
extern ToggleButton VISUALIZE_PARTICLE_CELL_BTN;
extern ToggleButton VISUALIZE_CELL_MASS_BTN;
extern ToggleButton VISUALIZE_COM_BTN;

static sf::Text RELOAD_REQUIRED_TXT;
extern SimpleButton RELOAD_BTN;
extern SimpleButton EXIT_BTN;

class Settings {
public:
	// Timestep (speed of animation)
	double TIMESTEP = 0.1;
	
	// Setup type
	PlacementType PLACEMENT_TYPE = PlacementType::Circular;
	SpeedType SPEED_TYPE = SpeedType::Angular;
	int SPAWN_MARGIN = 50; // avoids spawning particles at edge of screen
	int R = 400; // radius of circle in case of PlacementType::Circular (automatically set)
	
	// Number of particles
	int N = 700;
	
	// Properties of particles
	int RADIUS = 2;
	double MASS = 2;
	
	// Max force to expect per particle (for coloring purposes only)
	double MAX_FORCES = 3.0;
	
	// Bounce back from edges of screen
	bool HAS_BORDERS = true;
	
	// Trail settings
	bool HAS_TRAIL = false;
	int TRAIL_SIZE = 50;
	double TRAIL_RADIUS = 0.5;
	sf::Color TRAIL_COLOR = sf::Color(40,40,40);

	// Gravity settings
	bool HAS_GRAVITY = true;
	
	// Collision settings (to fully turn off collision set both to false)
	bool HAS_OVERLAPCHECK = true; // Turns on/off overlap avoidance
	bool HAS_BOUNCEOFF = true; // Turns on/off bounce off when collide (conservation of momentum)
	double COLLISION_THRESHOLD = 0.5; // Amount of space left between particles
	int COLLISION_ITERATIONS = 3; // Amount of collision handles per frame (higher is more accurate handling but more expensive)
	
	// Small damping to avoid uncontrollable velocities (first dampens the angular velocity, then the final calculated velocity again)
	// THESE SETTINGS ARE CAREFULLY SET AND NOT ADVISED TO BE CHANGED
	double DAMPING_COEFF = MASS * TIMESTEP / 5;
	double DAMPING_DIST = 2.0;
	
	// Collision optimization settings
	bool VISUALIZE_SPATIAL_GRID = false; // draw grid
	bool VISUALIZE_PARTICLE_CELL = false; // color particle based on position in optimization grid (instead of the forces acting on it)
	bool VISUALIZE_CELL_MASS = false; // color cells based on their mass [ONLY WORKS WITH VISUALIZE_SPATIAL_GRID ON]
	bool VISUALIZE_COM = false; // visualize center of mass of cells [ONLY WORKS WITH VISUALIZE_SPATIAL_GRID ON]
	int COLLISION_CELL_SIZE = 20;
};

#endif
