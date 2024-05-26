#include <SFML/Graphics.hpp>

#include <vector>
#include <random>

#include "globals.h"
#include "settings.h"
#include "utils.h"
#include "physics.h"
#include "grid.h"

void reload_sim()
{
    // Load new settings
    settings = current_settings;

    // Init particles
    particles = generate_particles(settings.SPAWN_MARGIN, CANVAS_WIDTH - settings.SPAWN_MARGIN, settings.SPAWN_MARGIN, HEIGHT - settings.SPAWN_MARGIN);
    
    // Init optimization grid
    optim_grid = Grid(settings.COLLISION_CELL_SIZE);
    init_optim_grid(optim_grid);
}

void recalc_sizes(int width, int height)
{
    WIDTH = width;
    HEIGHT = height;
    CANVAS_WIDTH = WIDTH - MENU_WIDTH;
    if (CANVAS_WIDTH > HEIGHT)
        settings.R = 2 * HEIGHT / 5;
    else
        settings.R = 2 * CANVAS_WIDTH / 5;
}

void init_buttons()
{
    FONT.loadFromFile("Poppins-Bold.ttf");
    FONT_SIZE = 20;

    int button_counter = 0;
    int label_counter = 0;
    int block_counter = 0;

    // Placement type settings
    PLACEMENT_TYPE_TXT.setString("PLACEMENT TYPE");
    PLACEMENT_TYPE_TXT.setFillColor(sf::Color::White);
    PLACEMENT_TYPE_TXT.setPosition(sf::Vector2f(CANVAS_WIDTH + MARGIN_LEFT, MARGIN_TOP + button_counter * (BTN_HEIGHT + MARGIN_BETWEEN) + label_counter * (FONT_SIZE + MARGIN_BETWEEN) + block_counter * MARGIN_TOP));
    PLACEMENT_TYPE_TXT.setFont(FONT);
    PLACEMENT_TYPE_TXT.setCharacterSize(FONT_SIZE);
    label_counter++;

    PLACEMENT_TYPE_CIRCULAR_BTN = ToggleButton(FONT, sf::Vector2f((MENU_WIDTH - MARGIN_LEFT - MARGIN_RIGHT)/2, BTN_HEIGHT), sf::Vector2f(CANVAS_WIDTH + MARGIN_LEFT, MARGIN_TOP + button_counter * (BTN_HEIGHT + MARGIN_BETWEEN) + label_counter * (FONT_SIZE + MARGIN_BETWEEN) + block_counter * MARGIN_TOP), true);
    PLACEMENT_TYPE_CIRCULAR_BTN.set_button_label(FONT_SIZE, "CIRCULAR");
    
    PLACEMENT_TYPE_FULLSCREEN_BTN = ToggleButton(FONT, sf::Vector2f((MENU_WIDTH - MARGIN_LEFT - MARGIN_RIGHT) / 2 - MARGIN_BETWEEN, BTN_HEIGHT), sf::Vector2f(CANVAS_WIDTH + MARGIN_LEFT + (MENU_WIDTH - MARGIN_LEFT - MARGIN_RIGHT) / 2 + MARGIN_BETWEEN, MARGIN_TOP + button_counter * (BTN_HEIGHT + MARGIN_BETWEEN) + label_counter * (FONT_SIZE + MARGIN_BETWEEN) + block_counter * MARGIN_TOP), false);
    PLACEMENT_TYPE_FULLSCREEN_BTN.set_button_label(FONT_SIZE, "FULLSCREEN");
    button_counter++;
    block_counter++;

    // Speed type settings
    SPEED_TYPE_TXT.setString("SPEED TYPE");
    SPEED_TYPE_TXT.setFillColor(sf::Color::White);
    SPEED_TYPE_TXT.setPosition(sf::Vector2f(CANVAS_WIDTH + MARGIN_LEFT, MARGIN_TOP + button_counter * (BTN_HEIGHT + MARGIN_BETWEEN) + label_counter * (FONT_SIZE + MARGIN_BETWEEN) + block_counter * MARGIN_TOP));
    SPEED_TYPE_TXT.setFont(FONT);
    SPEED_TYPE_TXT.setCharacterSize(FONT_SIZE);
    label_counter++;

    SPEED_TYPE_ANGULAR_BTN = ToggleButton(FONT, sf::Vector2f((MENU_WIDTH - MARGIN_LEFT - MARGIN_RIGHT) / 2, BTN_HEIGHT), sf::Vector2f(CANVAS_WIDTH + MARGIN_LEFT, MARGIN_TOP + button_counter * (BTN_HEIGHT + MARGIN_BETWEEN) + label_counter * (FONT_SIZE + MARGIN_BETWEEN) + block_counter * MARGIN_TOP), true);
    SPEED_TYPE_ANGULAR_BTN.set_button_label(FONT_SIZE, "ANGULAR");

    SPEED_TYPE_RANDOM_BTN = ToggleButton(FONT, sf::Vector2f((MENU_WIDTH - MARGIN_LEFT - MARGIN_RIGHT) / 2 - MARGIN_BETWEEN, BTN_HEIGHT), sf::Vector2f(CANVAS_WIDTH + MARGIN_LEFT + (MENU_WIDTH - MARGIN_LEFT - MARGIN_RIGHT) / 2 + MARGIN_BETWEEN, MARGIN_TOP + button_counter * (BTN_HEIGHT + MARGIN_BETWEEN) + label_counter * (FONT_SIZE + MARGIN_BETWEEN) + block_counter * MARGIN_TOP), false);
    SPEED_TYPE_RANDOM_BTN.set_button_label(FONT_SIZE, "RANDOM");
    button_counter++;

    SPEED_TYPE_ZERO_BTN = ToggleButton(FONT, sf::Vector2f((MENU_WIDTH - MARGIN_LEFT - MARGIN_RIGHT) / 2, BTN_HEIGHT), sf::Vector2f(CANVAS_WIDTH + MARGIN_LEFT, MARGIN_TOP + button_counter * (BTN_HEIGHT + MARGIN_BETWEEN) + label_counter * (FONT_SIZE + MARGIN_BETWEEN) + block_counter * MARGIN_TOP), false);
    SPEED_TYPE_ZERO_BTN.set_button_label(FONT_SIZE, "ZERO");

    SPEED_TYPE_CENTRAL_BTN = ToggleButton(FONT, sf::Vector2f((MENU_WIDTH - MARGIN_LEFT - MARGIN_RIGHT) / 2 - MARGIN_BETWEEN, BTN_HEIGHT), sf::Vector2f(CANVAS_WIDTH + MARGIN_LEFT + (MENU_WIDTH - MARGIN_LEFT - MARGIN_RIGHT) / 2 + MARGIN_BETWEEN, MARGIN_TOP + button_counter * (BTN_HEIGHT + MARGIN_BETWEEN) + label_counter * (FONT_SIZE + MARGIN_BETWEEN) + block_counter * MARGIN_TOP), false);
    SPEED_TYPE_CENTRAL_BTN.set_button_label(FONT_SIZE, "CENTRAL");
    button_counter++;
    block_counter++;

    // Test
    ONOFF_BTN = ToggleButton(FONT, sf::Vector2f(MENU_WIDTH - MARGIN_LEFT - MARGIN_RIGHT, BTN_HEIGHT), sf::Vector2f(CANVAS_WIDTH + MARGIN_LEFT, MARGIN_TOP + button_counter * (BTN_HEIGHT + MARGIN_BETWEEN) + label_counter * (FONT_SIZE + MARGIN_BETWEEN) + block_counter * MARGIN_TOP), false);
    ONOFF_BTN.set_button_label(FONT_SIZE, "ONOFF");
    button_counter++;

    // Restart simulation
    RELOAD_BTN = SimpleButton(FONT, sf::Vector2f(MENU_WIDTH - MARGIN_LEFT - MARGIN_RIGHT, BTN_HEIGHT), sf::Vector2f(CANVAS_WIDTH + MARGIN_LEFT, MARGIN_TOP + button_counter * (BTN_HEIGHT + MARGIN_BETWEEN) + label_counter * (FONT_SIZE + MARGIN_BETWEEN) + block_counter * MARGIN_TOP));
    RELOAD_BTN.set_button_label(FONT_SIZE, "RELOAD");
    button_counter++;

    // Exit
    EXIT_BTN = SimpleButton(FONT, sf::Vector2f(MENU_WIDTH - MARGIN_LEFT - MARGIN_RIGHT, BTN_HEIGHT), sf::Vector2f(CANVAS_WIDTH + MARGIN_LEFT, HEIGHT - BTN_HEIGHT - MARGIN_BOTTOM));
    EXIT_BTN.set_button_label(FONT_SIZE, "EXIT");
}

