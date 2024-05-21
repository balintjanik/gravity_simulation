////////////////////////////////////////////////////////////
///
/// Credit to: Pyromagne (https://github.com/Pyromagne/SFML-Button)
///
////////////////////////////////////////////////////////////

#include "button.h"
#include "rect_button.h"
#include "settings.h"
#include <iostream>

////////////////////////////////////////////////////////////
///
/// @category Rectangle Button methods
///
////////////////////////////////////////////////////////////


RectButton::RectButton(const sf::Vector2f size = sf::Vector2f(0, 0), const sf::Vector2f position = sf::Vector2f(0, 0), bool isToggle)
{
    count++;
    this->button.setSize(size);
    this->button.setPosition(position);
    this->buttonPos = position;
    this->buttonRect = this->button.getLocalBounds();
    this->button.setFillColor(defaultColor);

    this->label = "Button "+ std::to_string(count);
    this->setButtonLabel(FONT_SIZE, label);
    
    this->isToggle = isToggle;
}

////////////////////////////////////////////////////////////

RectButton::RectButton(sf::Font& font, const sf::Vector2f size = sf::Vector2f(0, 0), const sf::Vector2f position = sf::Vector2f(0, 0), bool isToggle)
{
    count++;
    this->button.setSize(size);
    this->button.setPosition(position);
    this->buttonPos = position;
    this->buttonRect = this->button.getLocalBounds();
    this->button.setFillColor(defaultColor);

    this->buttonLabel.setFont(font);
    this->label = "Button "+ std::to_string(count);
    this->setButtonLabel(FONT_SIZE, label);

    this->isToggle = isToggle;
}

////////////////////////////////////////////////////////////

RectButton::RectButton(sf::Font& font, bool autoSize = false, const sf::Vector2f position = sf::Vector2f(0, 0), bool isToggle)
{
    count++;
    this-> autoSize = autoSize;
    this->button.setPosition(position);
    this->buttonPos = position;
    this->buttonRect = this->button.getLocalBounds();
    this->button.setFillColor(defaultColor);

    this->buttonLabel.setFont(font);
    this->label = "Button "+ std::to_string(count);
    this->setButtonLabel(FONT_SIZE, label);

    this->isToggle = isToggle;
}

////////////////////////////////////////////////////////////

RectButton::~RectButton()
{
    count--;
}

////////////////////////////////////////////////////////////

void RectButton::getButtonStatus(sf::RenderWindow& window, sf::Event& event)
{
    this->mousePosWindow = sf::Mouse::getPosition(window);
    this->mousePosView = window.mapPixelToCoords(this->mousePosWindow);

    this->isHover = false;
    this->isPressed = false;

    if (isActive)
    {
        button.setFillColor(buttonColorSet.color);
        buttonLabel.setFillColor(labelColorSet.color);
        if (button.getGlobalBounds().contains(this->mousePosView))
        {
            this->isHover = true;
        }

        if (button.getGlobalBounds().contains(this->mousePosView))
        {
            if (event.type == sf::Event::MouseButtonReleased)
            {
                this->isPressed = true;

                if (isToggle)
                {
                    if (isChosen)
                        isChosen = false;
                    else
                        isChosen = true;
                }
            }
        }

        //I am not sure if it is best to implement this inside a class
        if (isHover)
        {
            button.setFillColor(buttonColorSet.hover);
            buttonLabel.setFillColor(labelColorSet.hover);
        }
        else if (isChosen)
        {
            button.setFillColor(buttonColorSet.chosen);
            buttonLabel.setFillColor(labelColorSet.chosen);
        }
        else
        {
            button.setFillColor(buttonColorSet.color);
        }

        if(button.getGlobalBounds().contains(this->mousePosView))
        {
            if (event.type == sf::Event::MouseButtonPressed)
            {
                button.setFillColor(buttonColorSet.press);
                buttonLabel.setFillColor(labelColorSet.press);
            }
        }

    }
    else
    {
        button.setFillColor(disabled);
    }

}

////////////////////////////////////////////////////////////

void RectButton::draw(sf::RenderWindow& window)
{
    window.draw(button);
    
    if (isLabelVisible)
    {
        window.draw(buttonLabel);
    }
    
}

////////////////////////////////////////////////////////////

void RectButton::setButtonLabel(float charSize, std::string label)
{
    this->buttonLabel.setString(label);
    this->buttonLabel.setCharacterSize(charSize);
    this->buttonLabel.setFillColor(labelColorSet.color);
    this->label = label;

    this->labelRect = this->buttonLabel.getLocalBounds();

    if(autoSize)
    {   /* Temporary Fix */
        sf::Vector2f autoRectSize = sf::Vector2f(labelRect.width/* + (2.5f * (labelRect.width/10))*/,
                                                 labelRect.height + (10.f * (labelRect.height/10)));
        this->button.setSize(autoRectSize);
        this->buttonRect = this->button.getLocalBounds();

        this->buttonLabel.setOrigin (this->labelRect.width/2.0f,
                                    this->labelRect.height/2.0f);

        this->buttonLabel.setPosition(this->buttonPos.x + (this->buttonRect.width/2.0f),
                                      this->buttonPos.y + (this->buttonRect.height/4.0f));
    }
    else
    {
        this->buttonLabel.setOrigin(this->labelRect.width/2.0f,
                                    this->labelRect.height/2.0f);

        this->buttonLabel.setPosition(this->buttonPos.x + (this->buttonRect.width/2.0f),
                                      this->buttonPos.y + (this->buttonRect.height/2.0f) - (FONT_SIZE / 4));
    }
}

////////////////////////////////////////////////////////////

void RectButton::setButtonLabel(float charSize)
{
    setButtonLabel(charSize, this->label);
}
