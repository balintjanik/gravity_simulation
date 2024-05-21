#include <SFML/Graphics.hpp>

#include <vector>
#include <random>

#include "globals.h"
#include "settings.h"
#include "utils.h"
#include "physics.h"
#include "grid.h"

int main()
{
    sf::VideoMode screen = sf::VideoMode::getDesktopMode();
    sf::RenderWindow window(screen, "Gravitational Force Simulation", sf::Style::Fullscreen);
    WIDTH = screen.width;
    HEIGHT = screen.height;
    if (WIDTH > HEIGHT)
        R = 2 * HEIGHT / 5;
    else
        R = 2 * WIDTH / 5;

    // Init particles
    particles = generate_particles(SPAWN_MARGIN, WIDTH - SPAWN_MARGIN, SPAWN_MARGIN, HEIGHT - SPAWN_MARGIN);
    Grid collision_grid(COLLISION_CELL_SIZE);
    init_collision_grid(collision_grid);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Update positions
        update_positions(collision_grid);

        // Display
        window.clear();

        // Draw trails first to avoid trails covering particles
        if (HAS_TRAIL)
        {
            for (auto& p : particles)
            {
                sf::Color current_trail_color = TRAIL_COLOR;
                for (int i = 0; i < p.trail.size(); i++)
                {
                    sf::CircleShape circle(TRAIL_RADIUS);
                    current_trail_color.a = ((255 * i) / TRAIL_SIZE);
                    circle.setFillColor(current_trail_color);
                    circle.setPosition(p.trail[i].x - TRAIL_RADIUS, p.trail[i].y - TRAIL_RADIUS);
                    window.draw(circle);
                }
            }
        }

        // Draw particles
        // If not set otherwise, draw them the most effective way
        if (!(VISUALIZE_SPATIAL_GRID || VISUALIZE_PARTICLE_CELL))
        {
            for (auto& p : particles)
            {
                sf::CircleShape circle(p.radius);
                circle.setFillColor(p.color);

                // setPosition sets the coordinates of top left corner
                circle.setPosition(p.position.x - p.radius, p.position.y - p.radius);

                window.draw(circle);
            }
        }
        // If set, draw grid and color particles accordingly
        else
        {
            // Draw grid
            if (VISUALIZE_SPATIAL_GRID)
            {
                for (int x = 0; x < collision_grid.width; x++)
                {
                    for (int y = 0; y < collision_grid.height; y++)
                    {
                        sf::Vector2f c_size(COLLISION_CELL_SIZE, COLLISION_CELL_SIZE);
                        sf::RectangleShape cell(c_size);

                        sf::Color fill_col = sf::Color::Transparent;
                        if (VISUALIZE_CELL_MASS)
                        {
                            fill_col = map_forces_to_color(collision_grid.get(x, y).total_mass/COLLISION_CELL_SIZE);
                            fill_col.a = 140;
                        }
                        cell.setFillColor(fill_col);
                        
                        cell.setOutlineColor(sf::Color(20, 20, 20));
                        cell.setOutlineThickness(0.5f);
                        cell.setPosition(x * COLLISION_CELL_SIZE - collision_grid.overflow_x/2, y * COLLISION_CELL_SIZE - collision_grid.overflow_y/2);
                        window.draw(cell);
                    }
                }
            }

            // Draw particles of cells
            int idx;
            for (int x = 0; x < collision_grid.width; x++)
            {
                for (int y = 0; y < collision_grid.height; y++)
                {
                    // Calculate color based on grid position
                    sf::Color col = sf::Color::Green;
                    if ((y % 2 == 0 && x % 2 == 1) || (y % 2 == 1 && x % 2 == 0))
                        col = sf::Color::Magenta;

                    auto& current_cell = collision_grid.get(x, y);
                    for (auto it1 = current_cell.particle_indices.begin(); it1 != current_cell.particle_indices.end(); ++it1)
                    {
                        idx = get_idx_by_id(*it1);
                        if (idx < 0)
                            continue;

                        Particle& p = particles[idx];

                        sf::CircleShape circle(p.radius);

                        // Set color based on custom settings
                        if (VISUALIZE_PARTICLE_CELL)
                            circle.setFillColor(col);
                        else
                            circle.setFillColor(p.color);

                        circle.setPosition(p.position.x - p.radius, p.position.y - p.radius);
                        window.draw(circle);
                    }

                    // draw center of mass
                    if (VISUALIZE_COM)
                    {
                        sf::CircleShape com(5,3);
                        com.setFillColor(sf::Color::Red);
                        sf::Vector2f com_pos = collision_grid.get(x, y).center_of_mass;
                        if (com_pos.x == 0 && com_pos.y == 0)
                        {
                            int to_center = COLLISION_CELL_SIZE / 2;
                            int correct_overflow_x = collision_grid.overflow_x / 2;
                            int correct_overflow_y = collision_grid.overflow_y / 2;
                            com.setPosition(x * COLLISION_CELL_SIZE + to_center - 5 - correct_overflow_x, y * COLLISION_CELL_SIZE + to_center - 5 - correct_overflow_y);
                        }
                        else
                        {
                            com.setPosition(com_pos.x - 5, com_pos.y - 5);
                        }
                        window.draw(com);
                    }
                }
            }
        }
        
        window.display();
    }

	return 0;
}