#include "cursors.h"

sf::Cursor default_cursor;
sf::Cursor pointer_cursor;
sf::Cursor grabber_cursor;

#include <iostream>

void init_cursors()
{
	default_cursor.loadFromSystem(sf::Cursor::Arrow);

	pointer_cursor.loadFromSystem(sf::Cursor::Hand);

	sf::Image grab_img;
	grab_img.loadFromFile("resources/cursors/grab_32.png");
	grabber_cursor.loadFromPixels(grab_img.getPixelsPtr(), grab_img.getSize(), sf::Vector2u(16, 16));
}