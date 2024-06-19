#ifndef MENU_UTILS_H
#define MENU_UTILS_H

#include "settings.h"
#include "globals.h"
#include "utils.h"
#include "key_conversion.h"

void update_fps()
{
    if (M_CLOCK.getElapsedTime().asSeconds() >= 1.f)
    {
        M_FPS = M_FRAME;
        M_FRAME = 0;
        M_CLOCK.restart();
    }

    M_FRAME++;
    FPS_TXT.setString(sf::String(std::to_string(M_FPS) + " FPS"));
}

void reload_sim()
{
    // Load new settings
    settings = current_settings;
    settings.update_dynamic_properties();

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
    MENU_WIDTH = WIDTH / 6;
    // CANVAS_WIDTH = WIDTH - MENU_WIDTH;
    CANVAS_WIDTH = width;
    if (CANVAS_WIDTH > HEIGHT)
        settings.R = 2 * HEIGHT / 5;
    else
        settings.R = 2 * CANVAS_WIDTH / 5;

    BTN_HEIGHT = HEIGHT / 48;
    TITLE_FONT_SIZE = 3 * BTN_HEIGHT / 4;
    FONT_SIZE = 4 * BTN_HEIGHT / 7;
    MARGIN_TOP = 2 * BTN_HEIGHT / 3;
    MARGIN_LEFT = BTN_HEIGHT / 2;
    MARGIN_BOTTOM = BTN_HEIGHT;
    MARGIN_RIGHT = BTN_HEIGHT / 2;
    MARGIN_BETWEEN = (MARGIN_LEFT / 2 < 10 ? 10 : MARGIN_LEFT / 2);
}

