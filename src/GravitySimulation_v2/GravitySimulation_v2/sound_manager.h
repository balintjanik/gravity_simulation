#ifndef SOUND_MANAGER_H
#define SOUND_MANAGER_H

#include <SFML/Audio.hpp>
#include <iostream>

// Sounds
static std::string hover_path = "resources/sounds/hover_medium.wav";
static std::string click_path = "resources/sounds/click.wav";
static std::string type_path = "resources/sounds/hover_medium.wav";
static std::string blackhole_path = "resources/sounds/blackhole_hit1.wav";

extern sf::SoundBuffer hover_buffer;
extern sf::Sound hover_sound;
extern sf::SoundBuffer click_buffer;
extern sf::Sound click_sound;
extern sf::SoundBuffer type_buffer;
extern sf::Sound type_sound;
extern sf::SoundBuffer blackhole_buffer;
extern sf::Sound blackhole_sound;

// Music
static std::string music_path = "resources/music/ambient_space_music_1.mp3";
extern sf::SoundBuffer music_buffer;
extern sf::Sound music_sound;

void init_sounds();

void init_music();

void set_sound_volume(int value);

void set_music_volume(int value);

#endif
