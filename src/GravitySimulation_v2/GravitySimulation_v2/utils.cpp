#include <SFML/Graphics.hpp>

#include <random>
#include <vector>

#include "settings.h"
#include "particle.h"

using namespace std;

sf::Color HSVtoRGB(float H, float S, float V)
{
    int Hi = int(H * 6) % 6;
    float f = H * 6 - Hi;
    float p = V * (1 - S);
    float q = V * (1 - f * S);
    float t = V * (1 - (1 - f) * S);

    switch (Hi)
    {
        case 0: return sf::Color(V * 255, t * 255, p * 255);
        case 1: return sf::Color(q * 255, V * 255, p * 255);
        case 2: return sf::Color(p * 255, V * 255, t * 255);
        case 3: return sf::Color(p * 255, q * 255, V * 255);
        case 4: return sf::Color(t * 255, p * 255, V * 255);
        case 5: return sf::Color(V * 255, p * 255, q * 255);
        default: return sf::Color::White;
    }
}

sf::Color mapForcesToColor(float all_forces)
{
    float normalized_forces = all_forces / MAX_FORCES;
    float hue = (1.0f - normalized_forces) * 0.65f;
    float saturation = 1.0f;
    float value = 1.0f;

    return HSVtoRGB(hue, saturation, value);
}

float generateRandomFloat(float min_value, float max_value)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> dist(min_value, max_value);

    return dist(gen);
}

vector<Particle> generate_particles(float min_x, float max_x, float min_y, float max_y)
{
    vector<Particle> particles;
    float x, y;
    float vx, vy;

    for (int i = 0; i < N - 1; i++)
    {
        x = generateRandomFloat(0, WIDTH);
        y = generateRandomFloat(0, HEIGHT);
        sf::Vector2f initialPosition(x, y);

        vx = generateRandomFloat(-1.0f, 1.0f);
        vy = generateRandomFloat(-1.0f, 1.0f);
        sf::Vector2f initialVelocity(vx, vy);

        sf::Color particleColor(sf::Color::Blue);

        particles.push_back(Particle(initialPosition, initialVelocity, particleColor, RADIUS, MASS));
    }

    return particles;
}