void init_ui()
{
    FONT.loadFromFile("Poppins-Bold.ttf");

    // FPS counter
    FPS_TXT.setFillColor(sf::Color::White);
    FPS_TXT.setPosition(MENU_WIDTH + MARGIN_LEFT, MARGIN_TOP);
    FPS_TXT.setFont(FONT);
    FPS_TXT.setCharacterSize(TITLE_FONT_SIZE);

    int button_counter = 0;
    int title_counter = 0;
    int label_counter = 0;
    int block_counter = 0;

    // Help text
    HELP_TXT.setString(key_to_string(RELOAD_KEY) + ": RELOAD\t\t"
        + key_to_string(SHOW_MENU_KEY) + ": SHOW/HIDE MENU\t\t"
        + key_to_string(SHOW_HELP_KEY) + ": SHOW/HIDE HELP\t\t"
        + key_to_string(SHOW_FPS_KEY) + ": SHOW/HIDE FPS\t\t"
        + key_to_string(SHOW_ALL_KEY) + ": SHOW/HIDE EVERYTHING\t\t"
        + key_to_string(EXIT_KEY) + ": EXIT");
    HELP_TXT.setFillColor(sf::Color::White);
    HELP_TXT.setFont(FONT);
    HELP_TXT.setCharacterSize(TITLE_FONT_SIZE);
    sf::FloatRect help_txt_rect = HELP_TXT.getLocalBounds();
    HELP_TXT.setOrigin(help_txt_rect.width / 2.0f, help_txt_rect.height / 2.0f);
    HELP_TXT.setPosition(WIDTH / 2, HEIGHT - TITLE_FONT_SIZE - MARGIN_BOTTOM);

    // Particle properties settings
    PARTICLE_PROPS_TXT.setString("PARTICLE PROPERTIES");
    PARTICLE_PROPS_TXT.setFillColor(sf::Color::White);
    PARTICLE_PROPS_TXT.setPosition(WIDTH - MENU_WIDTH + MARGIN_LEFT, MARGIN_TOP + button_counter * (BTN_HEIGHT + MARGIN_BETWEEN) + title_counter * (TITLE_FONT_SIZE + MARGIN_BETWEEN) + label_counter * (FONT_SIZE + MARGIN_BETWEEN) + block_counter * MARGIN_TOP);
    PARTICLE_PROPS_TXT.setFont(FONT);
    PARTICLE_PROPS_TXT.setCharacterSize(TITLE_FONT_SIZE);
    title_counter++;

    PARTICLE_NUM_TXT.setString("NUMBER OF PARTICLES");
    PARTICLE_NUM_TXT.setFillColor(sf::Color::White);
    PARTICLE_NUM_TXT.setPosition(WIDTH - MENU_WIDTH + MARGIN_LEFT, MARGIN_TOP + button_counter * (BTN_HEIGHT + MARGIN_BETWEEN) + title_counter * (TITLE_FONT_SIZE + MARGIN_BETWEEN) + label_counter * (FONT_SIZE + MARGIN_BETWEEN) + block_counter * MARGIN_TOP);
    PARTICLE_NUM_TXT.setFont(FONT);
    PARTICLE_NUM_TXT.setCharacterSize(FONT_SIZE);
    label_counter++;

    PARTICLE_NUM_TB = TextBox(FONT, sf::Vector2f(MENU_WIDTH - MARGIN_LEFT - MARGIN_RIGHT, BTN_HEIGHT), sf::Vector2f(WIDTH - MENU_WIDTH + MARGIN_LEFT, MARGIN_TOP + button_counter * (BTN_HEIGHT + MARGIN_BETWEEN) + title_counter * (TITLE_FONT_SIZE + MARGIN_BETWEEN) + label_counter * (FONT_SIZE + MARGIN_BETWEEN) + block_counter * MARGIN_TOP), settings.N, "int");
    PARTICLE_NUM_TB.set_button_label(FONT_SIZE, std::to_string(settings.N));
    button_counter++;

    PARTICLE_RADIUS_TXT.setString("RADIUS");
    PARTICLE_RADIUS_TXT.setFillColor(sf::Color::White);
    PARTICLE_RADIUS_TXT.setPosition(WIDTH - MENU_WIDTH + MARGIN_LEFT, MARGIN_TOP + button_counter * (BTN_HEIGHT + MARGIN_BETWEEN) + title_counter * (TITLE_FONT_SIZE + MARGIN_BETWEEN) + label_counter * (FONT_SIZE + MARGIN_BETWEEN) + block_counter * MARGIN_TOP);
    PARTICLE_RADIUS_TXT.setFont(FONT);
    PARTICLE_RADIUS_TXT.setCharacterSize(FONT_SIZE);

    PARTICLE_MASS_TXT.setString("MASS");
    PARTICLE_MASS_TXT.setFillColor(sf::Color::White);
    PARTICLE_MASS_TXT.setPosition(WIDTH - MENU_WIDTH + MARGIN_LEFT + (MENU_WIDTH - MARGIN_LEFT - MARGIN_RIGHT) / 2 + MARGIN_BETWEEN, MARGIN_TOP + button_counter * (BTN_HEIGHT + MARGIN_BETWEEN) + title_counter * (TITLE_FONT_SIZE + MARGIN_BETWEEN) + label_counter * (FONT_SIZE + MARGIN_BETWEEN) + block_counter * MARGIN_TOP);
    PARTICLE_MASS_TXT.setFont(FONT);
    PARTICLE_MASS_TXT.setCharacterSize(FONT_SIZE);
    label_counter++;

    PARTICLE_RADIUS_TB = TextBox(FONT, sf::Vector2f((MENU_WIDTH - MARGIN_LEFT - MARGIN_RIGHT) / 2, BTN_HEIGHT), sf::Vector2f(WIDTH - MENU_WIDTH + MARGIN_LEFT, MARGIN_TOP + button_counter * (BTN_HEIGHT + MARGIN_BETWEEN) + title_counter * (TITLE_FONT_SIZE + MARGIN_BETWEEN) + label_counter * (FONT_SIZE + MARGIN_BETWEEN) + block_counter * MARGIN_TOP), settings.RADIUS, "int");
    PARTICLE_RADIUS_TB.set_button_label(FONT_SIZE, std::to_string(settings.RADIUS));

    PARTICLE_MASS_TB = TextBox(FONT, sf::Vector2f((MENU_WIDTH - MARGIN_LEFT - MARGIN_RIGHT) / 2 - MARGIN_BETWEEN, BTN_HEIGHT), sf::Vector2f(WIDTH - MENU_WIDTH + MARGIN_LEFT + (MENU_WIDTH - MARGIN_LEFT - MARGIN_RIGHT) / 2 + MARGIN_BETWEEN, MARGIN_TOP + button_counter * (BTN_HEIGHT + MARGIN_BETWEEN) + title_counter * (TITLE_FONT_SIZE + MARGIN_BETWEEN) + label_counter * (FONT_SIZE + MARGIN_BETWEEN) + block_counter * MARGIN_TOP), settings.MASS, "double");
    PARTICLE_MASS_TB.set_button_label(FONT_SIZE, std::to_string(settings.MASS));
    button_counter++;
    block_counter++;

    // Placement type settings
    PLACEMENT_TYPE_TXT.setString("PLACEMENT TYPE");
    PLACEMENT_TYPE_TXT.setFillColor(sf::Color::White);
    PLACEMENT_TYPE_TXT.setPosition(WIDTH - MENU_WIDTH + MARGIN_LEFT, MARGIN_TOP + button_counter * (BTN_HEIGHT + MARGIN_BETWEEN) + title_counter * (TITLE_FONT_SIZE + MARGIN_BETWEEN) + label_counter * (FONT_SIZE + MARGIN_BETWEEN) + block_counter * MARGIN_TOP);
    PLACEMENT_TYPE_TXT.setFont(FONT);
    PLACEMENT_TYPE_TXT.setCharacterSize(TITLE_FONT_SIZE);
    title_counter++;

    PLACEMENT_TYPE_CIRCULAR_BTN = ToggleButton(FONT, sf::Vector2f((MENU_WIDTH - MARGIN_LEFT - MARGIN_RIGHT) / 2, BTN_HEIGHT), sf::Vector2f(WIDTH - MENU_WIDTH + MARGIN_LEFT, MARGIN_TOP + button_counter * (BTN_HEIGHT + MARGIN_BETWEEN) + title_counter * (TITLE_FONT_SIZE + MARGIN_BETWEEN) + label_counter * (FONT_SIZE + MARGIN_BETWEEN) + block_counter * MARGIN_TOP), true);
    PLACEMENT_TYPE_CIRCULAR_BTN.set_button_label(FONT_SIZE, "CIRCULAR");

    PLACEMENT_TYPE_FULLSCREEN_BTN = ToggleButton(FONT, sf::Vector2f((MENU_WIDTH - MARGIN_LEFT - MARGIN_RIGHT) / 2 - MARGIN_BETWEEN, BTN_HEIGHT), sf::Vector2f(WIDTH - MENU_WIDTH + MARGIN_LEFT + (MENU_WIDTH - MARGIN_LEFT - MARGIN_RIGHT) / 2 + MARGIN_BETWEEN, MARGIN_TOP + button_counter * (BTN_HEIGHT + MARGIN_BETWEEN) + title_counter * (TITLE_FONT_SIZE + MARGIN_BETWEEN) + label_counter * (FONT_SIZE + MARGIN_BETWEEN) + block_counter * MARGIN_TOP), false);
    PLACEMENT_TYPE_FULLSCREEN_BTN.set_button_label(FONT_SIZE, "FULLSCREEN");
    button_counter++;
    block_counter++;

    // Speed type settings
    SPEED_TYPE_TXT.setString("SPEED TYPE");
    SPEED_TYPE_TXT.setFillColor(sf::Color::White);
    SPEED_TYPE_TXT.setPosition(WIDTH - MENU_WIDTH + MARGIN_LEFT, MARGIN_TOP + button_counter * (BTN_HEIGHT + MARGIN_BETWEEN) + title_counter * (TITLE_FONT_SIZE + MARGIN_BETWEEN) + label_counter * (FONT_SIZE + MARGIN_BETWEEN) + block_counter * MARGIN_TOP);
    SPEED_TYPE_TXT.setFont(FONT);
    SPEED_TYPE_TXT.setCharacterSize(TITLE_FONT_SIZE);
    title_counter++;

    SPEED_TYPE_ANGULAR_BTN = ToggleButton(FONT, sf::Vector2f((MENU_WIDTH - MARGIN_LEFT - MARGIN_RIGHT) / 2, BTN_HEIGHT), sf::Vector2f(WIDTH - MENU_WIDTH + MARGIN_LEFT, MARGIN_TOP + button_counter * (BTN_HEIGHT + MARGIN_BETWEEN) + title_counter * (TITLE_FONT_SIZE + MARGIN_BETWEEN) + label_counter * (FONT_SIZE + MARGIN_BETWEEN) + block_counter * MARGIN_TOP), true);
    SPEED_TYPE_ANGULAR_BTN.set_button_label(FONT_SIZE, "ANGULAR");

    SPEED_TYPE_RANDOM_BTN = ToggleButton(FONT, sf::Vector2f((MENU_WIDTH - MARGIN_LEFT - MARGIN_RIGHT) / 2 - MARGIN_BETWEEN, BTN_HEIGHT), sf::Vector2f(WIDTH - MENU_WIDTH + MARGIN_LEFT + (MENU_WIDTH - MARGIN_LEFT - MARGIN_RIGHT) / 2 + MARGIN_BETWEEN, MARGIN_TOP + button_counter * (BTN_HEIGHT + MARGIN_BETWEEN) + title_counter * (TITLE_FONT_SIZE + MARGIN_BETWEEN) + label_counter * (FONT_SIZE + MARGIN_BETWEEN) + block_counter * MARGIN_TOP), false);
    SPEED_TYPE_RANDOM_BTN.set_button_label(FONT_SIZE, "RANDOM");
    button_counter++;

    SPEED_TYPE_ZERO_BTN = ToggleButton(FONT, sf::Vector2f((MENU_WIDTH - MARGIN_LEFT - MARGIN_RIGHT) / 2, BTN_HEIGHT), sf::Vector2f(WIDTH - MENU_WIDTH + MARGIN_LEFT, MARGIN_TOP + button_counter * (BTN_HEIGHT + MARGIN_BETWEEN) + title_counter * (TITLE_FONT_SIZE + MARGIN_BETWEEN) + label_counter * (FONT_SIZE + MARGIN_BETWEEN) + block_counter * MARGIN_TOP), false);
    SPEED_TYPE_ZERO_BTN.set_button_label(FONT_SIZE, "ZERO");

    SPEED_TYPE_CENTRAL_BTN = ToggleButton(FONT, sf::Vector2f((MENU_WIDTH - MARGIN_LEFT - MARGIN_RIGHT) / 2 - MARGIN_BETWEEN, BTN_HEIGHT), sf::Vector2f(WIDTH - MENU_WIDTH + MARGIN_LEFT + (MENU_WIDTH - MARGIN_LEFT - MARGIN_RIGHT) / 2 + MARGIN_BETWEEN, MARGIN_TOP + button_counter * (BTN_HEIGHT + MARGIN_BETWEEN) + title_counter * (TITLE_FONT_SIZE + MARGIN_BETWEEN) + label_counter * (FONT_SIZE + MARGIN_BETWEEN) + block_counter * MARGIN_TOP), false);
    SPEED_TYPE_CENTRAL_BTN.set_button_label(FONT_SIZE, "CENTRAL");
    button_counter++;
    block_counter++;

    // Border settings
    BORDER_TXT.setString("BORDER SETTINGS");
    BORDER_TXT.setFillColor(sf::Color::White);
    BORDER_TXT.setPosition(WIDTH - MENU_WIDTH + MARGIN_LEFT, MARGIN_TOP + button_counter * (BTN_HEIGHT + MARGIN_BETWEEN) + title_counter * (TITLE_FONT_SIZE + MARGIN_BETWEEN) + label_counter * (FONT_SIZE + MARGIN_BETWEEN) + block_counter * MARGIN_TOP);
    BORDER_TXT.setFont(FONT);
    BORDER_TXT.setCharacterSize(TITLE_FONT_SIZE);
    title_counter++;

    HAS_BORDERS_BTN = ToggleButton(FONT, sf::Vector2f(MENU_WIDTH - MARGIN_LEFT - MARGIN_RIGHT, BTN_HEIGHT), sf::Vector2f(WIDTH - MENU_WIDTH + MARGIN_LEFT, MARGIN_TOP + button_counter * (BTN_HEIGHT + MARGIN_BETWEEN) + title_counter * (TITLE_FONT_SIZE + MARGIN_BETWEEN) + label_counter * (FONT_SIZE + MARGIN_BETWEEN) + block_counter * MARGIN_TOP), settings.HAS_BORDERS);
    HAS_BORDERS_BTN.set_button_label(FONT_SIZE, "BORDERS ON/OFF");
    button_counter++;
    block_counter++;

    // Trail settings
    TRAIL_TXT.setString("TRAIL SETTINGS");
    TRAIL_TXT.setFillColor(sf::Color::White);
    TRAIL_TXT.setPosition(WIDTH - MENU_WIDTH + MARGIN_LEFT, MARGIN_TOP + button_counter * (BTN_HEIGHT + MARGIN_BETWEEN) + title_counter * (TITLE_FONT_SIZE + MARGIN_BETWEEN) + label_counter * (FONT_SIZE + MARGIN_BETWEEN) + block_counter * MARGIN_TOP);
    TRAIL_TXT.setFont(FONT);
    TRAIL_TXT.setCharacterSize(TITLE_FONT_SIZE);
    title_counter++;

    HAS_TRAIL_BTN = ToggleButton(FONT, sf::Vector2f(MENU_WIDTH - MARGIN_LEFT - MARGIN_RIGHT, BTN_HEIGHT), sf::Vector2f(WIDTH - MENU_WIDTH + MARGIN_LEFT, MARGIN_TOP + button_counter * (BTN_HEIGHT + MARGIN_BETWEEN) + title_counter * (TITLE_FONT_SIZE + MARGIN_BETWEEN) + label_counter * (FONT_SIZE + MARGIN_BETWEEN) + block_counter * MARGIN_TOP), settings.HAS_TRAIL);
    HAS_TRAIL_BTN.set_button_label(FONT_SIZE, "TRAILS ON/OFF");
    button_counter++;
    block_counter++;

    // Gravity settings
    GRAVITY_TXT.setString("GRAVITY SETTINGS");
    GRAVITY_TXT.setFillColor(sf::Color::White);
    GRAVITY_TXT.setPosition(WIDTH - MENU_WIDTH + MARGIN_LEFT, MARGIN_TOP + button_counter * (BTN_HEIGHT + MARGIN_BETWEEN) + title_counter * (TITLE_FONT_SIZE + MARGIN_BETWEEN) + label_counter * (FONT_SIZE + MARGIN_BETWEEN) + block_counter * MARGIN_TOP);
    GRAVITY_TXT.setFont(FONT);
    GRAVITY_TXT.setCharacterSize(TITLE_FONT_SIZE);
    title_counter++;

    HAS_GRAVITY_BTN = ToggleButton(FONT, sf::Vector2f(MENU_WIDTH - MARGIN_LEFT - MARGIN_RIGHT, BTN_HEIGHT), sf::Vector2f(WIDTH - MENU_WIDTH + MARGIN_LEFT, MARGIN_TOP + button_counter * (BTN_HEIGHT + MARGIN_BETWEEN) + title_counter * (TITLE_FONT_SIZE + MARGIN_BETWEEN) + label_counter * (FONT_SIZE + MARGIN_BETWEEN) + block_counter * MARGIN_TOP), settings.HAS_GRAVITY);
    HAS_GRAVITY_BTN.set_button_label(FONT_SIZE, "GRAVITY ON/OFF");
    button_counter++;
    block_counter++;

    // Damping settings
    DAMPING_TXT.setString("DAMPING SETTINGS");
    DAMPING_TXT.setFillColor(sf::Color::White);
    DAMPING_TXT.setPosition(WIDTH - MENU_WIDTH + MARGIN_LEFT, MARGIN_TOP + button_counter * (BTN_HEIGHT + MARGIN_BETWEEN) + title_counter * (TITLE_FONT_SIZE + MARGIN_BETWEEN) + label_counter * (FONT_SIZE + MARGIN_BETWEEN) + block_counter * MARGIN_TOP);
    DAMPING_TXT.setFont(FONT);
    DAMPING_TXT.setCharacterSize(TITLE_FONT_SIZE);
    title_counter++;

    HAS_DAMPING_BTN = ToggleButton(FONT, sf::Vector2f(MENU_WIDTH - MARGIN_LEFT - MARGIN_RIGHT, BTN_HEIGHT), sf::Vector2f(WIDTH - MENU_WIDTH + MARGIN_LEFT, MARGIN_TOP + button_counter * (BTN_HEIGHT + MARGIN_BETWEEN) + title_counter * (TITLE_FONT_SIZE + MARGIN_BETWEEN) + label_counter * (FONT_SIZE + MARGIN_BETWEEN) + block_counter * MARGIN_TOP), settings.HAS_DAMPING);
    HAS_DAMPING_BTN.set_button_label(FONT_SIZE, "DAMPING ON/OFF");
    button_counter++;

    DAMPING_DIST_TXT.setString("DISTANCE");
    DAMPING_DIST_TXT.setFillColor(sf::Color::White);
    DAMPING_DIST_TXT.setPosition(WIDTH - MENU_WIDTH + MARGIN_LEFT, MARGIN_TOP + button_counter * (BTN_HEIGHT + MARGIN_BETWEEN) + title_counter * (TITLE_FONT_SIZE + MARGIN_BETWEEN) + label_counter * (FONT_SIZE + MARGIN_BETWEEN) + block_counter * MARGIN_TOP);
    DAMPING_DIST_TXT.setFont(FONT);
    DAMPING_DIST_TXT.setCharacterSize(FONT_SIZE);

    DAMPING_COEFF_TXT.setString("COEFFICIENT");
    DAMPING_COEFF_TXT.setFillColor(sf::Color::White);
    DAMPING_COEFF_TXT.setPosition(WIDTH - MENU_WIDTH + MARGIN_LEFT + (MENU_WIDTH - MARGIN_LEFT - MARGIN_RIGHT) / 2 + MARGIN_BETWEEN, MARGIN_TOP + button_counter * (BTN_HEIGHT + MARGIN_BETWEEN) + title_counter * (TITLE_FONT_SIZE + MARGIN_BETWEEN) + label_counter * (FONT_SIZE + MARGIN_BETWEEN) + block_counter * MARGIN_TOP);
    DAMPING_COEFF_TXT.setFont(FONT);
    DAMPING_COEFF_TXT.setCharacterSize(FONT_SIZE);
    label_counter++;

    DAMPING_DIST_TB = TextBox(FONT, sf::Vector2f((MENU_WIDTH - MARGIN_LEFT - MARGIN_RIGHT) / 2, BTN_HEIGHT), sf::Vector2f(WIDTH - MENU_WIDTH + MARGIN_LEFT, MARGIN_TOP + button_counter * (BTN_HEIGHT + MARGIN_BETWEEN) + title_counter * (TITLE_FONT_SIZE + MARGIN_BETWEEN) + label_counter * (FONT_SIZE + MARGIN_BETWEEN) + block_counter * MARGIN_TOP), settings.DAMPING_DIST, "double");
    DAMPING_DIST_TB.set_button_label(FONT_SIZE, std::to_string(settings.DAMPING_DIST));

    DAMPING_COEFF_TB = TextBox(FONT, sf::Vector2f((MENU_WIDTH - MARGIN_LEFT - MARGIN_RIGHT) / 2 - MARGIN_BETWEEN, BTN_HEIGHT), sf::Vector2f(WIDTH - MENU_WIDTH + MARGIN_LEFT + (MENU_WIDTH - MARGIN_LEFT - MARGIN_RIGHT) / 2 + MARGIN_BETWEEN, MARGIN_TOP + button_counter * (BTN_HEIGHT + MARGIN_BETWEEN) + title_counter * (TITLE_FONT_SIZE + MARGIN_BETWEEN) + label_counter * (FONT_SIZE + MARGIN_BETWEEN) + block_counter * MARGIN_TOP), settings.DAMPING_COEFF, "double");
    DAMPING_COEFF_TB.set_button_label(FONT_SIZE, std::to_string(settings.DAMPING_COEFF));
    button_counter++;
    block_counter++;

    // Collision settings
    COLLISION_TXT.setString("COLLISION SETTINGS");
    COLLISION_TXT.setFillColor(sf::Color::White);
    COLLISION_TXT.setPosition(WIDTH - MENU_WIDTH + MARGIN_LEFT, MARGIN_TOP + button_counter * (BTN_HEIGHT + MARGIN_BETWEEN) + title_counter * (TITLE_FONT_SIZE + MARGIN_BETWEEN) + label_counter * (FONT_SIZE + MARGIN_BETWEEN) + block_counter * MARGIN_TOP);
    COLLISION_TXT.setFont(FONT);
    COLLISION_TXT.setCharacterSize(TITLE_FONT_SIZE);
    title_counter++;

    HAS_OVERLAPCHECK_BTN = ToggleButton(FONT, sf::Vector2f(MENU_WIDTH - MARGIN_LEFT - MARGIN_RIGHT, BTN_HEIGHT), sf::Vector2f(WIDTH - MENU_WIDTH + MARGIN_LEFT, MARGIN_TOP + button_counter * (BTN_HEIGHT + MARGIN_BETWEEN) + title_counter * (TITLE_FONT_SIZE + MARGIN_BETWEEN) + label_counter * (FONT_SIZE + MARGIN_BETWEEN) + block_counter * MARGIN_TOP), settings.HAS_OVERLAPCHECK);
    HAS_OVERLAPCHECK_BTN.set_button_label(FONT_SIZE, "OVERLAP CHECK ON/OFF");
    button_counter++;

    HAS_BOUNCEOFF_BTN = ToggleButton(FONT, sf::Vector2f(MENU_WIDTH - MARGIN_LEFT - MARGIN_RIGHT, BTN_HEIGHT), sf::Vector2f(WIDTH - MENU_WIDTH + MARGIN_LEFT, MARGIN_TOP + button_counter * (BTN_HEIGHT + MARGIN_BETWEEN) + title_counter * (TITLE_FONT_SIZE + MARGIN_BETWEEN) + label_counter * (FONT_SIZE + MARGIN_BETWEEN) + block_counter * MARGIN_TOP), settings.HAS_BOUNCEOFF);
    HAS_BOUNCEOFF_BTN.set_button_label(FONT_SIZE, "BOUNCE ON/OFF");
    button_counter++;
    
    COLLISION_THRESHOLD_TXT.setString("THRESHOLD");
    COLLISION_THRESHOLD_TXT.setFillColor(sf::Color::White);
    COLLISION_THRESHOLD_TXT.setPosition(WIDTH - MENU_WIDTH + MARGIN_LEFT, MARGIN_TOP + button_counter * (BTN_HEIGHT + MARGIN_BETWEEN) + title_counter * (TITLE_FONT_SIZE + MARGIN_BETWEEN) + label_counter * (FONT_SIZE + MARGIN_BETWEEN) + block_counter * MARGIN_TOP);
    COLLISION_THRESHOLD_TXT.setFont(FONT);
    COLLISION_THRESHOLD_TXT.setCharacterSize(FONT_SIZE);

    COLLISION_ITERATIONS_TXT.setString("ITERATIONS");
    COLLISION_ITERATIONS_TXT.setFillColor(sf::Color::White);
    COLLISION_ITERATIONS_TXT.setPosition(WIDTH - MENU_WIDTH + MARGIN_LEFT + (MENU_WIDTH - MARGIN_LEFT - MARGIN_RIGHT) / 2 + MARGIN_BETWEEN, MARGIN_TOP + button_counter * (BTN_HEIGHT + MARGIN_BETWEEN) + title_counter * (TITLE_FONT_SIZE + MARGIN_BETWEEN) + label_counter * (FONT_SIZE + MARGIN_BETWEEN) + block_counter * MARGIN_TOP);
    COLLISION_ITERATIONS_TXT.setFont(FONT);
    COLLISION_ITERATIONS_TXT.setCharacterSize(FONT_SIZE);
    label_counter++;

    COLLISION_THRESHOLD_TB = TextBox(FONT, sf::Vector2f((MENU_WIDTH - MARGIN_LEFT - MARGIN_RIGHT) / 2, BTN_HEIGHT), sf::Vector2f(WIDTH - MENU_WIDTH + MARGIN_LEFT, MARGIN_TOP + button_counter * (BTN_HEIGHT + MARGIN_BETWEEN) + title_counter * (TITLE_FONT_SIZE + MARGIN_BETWEEN) + label_counter * (FONT_SIZE + MARGIN_BETWEEN) + block_counter * MARGIN_TOP), settings.COLLISION_THRESHOLD, "double");
    COLLISION_THRESHOLD_TB.set_button_label(FONT_SIZE, std::to_string(settings.COLLISION_THRESHOLD));

    COLLISION_ITERATIONS_TB = TextBox(FONT, sf::Vector2f((MENU_WIDTH - MARGIN_LEFT - MARGIN_RIGHT) / 2 - MARGIN_BETWEEN, BTN_HEIGHT), sf::Vector2f(WIDTH - MENU_WIDTH + MARGIN_LEFT + (MENU_WIDTH - MARGIN_LEFT - MARGIN_RIGHT) / 2 + MARGIN_BETWEEN, MARGIN_TOP + button_counter * (BTN_HEIGHT + MARGIN_BETWEEN) + title_counter * (TITLE_FONT_SIZE + MARGIN_BETWEEN) + label_counter * (FONT_SIZE + MARGIN_BETWEEN) + block_counter * MARGIN_TOP), settings.COLLISION_ITERATIONS, "int");
    COLLISION_ITERATIONS_TB.set_button_label(FONT_SIZE, std::to_string(settings.COLLISION_ITERATIONS));
    button_counter++;
    block_counter++;

    // Grid visualization settings
    GRID_TXT.setString("OPTIMIZATION GRID SETTINGS");
    GRID_TXT.setFillColor(sf::Color::White);
    GRID_TXT.setPosition(WIDTH - MENU_WIDTH + MARGIN_LEFT, MARGIN_TOP + button_counter * (BTN_HEIGHT + MARGIN_BETWEEN) + title_counter * (TITLE_FONT_SIZE + MARGIN_BETWEEN) + label_counter * (FONT_SIZE + MARGIN_BETWEEN) + block_counter * MARGIN_TOP);
    GRID_TXT.setFont(FONT);
    GRID_TXT.setCharacterSize(TITLE_FONT_SIZE);
    title_counter++;
    
    VISUALIZE_GRID_BTN = ToggleButton(FONT, sf::Vector2f(MENU_WIDTH - MARGIN_LEFT - MARGIN_RIGHT, BTN_HEIGHT), sf::Vector2f(WIDTH - MENU_WIDTH + MARGIN_LEFT, MARGIN_TOP + button_counter * (BTN_HEIGHT + MARGIN_BETWEEN) + title_counter * (TITLE_FONT_SIZE + MARGIN_BETWEEN) + label_counter * (FONT_SIZE + MARGIN_BETWEEN) + block_counter * MARGIN_TOP), settings.VISUALIZE_SPATIAL_GRID);
    VISUALIZE_GRID_BTN.set_button_label(FONT_SIZE, "VISUALIZE GRID ON/OFF");
    button_counter++;

    VISUALIZE_PARTICLE_CELL_BTN = ToggleButton(FONT, sf::Vector2f(MENU_WIDTH - MARGIN_LEFT - MARGIN_RIGHT, BTN_HEIGHT), sf::Vector2f(WIDTH - MENU_WIDTH + MARGIN_LEFT, MARGIN_TOP + button_counter * (BTN_HEIGHT + MARGIN_BETWEEN) + title_counter * (TITLE_FONT_SIZE + MARGIN_BETWEEN) + label_counter * (FONT_SIZE + MARGIN_BETWEEN) + block_counter * MARGIN_TOP), settings.VISUALIZE_PARTICLE_CELL);
    VISUALIZE_PARTICLE_CELL_BTN.set_button_label(FONT_SIZE, "VISUALIZE PARTICLES' CELL ON/OFF");
    button_counter++;

    VISUALIZE_CELL_MASS_BTN = ToggleButton(FONT, sf::Vector2f(MENU_WIDTH - MARGIN_LEFT - MARGIN_RIGHT, BTN_HEIGHT), sf::Vector2f(WIDTH - MENU_WIDTH + MARGIN_LEFT, MARGIN_TOP + button_counter * (BTN_HEIGHT + MARGIN_BETWEEN) + title_counter * (TITLE_FONT_SIZE + MARGIN_BETWEEN) + label_counter * (FONT_SIZE + MARGIN_BETWEEN) + block_counter * MARGIN_TOP), settings.VISUALIZE_CELL_MASS);
    VISUALIZE_CELL_MASS_BTN.set_button_label(FONT_SIZE, "VISUALIZE CELLS' MASS ON/OFF");
    VISUALIZE_CELL_MASS_BTN.is_active = false;
    button_counter++;

    VISUALIZE_COM_BTN = ToggleButton(FONT, sf::Vector2f(MENU_WIDTH - MARGIN_LEFT - MARGIN_RIGHT, BTN_HEIGHT), sf::Vector2f(WIDTH - MENU_WIDTH + MARGIN_LEFT, MARGIN_TOP + button_counter * (BTN_HEIGHT + MARGIN_BETWEEN) + title_counter * (TITLE_FONT_SIZE + MARGIN_BETWEEN) + label_counter * (FONT_SIZE + MARGIN_BETWEEN) + block_counter * MARGIN_TOP), settings.VISUALIZE_COM);
    VISUALIZE_COM_BTN.set_button_label(FONT_SIZE, "VISUALIZE CELLS' CENTER OF MASS ON/OFF");
    VISUALIZE_COM_BTN.is_active = false;
    button_counter++;

    COLLISION_CELL_SIZE_TXT.setString("CELL SIZE");
    COLLISION_CELL_SIZE_TXT.setFillColor(sf::Color::White);
    COLLISION_CELL_SIZE_TXT.setPosition(WIDTH - MENU_WIDTH + MARGIN_LEFT, MARGIN_TOP + button_counter * (BTN_HEIGHT + MARGIN_BETWEEN) + title_counter * (TITLE_FONT_SIZE + MARGIN_BETWEEN) + label_counter * (FONT_SIZE + MARGIN_BETWEEN) + block_counter * MARGIN_TOP);
    COLLISION_CELL_SIZE_TXT.setFont(FONT);
    COLLISION_CELL_SIZE_TXT.setCharacterSize(FONT_SIZE);
    label_counter++;

    COLLISION_CELL_SIZE_TB = TextBox(FONT, sf::Vector2f(MENU_WIDTH - MARGIN_LEFT - MARGIN_RIGHT, BTN_HEIGHT), sf::Vector2f(WIDTH - MENU_WIDTH + MARGIN_LEFT, MARGIN_TOP + button_counter * (BTN_HEIGHT + MARGIN_BETWEEN) + title_counter * (TITLE_FONT_SIZE + MARGIN_BETWEEN) + label_counter * (FONT_SIZE + MARGIN_BETWEEN) + block_counter * MARGIN_TOP), settings.COLLISION_CELL_SIZE, "int");
    COLLISION_CELL_SIZE_TB.set_button_label(FONT_SIZE, std::to_string(settings.COLLISION_CELL_SIZE));
    button_counter++;

    // Restart simulation
    RELOAD_REQUIRED_TXT.setString("RELOAD REQUIRED");
    RELOAD_REQUIRED_TXT.setFillColor(sf::Color::Red);
    RELOAD_REQUIRED_TXT.setPosition(WIDTH - MENU_WIDTH + MARGIN_LEFT, MARGIN_TOP + button_counter * (BTN_HEIGHT + MARGIN_BETWEEN) + title_counter * (TITLE_FONT_SIZE + MARGIN_BETWEEN) + label_counter * (FONT_SIZE + MARGIN_BETWEEN) + block_counter * MARGIN_TOP);
    RELOAD_REQUIRED_TXT.setFont(FONT);
    RELOAD_REQUIRED_TXT.setCharacterSize(FONT_SIZE);
    label_counter++;

    RELOAD_BTN = SimpleButton(FONT, sf::Vector2f(MENU_WIDTH - MARGIN_LEFT - MARGIN_RIGHT, BTN_HEIGHT), sf::Vector2f(WIDTH - MENU_WIDTH + MARGIN_LEFT, MARGIN_TOP + button_counter * (BTN_HEIGHT + MARGIN_BETWEEN) + title_counter * (TITLE_FONT_SIZE + MARGIN_BETWEEN) + label_counter * (FONT_SIZE + MARGIN_BETWEEN) + block_counter * MARGIN_TOP));
    RELOAD_BTN.set_button_label(FONT_SIZE, "RELOAD");
    button_counter++;

    // Exit
    EXIT_BTN = SimpleButton(FONT, sf::Vector2f(MENU_WIDTH - MARGIN_LEFT - MARGIN_RIGHT, BTN_HEIGHT), sf::Vector2f(WIDTH - MENU_WIDTH + MARGIN_LEFT, HEIGHT - BTN_HEIGHT - MARGIN_BOTTOM));
    EXIT_BTN.set_button_label(FONT_SIZE, "EXIT");
}

