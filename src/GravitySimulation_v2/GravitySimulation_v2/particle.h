#ifndef PARTICLE_H
#define PARTICLE_H

#include <SFML/Graphics.hpp>

struct Particle {
    sf::Vector2f position;
    sf::Vector2f velocity;
    sf::Color color;
    float radius;

    Particle(const sf::Vector2f& pos, const sf::Vector2f& vel, const sf::Color& col, float rad)
        : position(pos), velocity(vel), color(col), radius(rad) {}
};

#endif