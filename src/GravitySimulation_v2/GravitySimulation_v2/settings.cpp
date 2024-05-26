#include "settings.h"

int WIDTH = 500;
int HEIGHT = 500;
int CANVAS_WIDTH = WIDTH - MENU_WIDTH;

sf::Font FONT;

ToggleButton PLACEMENT_TYPE_FULLSCREEN_BTN(sf::Vector2f(0, 0), sf::Vector2f(0, 0));
ToggleButton PLACEMENT_TYPE_CIRCULAR_BTN(sf::Vector2f(0, 0), sf::Vector2f(0, 0));

ToggleButton SPEED_TYPE_RANDOM_BTN(sf::Vector2f(0, 0), sf::Vector2f(0, 0));
ToggleButton SPEED_TYPE_ANGULAR_BTN(sf::Vector2f(0, 0), sf::Vector2f(0, 0));
ToggleButton SPEED_TYPE_ZERO_BTN(sf::Vector2f(0, 0), sf::Vector2f(0, 0));
ToggleButton SPEED_TYPE_CENTRAL_BTN(sf::Vector2f(0, 0), sf::Vector2f(0, 0));

ToggleButton HAS_BORDERS_BTN(sf::Vector2f(0, 0), sf::Vector2f(0, 0));

ToggleButton HAS_TRAIL_BTN(sf::Vector2f(0, 0), sf::Vector2f(0, 0));

ToggleButton HAS_OVERLAPCHECK_BTN(sf::Vector2f(0, 0), sf::Vector2f(0, 0));
ToggleButton HAS_BOUNCEOFF_BTN(sf::Vector2f(0, 0), sf::Vector2f(0, 0));

ToggleButton VISUALIZE_GRID_BTN(sf::Vector2f(0, 0), sf::Vector2f(0, 0));
ToggleButton VISUALIZE_PARTICLE_CELL_BTN(sf::Vector2f(0, 0), sf::Vector2f(0, 0));
ToggleButton VISUALIZE_CELL_MASS_BTN(sf::Vector2f(0, 0), sf::Vector2f(0, 0));
ToggleButton VISUALIZE_COM_BTN(sf::Vector2f(0, 0), sf::Vector2f(0, 0));

ToggleButton ONOFF_BTN(sf::Vector2f(0, 0), sf::Vector2f(0, 0));
SimpleButton RELOAD_BTN(sf::Vector2f(0, 0), sf::Vector2f(0, 0));
SimpleButton EXIT_BTN(sf::Vector2f(0, 0), sf::Vector2f(0, 0));