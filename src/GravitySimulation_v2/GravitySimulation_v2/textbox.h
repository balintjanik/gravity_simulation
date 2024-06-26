#ifndef TEXTBOX_H
#define TEXTBOX_H

#include <SFML/Graphics.hpp>
#include "button.h"

class TextBox : public Button
{
public:

    TextBox(const sf::Vector2f size = sf::Vector2f(0, 0), const sf::Vector2f position = sf::Vector2f(0, 0), int value = 0, std::string type = "int");
    TextBox(sf::Font& font, const sf::Vector2f size, const sf::Vector2f position, int value, std::string type);
    void set_toggle(bool value);
    void handle_input(const sf::Event& event);

    ~TextBox();

    void get_button_status(sf::RenderWindow& window, sf::Event& event);

    std::string type = "int";
    std::string default_text = "TYPE HERE NOW";
    bool is_toggle = false;
    double value = 0;
};

#endif
