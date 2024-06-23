#ifndef SOUND_MANAGER_H
#define SOUND_MANAGER_H

#include <SFML/Audio.hpp>
#include <iostream>

static std::string hover_path = "hover_medium.wav";
static std::string click_path = "click.wav";
static std::string type_path = "hover_medium.wav";

extern sf::SoundBuffer hover_buffer;
extern sf::Sound hover_sound;
extern sf::SoundBuffer click_buffer;
extern sf::Sound click_sound;
extern sf::SoundBuffer type_buffer;
extern sf::Sound type_sound;

void init_sounds();

void set_sound_volume(int value);

#endif
