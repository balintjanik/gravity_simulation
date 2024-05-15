#include <SFML/Graphics.hpp>

#include <random>
#include <vector>

#include "settings.h"
#include "particle.h"
#include "setup_type.h"

using namespace std;

sf::Color hsv_to_rgb(float H, float S, float V)
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

sf::Color map_forces_to_color(float all_forces)
{
    float normalized_forces = min(all_forces / MAX_FORCES, 1.0f);
    float hue = (1.0f - normalized_forces) * 0.65f;
    float saturation = 1.0f;
    float value = 1.0f;

    return hsv_to_rgb(hue, saturation, value);
}

float generate_random_float(float min_value, float max_value)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> dist(min_value, max_value);

    return dist(gen);
}

float v2f_distance(sf::Vector2f v1, sf::Vector2f v2)
{
    float dx = v2.x - v1.x;
    float dy = v2.y - v1.y;
    return sqrt(dx * dx + dy * dy);
}

float map_value(float value, float min_input, float max_input, float min_output, float max_output) {
    value = max(min_input, min(max_input, value));
    return min_output + (max_output - min_output) * (value - min_input) / (max_input - min_input);
}

vector<Particle> generate_particles(float min_x, float max_x, float min_y, float max_y)
{
    vector<Particle> particles;

    float x, y;
    float vx, vy;
    float r, theta;
    float ang_to_cent, angle, distance, speed, rand_x, rand_y;

    for (int i = 0; i < N - 1; i++)
    {
        // set random position
        switch (PLACEMENT_TYPE)
        {
            case PlacementType::Circular:
                r = R * sqrt(generate_random_float(0, 1));
                theta = generate_random_float(0, 1) * 2 * PI;
                x = WIDTH / 2 + r * cos(theta);
                y = HEIGHT / 2 + r * sin(theta);
                break;
            default: // FullScreen is default
                x = generate_random_float(0, WIDTH);
                y = generate_random_float(0, HEIGHT);
                break;
        }
        sf::Vector2f initialPosition(x, y);

        // set velocity
        switch (SPEED_TYPE)
        {
            case SpeedType::RandSpeed:
                vx = generate_random_float(-1.0f, 1.0f);
                vy = generate_random_float(-1.0f, 1.0f);
                break;
            case SpeedType::AngularSpeed:
                ang_to_cent = atan2(y - HEIGHT / 2, x - WIDTH / 2);
                angle = ang_to_cent + 90;
                distance = v2f_distance(sf::Vector2f(x, y), sf::Vector2f(WIDTH / 2, HEIGHT / 2));
                speed = map_value(distance, 0.0f, R, 0.0f, MASS*10.0f);
                rand_x = generate_random_float(0.7f, 2.0f);
                rand_y = generate_random_float(0.7f, 2.0f);
                vx = speed * cos(angle) * rand_x;
                vy = speed * sin(angle) * rand_y;
                break;
            default: // NoSpeed is default
                vx = 0.0f;
                vy = 0.0f;
                break;
        }
        sf::Vector2f initialVelocity(vx, vy);

        // set color
        sf::Color particleColor(sf::Color::Blue);

        particles.push_back(Particle(initialPosition, initialVelocity, particleColor, RADIUS, MASS));
    }

    return particles;
}