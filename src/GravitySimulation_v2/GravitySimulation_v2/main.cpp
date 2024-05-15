#include <SFML/Graphics.hpp>

#include <vector>
#include <random>

#include "settings.h"
#include "utils.h"
#include "physics.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(width, height), "Gravitational Force Simulation");

    // Init particles
    std::vector<Particle> particles = generate_particles(0, width, 0, height);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Update positions
        update_positions(particles);

        // Display
        window.clear();

        // Draw trails first to avoid trails covering particles
        if (has_trail)
        {
            for (auto& p : particles)
            {
                sf::Color current_trail_color = trail_color;
                for (int i = 0; i < p.trail.size(); i++)
                {
                    sf::CircleShape circle(trail_radius);
                    current_trail_color.a = ((255 * i) / trail_size);
                    circle.setFillColor(current_trail_color);
                    circle.setPosition(p.trail[i].x, p.trail[i].y);
                    window.draw(circle);
                }
            }
        }

        // Draw particles
        for (auto& p : particles)
        {
            sf::CircleShape circle(p.radius);
            circle.setFillColor(p.color);
            circle.setPosition(p.position.x, p.position.y);
            window.draw(circle);
        }
        window.display();
    }

	return 0;
}