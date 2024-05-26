#include "settings.h"

int WIDTH = 500;
int HEIGHT = 500;
int CANVAS_WIDTH = WIDTH - MENU_WIDTH;

sf::Font FONT;
ToggleButton ONOFF_BTN(sf::Vector2f(0, 0), sf::Vector2f(0, 0));
SimpleButton RELOAD_BTN(sf::Vector2f(0, 0), sf::Vector2f(0, 0));
SimpleButton EXIT_BTN(sf::Vector2f(0, 0), sf::Vector2f(0, 0));