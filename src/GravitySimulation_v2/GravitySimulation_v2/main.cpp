#include <SFML/Graphics.hpp>

#include <vector>
#include <random>

#include "globals.h"
#include "settings.h"
#include "utils.h"
#include "physics.h"
#include "grid.h"
#include "menu_utils.h"

int main()
{
    sf::VideoMode screen = sf::VideoMode::getDesktopMode();
    sf::RenderWindow window(screen, "Gravitational Force Simulation", sf::Style::Fullscreen);
    window.setFramerateLimit(30);

    // Initialize
    recalc_sizes(screen.width, screen.height);
    init_buttons();
    reload_sim();

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::Resized)
            {
                sf::Vector2u new_size = window.getSize();
                sf::View view(sf::FloatRect(0, 0, static_cast<float>(new_size.x), static_cast<float>(new_size.y)));
                window.setView(view);
                recalc_sizes(new_size.x, new_size.y);
                init_buttons();
                reload_sim();
            }

            // Show/hide menu on H keypress
            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::H)
                {
                    if (SHOW_MENU)
                        SHOW_MENU = false;
                    else
                        SHOW_MENU = true;
                }
            }

            // Untoggle textboxes on click
            if (event.type == sf::Event::MouseButtonReleased)
                untoggle_textboxes();

            // Update button statuses
            update_button_statuses(window, event);

            // Handle text input
            if (event.type == sf::Event::TextEntered)
                handle_textbox_input(event);

            // Handle button clicks
            if (event.type == sf::Event::MouseButtonReleased)
                handle_button_clicks(window, event);
        }

        // Update fps
        update_fps();

        // Update positions
        update_positions(optim_grid);

        // Display
        window.clear();

        // Draw particles
        draw_particles(window);

        // Draw menu
        if (SHOW_MENU)
            draw_menu(window);
        
        window.display();
    }

	return 0;
}