#include "button.h"
#include "toggle_button.h"

ToggleButton::ToggleButton(const sf::Vector2f size, const sf::Vector2f position, bool is_toggle)
    : Button(size, position)
{
    count++;
    this->is_toggle = is_toggle;
};

ToggleButton::ToggleButton(sf::Font& font, const sf::Vector2f size, const sf::Vector2f position, bool is_toggle)
    : Button(font, size, position)
{
    count++;
    this->is_toggle = is_toggle;
};

ToggleButton::~ToggleButton()
{
    count--;
}

void ToggleButton::get_button_status(sf::RenderWindow& window, sf::Event& event)
{
    this->mouse_pos_window = sf::Mouse::getPosition(window);
    this->mouse_pos_view = window.mapPixelToCoords(this->mouse_pos_window);

    this->is_hover = false;
    this->is_pressed = false;

    if (is_active)
    {
        button.setFillColor(button_colorset.color);
        button_label.setFillColor(label_colorset.color);
        if (button.getGlobalBounds().contains(this->mouse_pos_view))
        {
            this->is_hover = true;
        }

        if (button.getGlobalBounds().contains(this->mouse_pos_view))
        {
            if (event.type == sf::Event::MouseButtonReleased)
            {
                this->is_pressed = true;

                if (is_toggle)
                    is_toggle = false;
                else
                    is_toggle = true;
            }
        }

        if (is_hover)
        {
            button.setFillColor(button_colorset.hover);
            button_label.setFillColor(label_colorset.hover);
        }
        else if (is_toggle)
        {
            button.setFillColor(button_colorset.toggle);
            button_label.setFillColor(label_colorset.toggle);
        }
        else
        {
            button.setFillColor(button_colorset.color);
        }

        if (button.getGlobalBounds().contains(this->mouse_pos_view))
        {
            if (event.type == sf::Event::MouseButtonPressed)
            {
                button.setFillColor(button_colorset.press);
                button_label.setFillColor(label_colorset.press);
            }
        }

    }
    else
    {
        button.setFillColor(disabled);
    }

}
