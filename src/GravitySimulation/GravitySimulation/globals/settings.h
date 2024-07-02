#ifndef SETTINGS_H
#define SETTINGS_H

#include <SFML/Graphics.hpp>
#include <thread>
#include "../ui/simple_button.h"
#include "../ui/toggle_button.h"
#include "../ui/textbox.h"
#include "setup_type.h"

// We will automatically set width and height when the app starts
extern int WIDTH, HEIGHT, CANVAS_WIDTH;
static int MENU_WIDTH = 500;

// Constants
const unsigned int MAX_THREAD_NUM = std::thread::hardware_concurrency(); // Maximum threads available on device

const double EPSYLON = 1.8; // Softening length to avoid singularities

const sf::Color SINGULARITY_COLOR = sf::Color(255, 127, 0);
const int SINGULARITY_RADIUS = 9;
const int SINGULARITY_OUTLINE_THICKNESS = 3;

// Show/hide settings and hotkeys
static sf::Keyboard::Key RELOAD_KEY = sf::Keyboard::R;

static sf::Keyboard::Key SINGULARITY_KEY = sf::Keyboard::B;

static bool SHOW_MENU = true;
static sf::Keyboard::Key SHOW_MENU_KEY = sf::Keyboard::M;

static bool SHOW_HELP = true;
static sf::Keyboard::Key SHOW_HELP_KEY = sf::Keyboard::H;

static bool SHOW_PERFORMANCE = true;
static sf::Keyboard::Key SHOW_PERFORMANCE_KEY = sf::Keyboard::P;

static sf::Keyboard::Key SHOW_ALL_KEY = sf::Keyboard::A;

static sf::Keyboard::Key EXIT_KEY = sf::Keyboard::Escape;

// Help settings
static sf::Text HELP_TXT;
static sf::Text HELP2_TXT;

// FPS settings
static unsigned int M_FRAME = 0;
static unsigned int M_FPS;
static sf::Clock M_CLOCK;
static sf::Text FPS_TXT;

// Performance
extern unsigned int GRAV_CALC_COUNT;
static sf::Text GRAV_COUNT_TXT;
extern unsigned int QUADTREE_DEPTH;
static sf::Text QUADTREE_DEPTH_TXT;
extern unsigned int QUADTREE_NODES;
static sf::Text QUADTREE_NODES_TXT;
extern unsigned int QUADTREE_LEAVES;
static sf::Text QUADTREE_LEAVES_TXT;
extern unsigned int COLL_CALC_COUNT;
static sf::Text COLL_COUNT_TXT;

// Menu settings
static sf::Font FONT;
static float TITLE_FONT_SIZE = 25;
static float FONT_SIZE = 15;
static int MARGIN_TOP = 20;
static int MARGIN_LEFT = 15;
static int MARGIN_BOTTOM = 30;
static int MARGIN_RIGHT = 15;
static int MARGIN_BETWEEN = 10;
static int MARGIN_BLOCK = 20;
static int BTN_HEIGHT = 30;

// Left menu
static sf::Text SIMULATION_TITLE;

static sf::Text PARTICLE_NUM_TXT;
static TextBox PARTICLE_NUM_TB;

static sf::Text PARTICLE_PROPS_TXT;
static sf::Text PARTICLE_RADIUS_TXT;
static TextBox PARTICLE_RADIUS_TB;
static sf::Text PARTICLE_MASS_TXT;
static TextBox PARTICLE_MASS_TB;

static sf::Text SINGULARITY_MASS_TXT;
static TextBox SINGULARITY_MASS_TB;

static sf::Text PLACEMENT_TYPE_TXT;
static ToggleButton PLACEMENT_TYPE_FULLSCREEN_BTN;
static ToggleButton PLACEMENT_TYPE_CIRCULAR_BTN;
static sf::Text PLACEMENT_RADIUS_TXT;
static TextBox PLACEMENT_RADIUS_TB;
static sf::Text SPAWN_MARGIN_TXT;
static TextBox SPAWN_MARGIN_TB;

static sf::Text SPEED_TYPE_TXT;
static ToggleButton SPEED_TYPE_RANDOM_BTN;
static ToggleButton SPEED_TYPE_ANGULAR_BTN;
static ToggleButton SPEED_TYPE_ZERO_BTN;
static ToggleButton SPEED_TYPE_GALAXY_BTN;

static sf::Text BORDER_TXT;
static ToggleButton HAS_BORDERS_BTN;

static sf::Text GRAVITY_TXT;
static ToggleButton HAS_GRAVITY_BTN;

static sf::Text DAMPING_TXT;
static ToggleButton HAS_DAMPING_BTN;
static sf::Text DAMPING_DIST_TXT;
static TextBox DAMPING_DIST_TB;
static sf::Text DAMPING_COEFF_TXT;
static TextBox DAMPING_COEFF_TB;

static sf::Text COLLISION_TXT;
static ToggleButton HAS_COLLISIONS_BTN;
static sf::Text COLLISION_THRESHOLD_TXT;
static TextBox COLLISION_THRESHOLD_TB;
static sf::Text COLLISION_ITERATIONS_TXT;
static TextBox COLLISION_ITERATIONS_TB;
static sf::Text COLLISION_IMPULSE_COEFF_TXT;
static TextBox COLLISION_IMPULSE_COEFF_TB;

