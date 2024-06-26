#include "sound_manager.h"

sf::SoundBuffer hover_buffer;
sf::Sound hover_sound;
sf::SoundBuffer click_buffer;
sf::Sound click_sound;
sf::SoundBuffer type_buffer;
sf::Sound type_sound;
sf::SoundBuffer blackhole_buffer;
sf::Sound blackhole_sound;

sf::SoundBuffer music_buffer;
sf::Sound music_sound;

void init_sounds()
{
    if (!hover_buffer.loadFromFile(hover_path))
    {
        std::cout << "Error loading hover sound." << std::endl;
        // TODO: Error loading sounds
    }
    hover_sound.setBuffer(hover_buffer);

    if (!click_buffer.loadFromFile(click_path))
    {
        std::cout << "Error loading click sound." << std::endl;
        // TODO: Error loading sounds
    }
    click_sound.setBuffer(click_buffer);

    if (!type_buffer.loadFromFile(type_path))
    {
        std::cout << "Error loading type sound." << std::endl;
        // TODO: Error loading sounds
    }
    type_sound.setBuffer(type_buffer);

    if (!blackhole_buffer.loadFromFile(blackhole_path))
    {
        std::cout << "Error loading type sound." << std::endl;
        // TODO: Error loading sounds
    }
    blackhole_sound.setBuffer(blackhole_buffer);
}

void init_music()
{
    if (!music_buffer.loadFromFile(music_path))
    {
        std::cout << "Error loading music." << std::endl;
        // TODO: Error loading sounds
    }
    music_sound.setBuffer(music_buffer);
    music_sound.play();
    music_sound.setLoop(true);
}

void set_sound_volume(int value)
{
    hover_sound.setVolume(value);
    click_sound.setVolume(value);
    type_sound.setVolume(value);
    blackhole_sound.setVolume(value);
}

void set_music_volume(int value)
{
    music_sound.setVolume(value);
}