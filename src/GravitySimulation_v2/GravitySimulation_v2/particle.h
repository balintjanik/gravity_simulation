#ifndef PARTICLE_H
#define PARTICLE_H

#include <SFML/Graphics.hpp>
#include <deque>

struct Particle {
    sf::Vector2f position;
    sf::Vector2f velocity;
    sf::Color color;
    std::deque<sf::Vector2f> trail;
    float mass;
    float radius;

    Particle(const sf::Vector2f& pos, const sf::Vector2f& vel, const sf::Color& col, float rad, float m)
        : position(pos), velocity(vel), color(col), radius(rad), mass(m) {}
};

#endif