bool check_reload_required()
{
    if (settings.PLACEMENT_TYPE != current_settings.PLACEMENT_TYPE || settings.SPEED_TYPE != current_settings.SPEED_TYPE
        || settings.N != current_settings.N || settings.RADIUS != current_settings.RADIUS || settings.MASS != current_settings.MASS
        || settings.COLLISION_CELL_SIZE != current_settings.COLLISION_CELL_SIZE)
        return true;

    return false;
}

void draw_menu(sf::RenderWindow& window)
{
    // Menu left background
    sf::RectangleShape menu_left_background(sf::Vector2f(MENU_WIDTH, HEIGHT));
    menu_left_background.setPosition(0, 0);
    menu_left_background.setFillColor(sf::Color(12, 12, 12, 200));
    window.draw(menu_left_background);

    // Menu right background
    sf::RectangleShape menu_right_background(sf::Vector2f(MENU_WIDTH, HEIGHT));
    menu_right_background.setPosition(WIDTH - MENU_WIDTH, 0);
    menu_right_background.setFillColor(sf::Color(12, 12, 12, 200));
    window.draw(menu_right_background);

    window.draw(PARTICLE_NUM_TXT);
    PARTICLE_NUM_TB.draw(window);

    window.draw(PARTICLE_PROPS_TXT);
    window.draw(PARTICLE_RADIUS_TXT);
    PARTICLE_RADIUS_TB.draw(window);
    window.draw(PARTICLE_MASS_TXT);
    PARTICLE_MASS_TB.draw(window);

    window.draw(PLACEMENT_TYPE_TXT);
    PLACEMENT_TYPE_CIRCULAR_BTN.draw(window);
    PLACEMENT_TYPE_FULLSCREEN_BTN.draw(window);

    window.draw(SPEED_TYPE_TXT);
    SPEED_TYPE_ANGULAR_BTN.draw(window);
    SPEED_TYPE_RANDOM_BTN.draw(window);
    SPEED_TYPE_ZERO_BTN.draw(window);
    SPEED_TYPE_CENTRAL_BTN.draw(window);

    window.draw(BORDER_TXT);
    HAS_BORDERS_BTN.draw(window);

    window.draw(TRAIL_TXT);
    HAS_TRAIL_BTN.draw(window);

    window.draw(GRAVITY_TXT);
    HAS_GRAVITY_BTN.draw(window);

    window.draw(DAMPING_TXT);
    HAS_DAMPING_BTN.draw(window);
    window.draw(DAMPING_DIST_TXT);
    DAMPING_DIST_TB.draw(window);
    window.draw(DAMPING_COEFF_TXT);
    DAMPING_COEFF_TB.draw(window);

    window.draw(COLLISION_TXT);
    HAS_OVERLAPCHECK_BTN.draw(window);
    HAS_BOUNCEOFF_BTN.draw(window);
    window.draw(COLLISION_THRESHOLD_TXT);
    COLLISION_THRESHOLD_TB.draw(window);
    window.draw(COLLISION_ITERATIONS_TXT);
    COLLISION_ITERATIONS_TB.draw(window);

    window.draw(GRID_TXT);
    VISUALIZE_GRID_BTN.draw(window);
    VISUALIZE_PARTICLE_CELL_BTN.draw(window);
    VISUALIZE_CELL_MASS_BTN.draw(window);
    VISUALIZE_COM_BTN.draw(window);
    window.draw(COLLISION_CELL_SIZE_TXT);
    COLLISION_CELL_SIZE_TB.draw(window);

    if (check_reload_required())
        window.draw(RELOAD_REQUIRED_TXT);

    RELOAD_BTN.draw(window);
    EXIT_BTN.draw(window);
}

