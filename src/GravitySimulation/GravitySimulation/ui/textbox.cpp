#include "button.h"
#include "textbox.h"

TextBox::TextBox(const sf::Vector2f size, const sf::Vector2f position, int value, std::string type)
    : Button(size, position)
{
    count++;
    this->is_toggle = false;
    this->value = value;
    this->type = type;
};

TextBox::TextBox(sf::Font& font, const sf::Vector2f size, const sf::Vector2f position, int value, std::string type)
    : Button(font, size, position)
{
    count++;
    this->is_toggle = false;
    this->value = value;
    this->type = type;
};

TextBox::~TextBox()
{
    count--;
}

void TextBox::handle_input(const sf::Event& event) {
    if (event.type == sf::Event::TextEntered && is_toggle) {

        if (event.text.unicode == '\b' && !label.empty() && label != default_text)
        {
            type_sound.play();
            label.pop_back();
        }
        else if (std::isdigit(static_cast<char>(event.text.unicode)) && (label.size() < 9 || label == default_text)) 
        {
            type_sound.play();
            if (label == default_text)
                label.clear();
            label += static_cast<char>(event.text.unicode);
        }
        else if (type == "double" && (static_cast<char>(event.text.unicode) == '.' && label.find('.') == std::string::npos)
            && label.size() > 0 && label.size() < 9)
        {
            type_sound.play();
            label += static_cast<char>(event.text.unicode);
        }
        set_button_label(font_size, label);
    }
}

void TextBox::set_toggle(bool value)
{
    this->is_toggle = value;
    if (is_toggle)
    {
        button.setOutlineColor(button_colorset.toggle);
        set_button_label(font_size, default_text);
    }
    else
    {
        button.setOutlineColor(button_colorset.color);
        if (label.size() == 0)
            set_button_label(font_size, "0");
        if (label != default_text)
            this->value = std::stod(label);
        
        if (type == "int")
            set_button_label(font_size, std::to_string((int)this->value));
        else
            set_button_label(font_size, std::to_string(this->value));
    }
}

void TextBox::get_button_status(sf::RenderWindow& window, sf::Event& event)
{
    this->mouse_pos_window = sf::Mouse::getPosition(window);
    this->mouse_pos_view = window.mapPixelToCoords(this->mouse_pos_window);

    bool play_sound = !this->is_hover;
    bool change_cursor = this->is_hover;
    this->is_hover = false;
    this->is_pressed = false;

    if (is_active)
    {
        button.setFillColor(button_colorset.color);
        button_label.setFillColor(label_colorset.color);
        if (button.getGlobalBounds().contains(this->mouse_pos_view))
        {
            if (play_sound)
                hover_sound.play();
            this->is_hover = true;
            window.setMouseCursor(pointer_cursor);
        }
        else if (change_cursor)
        {
            window.setMouseCursor(default_cursor);
        }

        if (button.getGlobalBounds().contains(this->mouse_pos_view))
        {
            if (event.type == sf::Event::MouseButtonPressed)
            {
                click_sound.play();
                this->is_pressed = true;

                set_toggle(true);
            }
        }

        button.setOutlineThickness(button_border_thickness);
        if (is_toggle)
            button.setOutlineColor(button_colorset.toggle);
        else
            button.setOutlineColor(button_colorset.color);

        if (is_hover)
        {
            button.setFillColor(button_colorset.hover);
            button_label.setFillColor(label_colorset.hover);
        }
        else if (is_toggle)
        {
            button.setFillColor(button_colorset.hover);
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
        button.setOutlineColor(disabled);
    }

}
