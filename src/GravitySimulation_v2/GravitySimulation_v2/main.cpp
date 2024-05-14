#include <SFML/Graphics.hpp>

#include <vector>
#include <random>

#include "settings.h"
#include "utils.h"
#include "physics.h"

int main()
{
    // Create a window
    sf::RenderWindow window(sf::VideoMode(width, height), "Gravitational Force Simulation");

    // Init particles
    std::vector<Particle> particles = generateParticles(0, width, 0, height);

    while (window.isOpen()) {
        // Process events
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Update positions
        updatePositions(particles, timestep);

        // Clear the window
        window.clear();

        // Draw particles
        for (auto& p : particles)
        {
            sf::CircleShape circle(p.radius);
            circle.setFillColor(p.color);
            circle.setPosition(p.position.x, p.position.y);
            window.draw(circle);
        }

        // Display the window
        window.display();
    }

	return 0;
}