void draw_fps(sf::RenderWindow& window)
{
    // FPS
    window.draw(FPS_TXT);
}

void draw_help(sf::RenderWindow& window)
{
    window.draw(HELP_TXT);
}

void untoggle_textboxes()
{
    PARTICLE_NUM_TB.set_toggle(false);
    current_settings.N = (int)PARTICLE_NUM_TB.value;
    PARTICLE_RADIUS_TB.set_toggle(false);
    current_settings.RADIUS = (int)PARTICLE_RADIUS_TB.value;
    PARTICLE_MASS_TB.set_toggle(false);
    current_settings.MASS = PARTICLE_MASS_TB.value;

    COLLISION_THRESHOLD_TB.set_toggle(false);
    current_settings.COLLISION_THRESHOLD = COLLISION_THRESHOLD_TB.value;
    settings.COLLISION_THRESHOLD = COLLISION_THRESHOLD_TB.value;
    COLLISION_ITERATIONS_TB.set_toggle(false);
    current_settings.COLLISION_ITERATIONS = (int)COLLISION_ITERATIONS_TB.value;
    settings.COLLISION_ITERATIONS = (int)COLLISION_ITERATIONS_TB.value;

    DAMPING_DIST_TB.set_toggle(false);
    current_settings.DAMPING_DIST = DAMPING_DIST_TB.value;
    settings.DAMPING_DIST = DAMPING_DIST_TB.value;
    DAMPING_COEFF_TB.set_toggle(false);
    current_settings.DAMPING_COEFF = DAMPING_COEFF_TB.value;
    settings.DAMPING_COEFF = DAMPING_COEFF_TB.value;

    COLLISION_CELL_SIZE_TB.set_toggle(false);
    current_settings.COLLISION_CELL_SIZE = COLLISION_CELL_SIZE_TB.value;
}