static sf::Text RELOAD_REQUIRED_TXT;
static SimpleButton RELOAD_BTN;

// Right menu
static sf::Text DISPLAY_TITLE;

static sf::Text ANIMATION_SETTINGS_TXT;
static sf::Text TIMESTEP_TXT;
static TextBox TIMESTEP_TB;
static unsigned int DEFAULT_FPS_LIMIT = 30;
static sf::Text FPS_LIMIT_TXT;
static TextBox FPS_LIMIT_TB;

static sf::Text TRAIL_TXT;
static ToggleButton HAS_TRAIL_BTN;

static sf::Text OPTIMIZATION_TITLE;
static sf::Text COLLISION_OPTIMIZATION_TXT;
static ToggleButton VISUALIZE_GRID_BTN;
static ToggleButton VISUALIZE_PARTICLE_CELL_BTN;
static ToggleButton VISUALIZE_CELL_MASS_BTN;
static ToggleButton VISUALIZE_COM_BTN;
static sf::Text COLLISION_CELL_SIZE_TXT;
static TextBox COLLISION_CELL_SIZE_TB;

static sf::Text GRAVITY_OPTIMIZATION_TXT;
static ToggleButton VISUALIZE_GRAVITY_TREE_BTN;
static sf::Text QUADTREE_THETA_TXT;
static TextBox QUADTREE_THETA_TB;

static sf::Text MULTITHREADING_TXT;
static sf::Text THREAD_NUM_TXT;
static TextBox THREAD_NUM_TB;

static sf::Text AUDIO_TITLE;
static sf::Text SOUND_TXT;
static ToggleButton SOUND_BTN;
static TextBox SOUND_VOLUME_TB;
static sf::Text MUSIC_TXT;
static ToggleButton MUSIC_BTN;
static TextBox MUSIC_VOLUME_TB;

static SimpleButton EXIT_BTN;

class Settings {
public:
	// Timestep (speed of animation)
	double TIMESTEP = 0.5;
	
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
	double MAX_FORCES = 3 * sqrt(MASS) * (N / 700);
	
	// Bounce back from edges of screen
	bool HAS_BORDERS = true;
	
	// Trail settings
	bool HAS_TRAIL = false;
	int TRAIL_SIZE = 20;
	double TRAIL_RADIUS = (RADIUS / 2 > 1 ? RADIUS / 2 : 1);
	sf::Color TRAIL_COLOR = sf::Color(40,40,40);

	// Gravity settings
	bool HAS_GRAVITY = true;
	
	// Collision settings
	bool HAS_COLLISIONS = true;
	double COLLISION_THRESHOLD = 0.5; // Amount of space left between particles
	int COLLISION_ITERATIONS = 3; // Amount of collision handles per frame (higher is more accurate handling but more expensive)
	double COLLISION_IMPULSE_COEFF = 1.0; // Strength of bounceoff (0.0-2.0)

	// Small damping to avoid uncontrollable velocities (first dampens the angular velocity, then the final calculated velocity again)
	// THESE SETTINGS ARE CAREFULLY SET AND NOT ADVISED TO BE CHANGED
	bool HAS_DAMPING = true;
	double DAMPING_COEFF = MASS * TIMESTEP / 5;
	double DAMPING_DIST = 2.0;
	
	// Collision optimization settings
	bool VISUALIZE_COLLISION_GRID = false; // draw grid
	bool VISUALIZE_COLLISION_PARTICLE_CELL = false; // color particle based on position in optimization grid (instead of the forces acting on it)
	bool VISUALIZE_COLLISION_CELL_MASS = false; // color cells based on their mass [ONLY WORKS WITH VISUALIZE_COLLISION_GRID ON]
	bool VISUALIZE_COLLISION_COM = false; // visualize center of mass of cells [ONLY WORKS WITH VISUALIZE_COLLISION_GRID ON]
	int COLLISION_CELL_SIZE = 20;

	// Gravity optimization settings
	bool IS_GRAVITY_QUADTREE = true;
	bool VISUALIZE_GRAVITY_TREE = false;
	double THETA = 0.5;

	// Max threads
	unsigned int THREAD_NUM = 4; // TODO: textbox for this

	// Singularity mass
	double SINGULARITY_MASS = 10000;

	// FPS limit
	int FPS_LIMIT = DEFAULT_FPS_LIMIT;

	// Sound and music settings
	bool HAS_SOUND = true;
	int SOUND_VOLUME = 100;
	bool HAS_MUSIC = true;
	int MUSIC_VOLUME = 100;

	void update_dynamic_properties()
	{
		MAX_FORCES = 3 * sqrt(MASS) * ((double)N / 700);
		TRAIL_RADIUS = (RADIUS / 2 > 1 ? RADIUS / 2 : 1);
		update_damping_coeff();
		THREAD_NUM = (THREAD_NUM > MAX_THREAD_NUM ? MAX_THREAD_NUM : THREAD_NUM);
	}

	void update_damping_coeff()
	{
		DAMPING_COEFF = MASS * TIMESTEP / 20;
	}
};

#endif
