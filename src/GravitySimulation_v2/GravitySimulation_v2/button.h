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

#ifndef BUTTON_H
#define BUTTON_H

#include <SFML/Graphics.hpp>

const sf::Color defult_color = sf::Color(0, 100, 200);
const sf::Color default_toggle = sf::Color::White;
const sf::Color default_hover = sf::Color(0, 160, 255);
const sf::Color default_press = sf::Color(0, 70, 140);
const sf::Color disabled = sf::Color(60,60,60);

struct ColorSet
{
    public:

        sf::Color color;
        sf::Color toggle;
        sf::Color hover;
        sf::Color press;
        
        ColorSet();
        ColorSet(sf::Color color);
        ColorSet(sf::Color color, sf::Color toggle, sf::Color hover, sf::Color press);

    private:

        void init(sf::Color color, sf::Color toggle, sf::Color hover, sf::Color press);
};

class Button
{
    public:

        Button(const sf::Vector2f size = sf::Vector2f(0, 0), const sf::Vector2f position = sf::Vector2f(0, 0));
        Button(sf::Font& font, const sf::Vector2f size, const sf::Vector2f position);

        virtual void get_button_status(sf::RenderWindow& window, sf::Event& event) = 0;
        void draw(sf::RenderWindow& window);
        void set_button_label(float charsize, std::string label);
        void set_button_label(float charsize);
        void set_button_font(sf::Font& font);
        void set_button_color(sf::Color color);
        void set_button_color(sf::Color color, sf::Color chosen, sf::Color hover, sf::Color press);
        void set_label_color(sf::Color color);
        void set_label_color(sf::Color color, sf::Color chosen, sf::Color hover, sf::Color press);

        sf::RectangleShape button;

        bool is_hover = false;
        bool is_pressed = false;
        bool is_active = true;
        bool is_label_visible = true;
        static unsigned int count;

    protected:
        int font_size;
        int button_border_thickness = 3;
        sf::Text button_label;
        sf::Vector2i mouse_pos_window;
        sf::Vector2f mouse_pos_view;
        sf::Vector2f button_pos;
        sf::FloatRect label_rect;
        std::string label;
        ColorSet button_colorset;
        ColorSet label_colorset = ColorSet(sf::Color::White);
        sf::FloatRect button_rect;
};

#endif
