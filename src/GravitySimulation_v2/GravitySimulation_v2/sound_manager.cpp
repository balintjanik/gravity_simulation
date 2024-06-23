#include "sound_manager.h"

sf::SoundBuffer hover_buffer;
sf::Sound hover_sound;
sf::SoundBuffer click_buffer;
sf::Sound click_sound;
sf::SoundBuffer type_buffer;
sf::Sound type_sound;

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
}

void set_sound_volume(int value)
{
    hover_sound.setVolume(value);
    click_sound.setVolume(value);
    type_sound.setVolume(value);
}