void handle_textbox_input(const sf::Event& event)
{
    PARTICLE_NUM_TB.handle_input(event);
    PARTICLE_RADIUS_TB.handle_input(event);
    PARTICLE_MASS_TB.handle_input(event);

    COLLISION_THRESHOLD_TB.handle_input(event);
    COLLISION_ITERATIONS_TB.handle_input(event);

    DAMPING_DIST_TB.handle_input(event);
    DAMPING_COEFF_TB.handle_input(event);

    COLLISION_CELL_SIZE_TB.handle_input(event);
}

void update_button_statuses(sf::RenderWindow& window, sf::Event& event)
{
    PARTICLE_NUM_TB.get_button_status(window, event);

    PARTICLE_RADIUS_TB.get_button_status(window, event);
    PARTICLE_MASS_TB.get_button_status(window, event);

    PLACEMENT_TYPE_CIRCULAR_BTN.get_button_status(window, event);
    PLACEMENT_TYPE_FULLSCREEN_BTN.get_button_status(window, event);

    SPEED_TYPE_ANGULAR_BTN.get_button_status(window, event);
    SPEED_TYPE_RANDOM_BTN.get_button_status(window, event);
    SPEED_TYPE_ZERO_BTN.get_button_status(window, event);
    SPEED_TYPE_CENTRAL_BTN.get_button_status(window, event);

    HAS_BORDERS_BTN.get_button_status(window, event);

    HAS_TRAIL_BTN.get_button_status(window, event);

    HAS_GRAVITY_BTN.get_button_status(window, event);

    HAS_DAMPING_BTN.get_button_status(window, event);
    DAMPING_DIST_TB.get_button_status(window, event);
    DAMPING_COEFF_TB.get_button_status(window, event);

    HAS_OVERLAPCHECK_BTN.get_button_status(window, event);
    HAS_BOUNCEOFF_BTN.get_button_status(window, event);
    COLLISION_THRESHOLD_TB.get_button_status(window, event);
    COLLISION_ITERATIONS_TB.get_button_status(window, event);

    VISUALIZE_GRID_BTN.get_button_status(window, event);
    VISUALIZE_PARTICLE_CELL_BTN.get_button_status(window, event);
    VISUALIZE_CELL_MASS_BTN.get_button_status(window, event);
    VISUALIZE_COM_BTN.get_button_status(window, event);
    COLLISION_CELL_SIZE_TB.get_button_status(window, event);

    RELOAD_BTN.get_button_status(window, event);

    EXIT_BTN.get_button_status(window, event);
}

