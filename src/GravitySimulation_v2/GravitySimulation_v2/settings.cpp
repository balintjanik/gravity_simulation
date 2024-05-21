#include "settings.h"

int WIDTH = 1920;
int HEIGHT = 1080;
int CANVAS_WIDTH = WIDTH - MENU_WIDTH;

sf::Font FONT;
float FONT_SIZE;
RectButton ONOFF_BTN(sf::Vector2f(0, 0), sf::Vector2f(0, 0));
RectButton EXIT_BTN(sf::Vector2f(0, 0), sf::Vector2f(0, 0));

int R = 400;