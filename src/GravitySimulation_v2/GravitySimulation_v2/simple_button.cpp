////////////////////////////////////////////////////////////
//
// Credit to: Pyromagne (https://github.com/Pyromagne/SFML-Button)
//
// MIT License
//
// Copyright (c) 2024 Pyromagne
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
// 
////////////////////////////////////////////////////////////

#include "button.h"
#include "simple_button.h"

SimpleButton::SimpleButton(const sf::Vector2f size, const sf::Vector2f position)
    : Button(size, position)
{
    count++;
};

SimpleButton::SimpleButton(sf::Font& font, const sf::Vector2f size, const sf::Vector2f position)
    : Button(font, size, position)
{
    count++;
};

SimpleButton::~SimpleButton()
{
    count--;
}

void SimpleButton::get_button_status(sf::RenderWindow& window, sf::Event& event)
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
            }
        }

        if (is_hover)
        {
            button.setFillColor(button_colorset.hover);
            button_label.setFillColor(label_colorset.hover);
        }
        else
        {
            button.setFillColor(button_colorset.color);
        }

        if(button.getGlobalBounds().contains(this->mouse_pos_view))
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
