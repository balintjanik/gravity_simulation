#include <SFML/Graphics.hpp>

#include <vector>
#include <random>

#include "globals/globals.h"
#include "globals/settings.h"
#include "utils/utils.h"
#include "physics/physics.h"
#include "grid/grid.h"
#include "ui/menu_utils.h"
#include "sound/sound_manager.h"

int main()
{
    sf::VideoMode screen = sf::VideoMode::getDesktopMode();
    sf::RenderWindow window(screen, "Gravitational Force Simulation", sf::Style::Fullscreen);
    window.setFramerateLimit(DEFAULT_FPS_LIMIT);

    // Initialize
    recalc_sizes(screen.width, screen.height);
    init_sounds();
    init_music();
    Grid collision_grid(settings.COLLISION_CELL_SIZE);
    reload_sim(collision_grid);

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
                reload_sim(collision_grid);
            }

            // Show/hide UI elements
            if (event.type == sf::Event::KeyPressed)
            {
                // Reload simulation
                if (event.key.code == RELOAD_KEY)
                {
                    reload_sim(collision_grid);
                    click_sound.play();
                }
                // Show/hide menu
                else if (event.key.code == SHOW_MENU_KEY)
                {
                    SHOW_MENU = !SHOW_MENU;
                    update_performance_position(SHOW_MENU);

                    click_sound.play();
                }
                // Show/hide help
                else if (event.key.code == SHOW_HELP_KEY)
                {
                    if (SHOW_HELP)
                        SHOW_HELP = false;
                    else
                        SHOW_HELP = true;

                    click_sound.play();
                }
                // Show/hide FPS
                else if (event.key.code == SHOW_PERFORMANCE_KEY)
                {
                    if (SHOW_PERFORMANCE)
                        SHOW_PERFORMANCE = false;
                    else
                        SHOW_PERFORMANCE = true;

                    click_sound.play();
                }
                // Show/hide everything
                else if (event.key.code == SHOW_ALL_KEY)
                {
                    if (SHOW_MENU || SHOW_HELP || SHOW_PERFORMANCE)
                    {
                        SHOW_MENU = false;
                        SHOW_HELP = false;
                        SHOW_PERFORMANCE = false;
                    }
                    else
                    {
                        SHOW_MENU = true;
                        SHOW_HELP = true;
                        SHOW_PERFORMANCE = true;
                    }
                    update_performance_position(SHOW_MENU);

                    click_sound.play();
                }
                // Add singularity
                else if (event.key.code == SINGULARITY_KEY)
                {
                    add_singularity(collision_grid);
                    blackhole_sound.play();
                }
                // Enter textbox
                else if (event.key.code == sf::Keyboard::Enter)
                {
                    untoggle_textboxes(window);
                }
                // Exit
                else if (event.key.code == EXIT_KEY)
                {
                    window.close();
                }
            }

            if (SHOW_MENU)
            {
                // Untoggle textboxes on any click
                if (event.type == sf::Event::MouseButtonPressed)
                    untoggle_textboxes(window);

                // Update button statuses
                update_button_statuses(window, event);

                // Handle text input
                if (event.type == sf::Event::TextEntered)
                    handle_textbox_input(event);

                // Handle button clicks
                if (event.type == sf::Event::MouseButtonPressed)
                    handle_button_clicks(window, event, collision_grid);
            }
        }

        // Update fps
        update_fps();

        // Display
        window.clear();

        // Update positions
        update_positions(collision_grid, window);

        // Draw particles
        draw_particles(window, collision_grid);

        // Draw menu
        if (SHOW_MENU)
            draw_menu(window);

        // Draw fps
        if (SHOW_PERFORMANCE)
            draw_performance(window);

        // Draw help
        if (SHOW_HELP)
            draw_help(window);
        
        window.display();
    }

	return 0;
}