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
    window.setFramerateLimit(DEFAULT_FPS_LIMIT);

    // Initialize
    recalc_sizes(screen.width, screen.height);
    init_ui();
    reload_sim();

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            // Handle resize
            if (event.type == sf::Event::Resized)
            {
                sf::Vector2u new_size = window.getSize();
                sf::View view(sf::FloatRect(0, 0, static_cast<float>(new_size.x), static_cast<float>(new_size.y)));
                window.setView(view);
                recalc_sizes(new_size.x, new_size.y);
                init_ui();
                reload_sim();
            }

            // Show/hide UI elements
            if (event.type == sf::Event::KeyPressed)
            {
                // Reload simulation
                if (event.key.code == RELOAD_KEY)
                    reload_sim();
                // Show/hide menu
                else if (event.key.code == SHOW_MENU_KEY)
                {
                    if (SHOW_MENU)
                    {
                        SHOW_MENU = false;
                        FPS_TXT.setPosition(MARGIN_LEFT, MARGIN_TOP);
                    }
                    else
                    {
                        SHOW_MENU = true;
                        FPS_TXT.setPosition(MENU_WIDTH + MARGIN_LEFT, MARGIN_TOP);
                    }
                }
                // Show/hide help
                else if (event.key.code == SHOW_HELP_KEY)
                {
                    if (SHOW_HELP)
                        SHOW_HELP = false;
                    else
                        SHOW_HELP = true;
                }
                // Show/hide FPS
                else if (event.key.code == SHOW_FPS_KEY)
                {
                    if (SHOW_FPS)
                        SHOW_FPS = false;
                    else
                        SHOW_FPS = true;
                }
                // Show/hide everything
                else if (event.key.code == SHOW_ALL_KEY)
                {
                    if (SHOW_MENU || SHOW_HELP || SHOW_FPS)
                    {
                        SHOW_MENU = false;
                        SHOW_HELP = false;
                        SHOW_FPS = false;
                        FPS_TXT.setPosition(MARGIN_LEFT, MARGIN_TOP);
                    }
                    else
                    {
                        SHOW_MENU = true;
                        SHOW_HELP = true;
                        SHOW_FPS = true;
                        FPS_TXT.setPosition(MENU_WIDTH + MARGIN_LEFT, MARGIN_TOP);
                    }
                }
                // Exit
                else if (event.key.code == EXIT_KEY)
                    window.close();
            }

            // Untoggle textboxes on any click
            if (event.type == sf::Event::MouseButtonReleased)
                untoggle_textboxes(window);

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

        // Draw fps
        if (SHOW_FPS)
            draw_fps(window);

        // Draw help
        if (SHOW_HELP)
            draw_help(window);
        
        window.display();
    }

	return 0;
}