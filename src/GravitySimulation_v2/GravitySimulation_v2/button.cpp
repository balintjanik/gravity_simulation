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

ColorSet::ColorSet()
{
    this->color = defult_color;
    this->toggle = default_toggle;
    this->hover = default_hover;
    this->press = default_press;
}

ColorSet::ColorSet(sf::Color color)
{
    init(color, color, color, color);
}

ColorSet::ColorSet(sf::Color color, sf::Color toggle, sf::Color hover, sf::Color press)
{
    init(color, toggle, hover, press);
}

void ColorSet::init(sf::Color color, sf::Color toggle, sf::Color hover, sf::Color press)
{
    this->color = color;
    this->toggle = toggle;
    this->hover = hover;
    this->press = press;
}

Button::Button(const sf::Vector2f size, const sf::Vector2f position)
{
    this->button.setSize(size);
    this->button.setPosition(position);
    this->button_pos = position;
    this->button_rect = this->button.getLocalBounds();
    this->button.setFillColor(defult_color);

    this->font_size = 10;
    this->label = "Button " + std::to_string(count);
    this->set_button_label(font_size, label);
}

Button::Button(sf::Font& font, const sf::Vector2f size, const sf::Vector2f position)
{
    this->button.setSize(size);
    this->button.setPosition(position);
    this->button_pos = position;
    this->button_rect = this->button.getLocalBounds();
    this->button.setFillColor(defult_color);

    this->font_size = 10;
    this->button_label.setFont(font);
    this->label = "Button " + std::to_string(count);
    this->set_button_label(font_size, label);

    button.setOutlineThickness(button_border_thickness);
}

void Button::draw(sf::RenderWindow& window)
{
    window.draw(button);

    if (is_label_visible)
    {
        window.draw(button_label);
    }

}

void Button::set_button_label(float char_size, std::string label)
{
    this->font_size = char_size;
    this->button_label.setString(label);
    this->button_label.setCharacterSize(char_size);
    this->button_label.setFillColor(label_colorset.color);
    this->label = label;

    this->label_rect = this->button_label.getLocalBounds();

    this->button_label.setOrigin(this->label_rect.width / 2.0f, this->label_rect.height / 2.0f - (this->label_rect.height - char_size < 0 ? this->label_rect.height - char_size : 0));

    this->button_label.setPosition(this->button_pos.x + (this->button_rect.width / 2.0f), this->button_pos.y + (this->button_rect.height / 2.0f));
}

void Button::set_button_label(float char_size)
{
    this->font_size = char_size;
    set_button_label(char_size, this->label);
}

void Button::set_button_font(sf::Font& font)
{
    button_label.setFont(font);
}

void Button::set_button_color(sf::Color color)
{
    set_button_color(color,color,color,color);
}

void Button::set_button_color(sf::Color color, sf::Color toggle, sf::Color hover, sf::Color press)
{
    this->button_colorset.color = color;
    this->button_colorset.toggle = toggle;
    this->button_colorset.hover = hover;
    this->button_colorset.press = press;
}

void Button::set_label_color(sf::Color color)
{
    set_label_color(color,color,color,color);
}


void Button::set_label_color(sf::Color color, sf::Color toggle, sf::Color hover, sf::Color press)
{
    this->label_colorset.color = color;
    this->label_colorset.toggle = toggle;
    this->label_colorset.hover = hover;
    this->label_colorset.press = press;
}

unsigned int Button::count = 0;
