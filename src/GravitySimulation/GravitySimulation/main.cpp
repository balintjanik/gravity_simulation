#include <SFML/Graphics.hpp>

#include <vector>
#include <random>

#include "globals/globals.h"
#include "globals/settings.h"
#include "utils/utils.h"
#include "physics/physics.h"
#include "grid/grid.h"
#include "ui/menu_utils.h"
#include "ui/cursors.h"
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
    init_cursors();
    Grid collision_grid(settings.COLLISION_CELL_SIZE);
    reload_sim(collision_grid);

    // Grab move
    sf::Vector2f start_position;
    sf::Vector2f end_position;
    bool is_moving = false;

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

            // Handle hotkeys
            if (event.type == sf::Event::KeyPressed)
            {
                handle_hotkeys(window, event, collision_grid);
            }

            // Handle moving
            if (event.type == sf::Event::MouseButtonPressed)
            {
                sf::Vector2f cursor_pos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
                if (!SHOW_MENU || (cursor_pos.x > MENU_WIDTH && cursor_pos.x < WIDTH - MENU_WIDTH))
                {
                    start_position = cursor_pos;
                    is_moving = true;
                    window.setMouseCursor(grabber_cursor);
                }
            }
            else if (event.type == sf::Event::MouseButtonReleased)
            {
                is_moving = false;
                window.setMouseCursor(default_cursor);
            }

            if (SHOW_MENU && !is_moving)
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

        // Handle moving
        if (is_moving)
        {
            end_position = window.mapPixelToCoords(sf::Mouse::getPosition(window));
            handle_move(start_position, end_position);
            start_position = window.mapPixelToCoords(sf::Mouse::getPosition(window));
        }

        // Update fps
        update_fps();

        // Display
        window.clear();

        if (settings.IS_PLAYING || settings.IS_FRAMESTEP)
        {
            settings.IS_FRAMESTEP = false;

            // Update positions
            update_positions(collision_grid, window);
        }

        // Draw particles
        draw_particles(window, collision_grid);

        // Draw borders
        draw_borders(window);

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