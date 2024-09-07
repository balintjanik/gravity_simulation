#include "settings.h"

int WIDTH = 500;
int HEIGHT = 500;
int CANVAS_WIDTH = WIDTH - MENU_WIDTH;

bool SHOW_MENU = true;
bool SHOW_HELP = true;
bool SHOW_PERFORMANCE = true;

sf::Vector2f delta_move(0, 0);
sf::Vector2f map_offset(0, 0);
sf::Vector2f final_limit(0, 0);
double zoom = 1.0;

unsigned int GRAV_CALC_COUNT = 0;
unsigned int QUADTREE_DEPTH = 0;
unsigned int QUADTREE_NODES = 0;
unsigned int QUADTREE_LEAVES = 0;
unsigned int COLL_CALC_COUNT = 0;