void handle_button_clicks(sf::RenderWindow& window, sf::Event& event)
{
    if (PARTICLE_NUM_TB.is_pressed)
    {
        PARTICLE_NUM_TB.set_toggle(true);
    }
    else if (PARTICLE_RADIUS_TB.is_pressed)
    {
        PARTICLE_RADIUS_TB.set_toggle(true);
    }
    else if (PARTICLE_MASS_TB.is_pressed)
    {
        PARTICLE_MASS_TB.set_toggle(true);
    }

    else if (PLACEMENT_TYPE_CIRCULAR_BTN.is_pressed)
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

    else if (SPEED_TYPE_ANGULAR_BTN.is_pressed)
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

    else if (HAS_BORDERS_BTN.is_pressed)
    {
        if (current_settings.HAS_BORDERS)
        {
            current_settings.HAS_BORDERS = false;
            settings.HAS_BORDERS = false;
        }
        else
        {
            current_settings.HAS_BORDERS = true;
            settings.HAS_BORDERS = true;
        }
    }

    else if (HAS_TRAIL_BTN.is_pressed)
    {
        if (current_settings.HAS_TRAIL)
        {
            current_settings.HAS_TRAIL = false;
            settings.HAS_TRAIL = false;
        }
        else
        {
            current_settings.HAS_TRAIL = true;
            settings.HAS_TRAIL = true;
        }
    }

    else if (HAS_GRAVITY_BTN.is_pressed)
    {
        if (current_settings.HAS_GRAVITY)
        {
            current_settings.HAS_GRAVITY = false;
            settings.HAS_GRAVITY = false;
        }
        else
        {
            current_settings.HAS_GRAVITY = true;
            settings.HAS_GRAVITY = true;
        }
    }

    else if (HAS_DAMPING_BTN.is_pressed)
    {
        if (current_settings.HAS_DAMPING)
        {
            current_settings.HAS_DAMPING = false;
            settings.HAS_DAMPING = false;

            DAMPING_DIST_TB.is_active = false;
            DAMPING_DIST_TB.get_button_status(window, event);
            DAMPING_COEFF_TB.is_active = false;
            DAMPING_COEFF_TB.get_button_status(window, event);
        }
        else
        {
            current_settings.HAS_DAMPING = true;
            settings.HAS_DAMPING = true;

            DAMPING_DIST_TB.is_active = true;
            DAMPING_DIST_TB.get_button_status(window, event);
            DAMPING_COEFF_TB.is_active = true;
            DAMPING_COEFF_TB.get_button_status(window, event);
        }
    }
    else if (DAMPING_DIST_TB.is_pressed)
    {
        DAMPING_DIST_TB.set_toggle(true);
    }
    else if (DAMPING_COEFF_TB.is_pressed)
    {
        DAMPING_COEFF_TB.set_toggle(true);
    }

    else if (HAS_OVERLAPCHECK_BTN.is_pressed)
    {
        if (current_settings.HAS_OVERLAPCHECK)
        {
            current_settings.HAS_OVERLAPCHECK = false;
            settings.HAS_OVERLAPCHECK = false;
        }
        else
        {
            current_settings.HAS_OVERLAPCHECK = true;
            settings.HAS_OVERLAPCHECK = true;
        }
    }
    else if (HAS_BOUNCEOFF_BTN.is_pressed)
    {
        if (current_settings.HAS_BOUNCEOFF)
        {
            current_settings.HAS_BOUNCEOFF = false;
            settings.HAS_BOUNCEOFF = false;
        }
        else
        {
            current_settings.HAS_BOUNCEOFF = true;
            settings.HAS_BOUNCEOFF = true;
        }
    }
    else if (COLLISION_THRESHOLD_TB.is_pressed)
    {
        COLLISION_THRESHOLD_TB.set_toggle(true);
    }
    else if (COLLISION_ITERATIONS_TB.is_pressed)
    {
        COLLISION_ITERATIONS_TB.set_toggle(true);
    }

    else if (VISUALIZE_GRID_BTN.is_pressed)
    {
        if (settings.VISUALIZE_SPATIAL_GRID)
        {
            settings.VISUALIZE_SPATIAL_GRID = false;
            current_settings.VISUALIZE_SPATIAL_GRID = false;

            VISUALIZE_CELL_MASS_BTN.is_active = false;
            VISUALIZE_CELL_MASS_BTN.get_button_status(window, event);
            VISUALIZE_COM_BTN.is_active = false;
            VISUALIZE_COM_BTN.get_button_status(window, event);
        }
        else
        {
            settings.VISUALIZE_SPATIAL_GRID = true;
            current_settings.VISUALIZE_SPATIAL_GRID = true;

            VISUALIZE_CELL_MASS_BTN.is_active = true;
            VISUALIZE_CELL_MASS_BTN.get_button_status(window, event);
            VISUALIZE_COM_BTN.is_active = true;
            VISUALIZE_COM_BTN.get_button_status(window, event);
        }
    }
    else if (VISUALIZE_PARTICLE_CELL_BTN.is_pressed)
    {
        if (settings.VISUALIZE_PARTICLE_CELL)
        {
            settings.VISUALIZE_PARTICLE_CELL = false;
            current_settings.VISUALIZE_PARTICLE_CELL = false;
        }
        else
        {
            settings.VISUALIZE_PARTICLE_CELL = true;
            current_settings.VISUALIZE_PARTICLE_CELL = true;
        }
    }
    else if (VISUALIZE_CELL_MASS_BTN.is_pressed)
    {
        if (settings.VISUALIZE_CELL_MASS)
        {
            settings.VISUALIZE_CELL_MASS = false;
            current_settings.VISUALIZE_CELL_MASS = false;
        }
        else
        {
            settings.VISUALIZE_CELL_MASS = true;
            current_settings.VISUALIZE_CELL_MASS = true;
        }
    }
    else if (VISUALIZE_COM_BTN.is_pressed)
    {
        if (settings.VISUALIZE_COM)
        {
            settings.VISUALIZE_COM = false;
            current_settings.VISUALIZE_COM = false;
        }
        else
        {
            settings.VISUALIZE_COM = true;
            current_settings.VISUALIZE_COM = true;
        }
    }
    else if (COLLISION_CELL_SIZE_TB.is_pressed)
        COLLISION_CELL_SIZE_TB.set_toggle(true);

    else if (RELOAD_BTN.is_pressed)
        reload_sim();

    else if (EXIT_BTN.is_pressed)
        window.close();
}

#endif