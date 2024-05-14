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
        update_positions(particles, timestep);

        // Draw particles
        window.clear();

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