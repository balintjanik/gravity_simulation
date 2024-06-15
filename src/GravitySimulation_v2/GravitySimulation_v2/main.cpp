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

    // Initialize
    recalc_sizes(screen.width, screen.height);
    init_buttons();
    reload_sim();

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

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

        // Update positions
        update_positions(optim_grid);

        // Display
        window.clear();

        // Draw particles
        draw_particles(window);

        // Draw menu
        draw_menu(window);
        
        window.display();
    }

	return 0;
}