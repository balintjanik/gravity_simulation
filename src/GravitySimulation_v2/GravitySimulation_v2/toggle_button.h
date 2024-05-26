#ifndef TOGGLEBUTTON_H
#define TOGGLEBUTTON_H

#include <SFML/Graphics.hpp>
#include "button.h"

class ToggleButton : public Button
{
public:

    ToggleButton(const sf::Vector2f size, const sf::Vector2f position, bool is_toggle = false);
    ToggleButton(sf::Font& font, const sf::Vector2f size, const sf::Vector2f position, bool is_toggle = false);
    void set_toggle(bool value);

    ~ToggleButton();

    void get_button_status(sf::RenderWindow& window, sf::Event& event);

    bool is_toggle = false;
};

#endif

