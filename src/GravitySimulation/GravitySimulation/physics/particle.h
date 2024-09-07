#ifndef PARTICLE_H
#define PARTICLE_H

#include <SFML/Graphics.hpp>
#include <deque>
#include "../globals/settings.h"

static int id_counter = 0;

struct Particle {
    sf::Vector2f position;
    sf::Vector2f old_position;
    sf::Vector2f velocity;
    sf::Color color;
    std::deque<sf::Vector2f> trail;
    const double mass;
    const double radius;
    const int id;
    const bool is_singularity;

    Particle(const sf::Vector2f& pos, const sf::Vector2f& vel, const sf::Color& col, double rad, double m, bool is_sin = false)
        : position(pos), old_position(pos), velocity(vel), color(col), radius(rad), mass(m), id(id_counter), is_singularity(is_sin){}
};

#endif