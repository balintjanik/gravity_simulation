#include "settings.h"

int WIDTH = 1920;
int HEIGHT = 1080;
int CANVAS_WIDTH = WIDTH - MENU_WIDTH;

sf::Font FONT;
float FONT_SIZE;
ToggleButton ONOFF_BTN(sf::Vector2f(0, 0), sf::Vector2f(0, 0));
SimpleButton EXIT_BTN(sf::Vector2f(0, 0), sf::Vector2f(0, 0));

int R = 400;