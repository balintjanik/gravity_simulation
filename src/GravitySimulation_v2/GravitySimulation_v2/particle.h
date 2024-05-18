#ifndef PARTICLE_H
#define PARTICLE_H

#include <SFML/Graphics.hpp>
#include <deque>
#include "settings.h"

struct Particle {
    sf::Vector2f position;
    sf::Vector2f old_position;
    sf::Vector2f velocity;
    sf::Color color;
    std::deque<sf::Vector2f> trail;
    float mass;
    float radius;
    const int id;

    Particle(const sf::Vector2f& pos, const sf::Vector2f& vel, const sf::Color& col, float rad, float m)
        : position(pos), old_position(pos), velocity(vel), color(col), radius(rad), mass(m), id(id_counter){}
};

#endif