int main()
{
    sf::VideoMode screen = sf::VideoMode::getDesktopMode();
    sf::RenderWindow window(screen, "Gravitational Force Simulation", sf::Style::Fullscreen);

    recalc_sizes(screen.width, screen.height);
    init_buttons();
    reload_sim();

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            PLACEMENT_TYPE_CIRCULAR_BTN.get_button_status(window, event);
            PLACEMENT_TYPE_FULLSCREEN_BTN.get_button_status(window, event);
            SPEED_TYPE_ANGULAR_BTN.get_button_status(window, event);
            SPEED_TYPE_RANDOM_BTN.get_button_status(window, event);
            SPEED_TYPE_ZERO_BTN.get_button_status(window, event);
            SPEED_TYPE_CENTRAL_BTN.get_button_status(window, event);
            ONOFF_BTN.get_button_status(window, event);
            RELOAD_BTN.get_button_status(window, event);
            EXIT_BTN.get_button_status(window, event);

            if (PLACEMENT_TYPE_CIRCULAR_BTN.is_pressed)
            {
                PLACEMENT_TYPE_CIRCULAR_BTN.set_toggle(true);
                PLACEMENT_TYPE_FULLSCREEN_BTN.set_toggle(false);
                current_settings.PLACEMENT_TYPE = PlacementType::Circular;
            }
            else if (PLACEMENT_TYPE_FULLSCREEN_BTN.is_pressed)
            {
                PLACEMENT_TYPE_CIRCULAR_BTN.set_toggle(false);
                PLACEMENT_TYPE_FULLSCREEN_BTN.set_toggle(true);
                current_settings.PLACEMENT_TYPE = PlacementType::Fullscreen;
            }

            if (SPEED_TYPE_ANGULAR_BTN.is_pressed)
            {
                SPEED_TYPE_ANGULAR_BTN.set_toggle(true);
                SPEED_TYPE_RANDOM_BTN.set_toggle(false);
                SPEED_TYPE_ZERO_BTN.set_toggle(false);
                SPEED_TYPE_CENTRAL_BTN.set_toggle(false);
                current_settings.SPEED_TYPE = SpeedType::Angular;

            }
            else if (SPEED_TYPE_RANDOM_BTN.is_pressed)
            {
                SPEED_TYPE_ANGULAR_BTN.set_toggle(false);
                SPEED_TYPE_RANDOM_BTN.set_toggle(true);
                SPEED_TYPE_ZERO_BTN.set_toggle(false);
                SPEED_TYPE_CENTRAL_BTN.set_toggle(false);
                current_settings.SPEED_TYPE = SpeedType::Random;

            }
            else if (SPEED_TYPE_ZERO_BTN.is_pressed)
            {
                SPEED_TYPE_ANGULAR_BTN.set_toggle(false);
                SPEED_TYPE_RANDOM_BTN.set_toggle(false);
                SPEED_TYPE_ZERO_BTN.set_toggle(true);
                SPEED_TYPE_CENTRAL_BTN.set_toggle(false);
                current_settings.SPEED_TYPE = SpeedType::Zero;

            }
            else if (SPEED_TYPE_CENTRAL_BTN.is_pressed)
            {
                SPEED_TYPE_ANGULAR_BTN.set_toggle(false);
                SPEED_TYPE_RANDOM_BTN.set_toggle(false);
                SPEED_TYPE_ZERO_BTN.set_toggle(false);
                SPEED_TYPE_CENTRAL_BTN.set_toggle(true);
                current_settings.SPEED_TYPE = SpeedType::Central;

            }

            if (RELOAD_BTN.is_pressed)
                reload_sim();

            if (EXIT_BTN.is_pressed)
                window.close();
        }

        // Update positions
        update_positions(optim_grid);

        // Display
        window.clear();

        // Draw trails first to avoid trails covering particles
        if (settings.HAS_TRAIL)
        {
            for (auto& p : particles)
            {
                sf::Color current_trail_color = settings.TRAIL_COLOR;
                for (int i = 0; i < p.trail.size(); i++)
                {
                    sf::CircleShape circle(settings.TRAIL_RADIUS);
                    current_trail_color.a = ((255 * i) / settings.TRAIL_SIZE);
                    circle.setFillColor(current_trail_color);
                    circle.setPosition(p.trail[i].x - settings.TRAIL_RADIUS, p.trail[i].y - settings.TRAIL_RADIUS);
                    window.draw(circle);
                }
            }
        }

        // Draw particles
        // If not set otherwise, draw them the most effective way
        if (!(settings.VISUALIZE_SPATIAL_GRID || settings.VISUALIZE_PARTICLE_CELL))
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
            if (settings.VISUALIZE_SPATIAL_GRID)
            {
                for (int x = 0; x < optim_grid.width; x++)
                {
                    for (int y = 0; y < optim_grid.height; y++)
                    {
                        sf::Vector2f c_size(settings.COLLISION_CELL_SIZE, settings.COLLISION_CELL_SIZE);
                        sf::RectangleShape cell(c_size);

                        sf::Color fill_col = sf::Color::Transparent;
                        if (settings.VISUALIZE_CELL_MASS)
                        {
                            fill_col = map_forces_to_color(optim_grid.get(x, y).total_mass/ settings.COLLISION_CELL_SIZE);
                            fill_col.a = 140;
                        }
                        cell.setFillColor(fill_col);
                        
                        cell.setOutlineColor(sf::Color(20, 20, 20));
                        cell.setOutlineThickness(0.5f);
                        cell.setPosition(x * settings.COLLISION_CELL_SIZE - optim_grid.overflow_x/2, y * settings.COLLISION_CELL_SIZE - optim_grid.overflow_y/2);
                        window.draw(cell);
                    }
                }
            }

            // Draw particles of cells
            int idx;
            for (int x = 0; x < optim_grid.width; x++)
            {
                for (int y = 0; y < optim_grid.height; y++)
                {
                    // Calculate color based on grid position
                    sf::Color col = sf::Color::Green;
                    if ((y % 2 == 0 && x % 2 == 1) || (y % 2 == 1 && x % 2 == 0))
                        col = sf::Color::Magenta;

                    auto& current_cell = optim_grid.get(x, y);
                    for (auto it1 = current_cell.particle_indices.begin(); it1 != current_cell.particle_indices.end(); ++it1)
                    {
                        idx = get_idx_by_id(*it1);
                        if (idx < 0)
                            continue;

                        Particle& p = particles[idx];

                        sf::CircleShape circle(p.radius);

                        // Set color based on custom settings
                        if (settings.VISUALIZE_PARTICLE_CELL)
                            circle.setFillColor(col);
                        else
                            circle.setFillColor(p.color);

                        circle.setPosition(p.position.x - p.radius, p.position.y - p.radius);
                        window.draw(circle);
                    }

                    // draw center of mass
                    if (settings.VISUALIZE_COM)
                    {
                        sf::CircleShape com(5,3);
                        com.setFillColor(sf::Color::Red);
                        sf::Vector2f com_pos = optim_grid.get(x, y).center_of_mass;
                        if (com_pos.x == 0 && com_pos.y == 0)
                        {
                            int to_center = settings.COLLISION_CELL_SIZE / 2;
                            int correct_overflow_x = optim_grid.overflow_x / 2;
                            int correct_overflow_y = optim_grid.overflow_y / 2;
                            com.setPosition(x * settings.COLLISION_CELL_SIZE + to_center - 5 - correct_overflow_x, y * settings.COLLISION_CELL_SIZE + to_center - 5 - correct_overflow_y);
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

        // Menu background
        sf::RectangleShape menu_background(sf::Vector2f(MENU_WIDTH,HEIGHT));
        menu_background.setPosition(CANVAS_WIDTH, 0);
        menu_background.setFillColor(sf::Color(12,12,12));
        window.draw(menu_background);

        // Draw buttons
        window.draw(PLACEMENT_TYPE_TXT);
        PLACEMENT_TYPE_CIRCULAR_BTN.draw(window);
        PLACEMENT_TYPE_FULLSCREEN_BTN.draw(window);
        window.draw(SPEED_TYPE_TXT);
        SPEED_TYPE_ANGULAR_BTN.draw(window);
        SPEED_TYPE_RANDOM_BTN.draw(window);
        SPEED_TYPE_ZERO_BTN.draw(window);
        SPEED_TYPE_CENTRAL_BTN.draw(window);
        ONOFF_BTN.draw(window);
        RELOAD_BTN.draw(window);
        EXIT_BTN.draw(window);
        
        window.display();
    }

	return 0;
}