#ifndef MENU_UTILS_H
#define MENU_UTILS_H

#include "../globals/settings.h"
#include "../globals/globals.h"
#include "../utils/utils.h"
#include "../utils/key_conversion.h"

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

void recalc_sizes(int width, int height)
{
    WIDTH = width;
    HEIGHT = height;
    MENU_WIDTH = WIDTH / 6;
    CANVAS_WIDTH = width;
    if (CANVAS_WIDTH > HEIGHT)
        settings.R = 2 * HEIGHT / 5;
    else
        settings.R = 2 * CANVAS_WIDTH / 5;

    BTN_HEIGHT = HEIGHT / 52;
    TITLE_FONT_SIZE = 5 * BTN_HEIGHT / 6;
    FONT_SIZE = 5 * BTN_HEIGHT / 8;
    MARGIN_TOP = 2 * BTN_HEIGHT / 3;
    MARGIN_LEFT = BTN_HEIGHT / 2;
    MARGIN_BOTTOM = BTN_HEIGHT;
    MARGIN_RIGHT = BTN_HEIGHT / 2;
    MARGIN_BETWEEN = (MARGIN_LEFT / 2 < 10 ? 10 : MARGIN_LEFT / 2);
    MARGIN_BLOCK = 3 * BTN_HEIGHT / 4;
}

void init_ui()
{
    // BASIC STUFF

    FONT.loadFromFile("resources/fonts/Poppins-Bold.ttf");

    // FPS counter
    FPS_TXT.setFillColor(sf::Color::White);
    FPS_TXT.setPosition((SHOW_MENU ? MENU_WIDTH : 0) + MARGIN_LEFT, MARGIN_TOP);
    FPS_TXT.setFont(FONT);
    FPS_TXT.setCharacterSize(TITLE_FONT_SIZE);

    // Performance
    int stat_counter = 1;

    GRAV_COUNT_TXT.setFillColor(sf::Color::White);
    GRAV_COUNT_TXT.setPosition((SHOW_MENU ? MENU_WIDTH : 0) + MARGIN_LEFT, MARGIN_TOP + TITLE_FONT_SIZE + MARGIN_BETWEEN);
    GRAV_COUNT_TXT.setFont(FONT);
    GRAV_COUNT_TXT.setCharacterSize(FONT_SIZE);
    stat_counter++;

    QUADTREE_DEPTH_TXT.setFillColor(sf::Color::White);
    QUADTREE_DEPTH_TXT.setPosition((SHOW_MENU ? MENU_WIDTH : 0) + MARGIN_LEFT, MARGIN_TOP + TITLE_FONT_SIZE + (stat_counter - 1) * FONT_SIZE + stat_counter * MARGIN_BETWEEN);
    QUADTREE_DEPTH_TXT.setFont(FONT);
    QUADTREE_DEPTH_TXT.setCharacterSize(FONT_SIZE);
    stat_counter++;

    QUADTREE_NODES_TXT.setFillColor(sf::Color::White);
    QUADTREE_NODES_TXT.setPosition((SHOW_MENU ? MENU_WIDTH : 0) + MARGIN_LEFT, MARGIN_TOP + TITLE_FONT_SIZE + (stat_counter - 1) * FONT_SIZE + stat_counter * MARGIN_BETWEEN);
    QUADTREE_NODES_TXT.setFont(FONT);
    QUADTREE_NODES_TXT.setCharacterSize(FONT_SIZE);
    stat_counter++;

    QUADTREE_LEAVES_TXT.setFillColor(sf::Color::White);
    QUADTREE_LEAVES_TXT.setPosition((SHOW_MENU ? MENU_WIDTH : 0) + MARGIN_LEFT, MARGIN_TOP + TITLE_FONT_SIZE + (stat_counter - 1) * FONT_SIZE + stat_counter * MARGIN_BETWEEN);
    QUADTREE_LEAVES_TXT.setFont(FONT);
    QUADTREE_LEAVES_TXT.setCharacterSize(FONT_SIZE);
    stat_counter++;

    COLL_COUNT_TXT.setFillColor(sf::Color::White);
    COLL_COUNT_TXT.setPosition((SHOW_MENU ? MENU_WIDTH : 0) + MARGIN_LEFT, MARGIN_TOP + TITLE_FONT_SIZE + (stat_counter - 1) * FONT_SIZE + stat_counter * MARGIN_BETWEEN);
    COLL_COUNT_TXT.setFont(FONT);
    COLL_COUNT_TXT.setCharacterSize(FONT_SIZE);
    stat_counter++;

    // Help text
    HELP_TXT.setString(key_to_string(RELOAD_KEY) + ": RELOAD\t"
        + key_to_string(SINGULARITY_KEY) + ": PLACE BLACK HOLE\t"
        + key_to_string(SHOW_MENU_KEY) + ": SHOW/HIDE MENU\t"
        + key_to_string(SHOW_HELP_KEY) + ": SHOW/HIDE HELP");
    HELP_TXT.setFillColor(sf::Color::White);
    HELP_TXT.setFont(FONT);
    HELP_TXT.setCharacterSize(TITLE_FONT_SIZE);
    sf::FloatRect help_txt_rect = HELP_TXT.getLocalBounds();
    HELP_TXT.setOrigin(help_txt_rect.width / 2.0f, help_txt_rect.height / 2.0f);
    HELP_TXT.setPosition(WIDTH / 2, HEIGHT - FONT_SIZE - MARGIN_BOTTOM);

    HELP2_TXT.setString(key_to_string(SHOW_PERFORMANCE_KEY) + ": SHOW/HIDE PERFORMANCE\t"
        + key_to_string(SHOW_ALL_KEY) + ": SHOW/HIDE EVERYTHING\t"
        + key_to_string(EXIT_KEY) + ": EXIT");
    HELP2_TXT.setFillColor(sf::Color::White);
    HELP2_TXT.setFont(FONT);
    HELP2_TXT.setCharacterSize(TITLE_FONT_SIZE);
    help_txt_rect = HELP2_TXT.getLocalBounds();
    HELP2_TXT.setOrigin(help_txt_rect.width / 2.0f, help_txt_rect.height / 2.0f);
    HELP2_TXT.setPosition(WIDTH / 2, HEIGHT - FONT_SIZE);

    // LEFT MENU
    int button_counter = 0;
    int title_counter = 0;
    int label_counter = 0;
    int block_counter = 0;

    // Simulation title
    SIMULATION_TITLE.setString("SIMULATION");
    SIMULATION_TITLE.setFillColor(sf::Color::White);
    SIMULATION_TITLE.setPosition(MARGIN_LEFT, MARGIN_TOP + button_counter * (BTN_HEIGHT + MARGIN_BETWEEN) + title_counter * (TITLE_FONT_SIZE + MARGIN_BETWEEN) + label_counter * (FONT_SIZE + MARGIN_BETWEEN) + block_counter * MARGIN_BLOCK);
    SIMULATION_TITLE.setFont(FONT);
    SIMULATION_TITLE.setCharacterSize(2 * TITLE_FONT_SIZE);
    title_counter++;
    block_counter++;

    // Particle properties settings
    PARTICLE_PROPS_TXT.setString("PARTICLE PROPERTIES");
    PARTICLE_PROPS_TXT.setFillColor(sf::Color::White);
    PARTICLE_PROPS_TXT.setPosition(MARGIN_LEFT, MARGIN_TOP + button_counter * (BTN_HEIGHT + MARGIN_BETWEEN) + title_counter * (TITLE_FONT_SIZE + MARGIN_BETWEEN) + label_counter * (FONT_SIZE + MARGIN_BETWEEN) + block_counter * MARGIN_BLOCK);
    PARTICLE_PROPS_TXT.setFont(FONT);
    PARTICLE_PROPS_TXT.setCharacterSize(TITLE_FONT_SIZE);
    title_counter++;

    PARTICLE_NUM_TXT.setString("NUMBER OF PARTICLES");
    PARTICLE_NUM_TXT.setFillColor(sf::Color::White);
    PARTICLE_NUM_TXT.setPosition(MARGIN_LEFT, MARGIN_TOP + button_counter * (BTN_HEIGHT + MARGIN_BETWEEN) + title_counter * (TITLE_FONT_SIZE + MARGIN_BETWEEN) + label_counter * (FONT_SIZE + MARGIN_BETWEEN) + block_counter * MARGIN_BLOCK);
    PARTICLE_NUM_TXT.setFont(FONT);
    PARTICLE_NUM_TXT.setCharacterSize(FONT_SIZE);
    label_counter++;

    PARTICLE_NUM_TB = TextBox(FONT, sf::Vector2f(MENU_WIDTH - MARGIN_LEFT - MARGIN_RIGHT, BTN_HEIGHT), sf::Vector2f(MARGIN_LEFT, MARGIN_TOP + button_counter * (BTN_HEIGHT + MARGIN_BETWEEN) + title_counter * (TITLE_FONT_SIZE + MARGIN_BETWEEN) + label_counter * (FONT_SIZE + MARGIN_BETWEEN) + block_counter * MARGIN_BLOCK), settings.N, "int");
    PARTICLE_NUM_TB.set_button_label(FONT_SIZE, std::to_string(settings.N));
    button_counter++;

    PARTICLE_RADIUS_TXT.setString("RADIUS");
    PARTICLE_RADIUS_TXT.setFillColor(sf::Color::White);
    PARTICLE_RADIUS_TXT.setPosition(MARGIN_LEFT, MARGIN_TOP + button_counter * (BTN_HEIGHT + MARGIN_BETWEEN) + title_counter * (TITLE_FONT_SIZE + MARGIN_BETWEEN) + label_counter * (FONT_SIZE + MARGIN_BETWEEN) + block_counter * MARGIN_BLOCK);
    PARTICLE_RADIUS_TXT.setFont(FONT);
    PARTICLE_RADIUS_TXT.setCharacterSize(FONT_SIZE);

    PARTICLE_MASS_TXT.setString("MASS");
    PARTICLE_MASS_TXT.setFillColor(sf::Color::White);
    PARTICLE_MASS_TXT.setPosition(MARGIN_LEFT + (MENU_WIDTH - MARGIN_LEFT - MARGIN_RIGHT) / 2 + MARGIN_BETWEEN, MARGIN_TOP + button_counter * (BTN_HEIGHT + MARGIN_BETWEEN) + title_counter * (TITLE_FONT_SIZE + MARGIN_BETWEEN) + label_counter * (FONT_SIZE + MARGIN_BETWEEN) + block_counter * MARGIN_BLOCK);
    PARTICLE_MASS_TXT.setFont(FONT);
    PARTICLE_MASS_TXT.setCharacterSize(FONT_SIZE);
    label_counter++;

    PARTICLE_RADIUS_TB = TextBox(FONT, sf::Vector2f((MENU_WIDTH - MARGIN_LEFT - MARGIN_RIGHT) / 2, BTN_HEIGHT), sf::Vector2f(MARGIN_LEFT, MARGIN_TOP + button_counter * (BTN_HEIGHT + MARGIN_BETWEEN) + title_counter * (TITLE_FONT_SIZE + MARGIN_BETWEEN) + label_counter * (FONT_SIZE + MARGIN_BETWEEN) + block_counter * MARGIN_BLOCK), settings.RADIUS, "int");
    PARTICLE_RADIUS_TB.set_button_label(FONT_SIZE, std::to_string(settings.RADIUS));

    PARTICLE_MASS_TB = TextBox(FONT, sf::Vector2f((MENU_WIDTH - MARGIN_LEFT - MARGIN_RIGHT) / 2 - MARGIN_BETWEEN, BTN_HEIGHT), sf::Vector2f(MARGIN_LEFT + (MENU_WIDTH - MARGIN_LEFT - MARGIN_RIGHT) / 2 + MARGIN_BETWEEN, MARGIN_TOP + button_counter * (BTN_HEIGHT + MARGIN_BETWEEN) + title_counter * (TITLE_FONT_SIZE + MARGIN_BETWEEN) + label_counter * (FONT_SIZE + MARGIN_BETWEEN) + block_counter * MARGIN_BLOCK), settings.MASS, "double");
    PARTICLE_MASS_TB.set_button_label(FONT_SIZE, std::to_string(settings.MASS));
    button_counter++;

    SINGULARITY_MASS_TXT.setString("BLACK HOLE MASS");
    SINGULARITY_MASS_TXT.setFillColor(sf::Color::White);
    SINGULARITY_MASS_TXT.setPosition(MARGIN_LEFT, MARGIN_TOP + button_counter * (BTN_HEIGHT + MARGIN_BETWEEN) + title_counter * (TITLE_FONT_SIZE + MARGIN_BETWEEN) + label_counter * (FONT_SIZE + MARGIN_BETWEEN) + block_counter * MARGIN_BLOCK);
    SINGULARITY_MASS_TXT.setFont(FONT);
    SINGULARITY_MASS_TXT.setCharacterSize(FONT_SIZE);
    label_counter++;

    SINGULARITY_MASS_TB = TextBox(FONT, sf::Vector2f(MENU_WIDTH - MARGIN_LEFT - MARGIN_RIGHT, BTN_HEIGHT), sf::Vector2f(MARGIN_LEFT, MARGIN_TOP + button_counter * (BTN_HEIGHT + MARGIN_BETWEEN) + title_counter * (TITLE_FONT_SIZE + MARGIN_BETWEEN) + label_counter * (FONT_SIZE + MARGIN_BETWEEN) + block_counter * MARGIN_BLOCK), settings.SINGULARITY_MASS, "double");
    SINGULARITY_MASS_TB.set_button_label(FONT_SIZE, std::to_string(settings.SINGULARITY_MASS));
    button_counter++;
    block_counter++;

    // Placement type settings
    PLACEMENT_TYPE_TXT.setString("PLACEMENT TYPE");
    PLACEMENT_TYPE_TXT.setFillColor(sf::Color::White);
    PLACEMENT_TYPE_TXT.setPosition(MARGIN_LEFT, MARGIN_TOP + button_counter * (BTN_HEIGHT + MARGIN_BETWEEN) + title_counter * (TITLE_FONT_SIZE + MARGIN_BETWEEN) + label_counter * (FONT_SIZE + MARGIN_BETWEEN) + block_counter * MARGIN_BLOCK);
    PLACEMENT_TYPE_TXT.setFont(FONT);
    PLACEMENT_TYPE_TXT.setCharacterSize(TITLE_FONT_SIZE);
    title_counter++;

    PLACEMENT_TYPE_CIRCULAR_BTN = ToggleButton(FONT, sf::Vector2f((MENU_WIDTH - MARGIN_LEFT - MARGIN_RIGHT) / 2, BTN_HEIGHT), sf::Vector2f(MARGIN_LEFT, MARGIN_TOP + button_counter * (BTN_HEIGHT + MARGIN_BETWEEN) + title_counter * (TITLE_FONT_SIZE + MARGIN_BETWEEN) + label_counter * (FONT_SIZE + MARGIN_BETWEEN) + block_counter * MARGIN_BLOCK), settings.PLACEMENT_TYPE == PlacementType::Circular);
    PLACEMENT_TYPE_CIRCULAR_BTN.set_button_label(FONT_SIZE, "CIRCULAR");

    PLACEMENT_TYPE_FULLSCREEN_BTN = ToggleButton(FONT, sf::Vector2f((MENU_WIDTH - MARGIN_LEFT - MARGIN_RIGHT) / 2 - MARGIN_BETWEEN, BTN_HEIGHT), sf::Vector2f(MARGIN_LEFT + (MENU_WIDTH - MARGIN_LEFT - MARGIN_RIGHT) / 2 + MARGIN_BETWEEN, MARGIN_TOP + button_counter * (BTN_HEIGHT + MARGIN_BETWEEN) + title_counter * (TITLE_FONT_SIZE + MARGIN_BETWEEN) + label_counter * (FONT_SIZE + MARGIN_BETWEEN) + block_counter * MARGIN_BLOCK), settings.PLACEMENT_TYPE == PlacementType::Fullscreen);
    PLACEMENT_TYPE_FULLSCREEN_BTN.set_button_label(FONT_SIZE, "FULLSCREEN");
    button_counter++;

    PLACEMENT_RADIUS_TXT.setString("RADIUS");
    PLACEMENT_RADIUS_TXT.setFillColor(sf::Color::White);
    PLACEMENT_RADIUS_TXT.setPosition(MARGIN_LEFT, MARGIN_TOP + button_counter * (BTN_HEIGHT + MARGIN_BETWEEN) + title_counter * (TITLE_FONT_SIZE + MARGIN_BETWEEN) + label_counter * (FONT_SIZE + MARGIN_BETWEEN) + block_counter * MARGIN_BLOCK);
    PLACEMENT_RADIUS_TXT.setFont(FONT);
    PLACEMENT_RADIUS_TXT.setCharacterSize(FONT_SIZE);
    label_counter++;

    PLACEMENT_RADIUS_TB = TextBox(FONT, sf::Vector2f(MENU_WIDTH - MARGIN_LEFT - MARGIN_RIGHT, BTN_HEIGHT), sf::Vector2f(MARGIN_LEFT, MARGIN_TOP + button_counter * (BTN_HEIGHT + MARGIN_BETWEEN) + title_counter * (TITLE_FONT_SIZE + MARGIN_BETWEEN) + label_counter * (FONT_SIZE + MARGIN_BETWEEN) + block_counter * MARGIN_BLOCK), settings.R, "int");
    PLACEMENT_RADIUS_TB.set_button_label(FONT_SIZE, std::to_string(settings.R));
    PLACEMENT_RADIUS_TB.is_active = settings.PLACEMENT_TYPE == PlacementType::Circular;
    button_counter++;
    block_counter++;

    // Speed type settings
    SPEED_TYPE_TXT.setString("SPEED TYPE");
    SPEED_TYPE_TXT.setFillColor(sf::Color::White);
    SPEED_TYPE_TXT.setPosition(MARGIN_LEFT, MARGIN_TOP + button_counter * (BTN_HEIGHT + MARGIN_BETWEEN) + title_counter * (TITLE_FONT_SIZE + MARGIN_BETWEEN) + label_counter * (FONT_SIZE + MARGIN_BETWEEN) + block_counter * MARGIN_BLOCK);
    SPEED_TYPE_TXT.setFont(FONT);
    SPEED_TYPE_TXT.setCharacterSize(TITLE_FONT_SIZE);
    title_counter++;

    SPEED_TYPE_ANGULAR_BTN = ToggleButton(FONT, sf::Vector2f((MENU_WIDTH - MARGIN_LEFT - MARGIN_RIGHT) / 2, BTN_HEIGHT), sf::Vector2f(MARGIN_LEFT, MARGIN_TOP + button_counter * (BTN_HEIGHT + MARGIN_BETWEEN) + title_counter * (TITLE_FONT_SIZE + MARGIN_BETWEEN) + label_counter * (FONT_SIZE + MARGIN_BETWEEN) + block_counter * MARGIN_BLOCK), settings.SPEED_TYPE == SpeedType::Angular);
    SPEED_TYPE_ANGULAR_BTN.set_button_label(FONT_SIZE, "ANGULAR");

    SPEED_TYPE_RANDOM_BTN = ToggleButton(FONT, sf::Vector2f((MENU_WIDTH - MARGIN_LEFT - MARGIN_RIGHT) / 2 - MARGIN_BETWEEN, BTN_HEIGHT), sf::Vector2f(MARGIN_LEFT + (MENU_WIDTH - MARGIN_LEFT - MARGIN_RIGHT) / 2 + MARGIN_BETWEEN, MARGIN_TOP + button_counter * (BTN_HEIGHT + MARGIN_BETWEEN) + title_counter * (TITLE_FONT_SIZE + MARGIN_BETWEEN) + label_counter * (FONT_SIZE + MARGIN_BETWEEN) + block_counter * MARGIN_BLOCK), settings.SPEED_TYPE == SpeedType::Random);
    SPEED_TYPE_RANDOM_BTN.set_button_label(FONT_SIZE, "RANDOM");
    button_counter++;

    SPEED_TYPE_ZERO_BTN = ToggleButton(FONT, sf::Vector2f((MENU_WIDTH - MARGIN_LEFT - MARGIN_RIGHT) / 2, BTN_HEIGHT), sf::Vector2f(MARGIN_LEFT, MARGIN_TOP + button_counter * (BTN_HEIGHT + MARGIN_BETWEEN) + title_counter * (TITLE_FONT_SIZE + MARGIN_BETWEEN) + label_counter * (FONT_SIZE + MARGIN_BETWEEN) + block_counter * MARGIN_BLOCK), settings.SPEED_TYPE == SpeedType::Zero);
    SPEED_TYPE_ZERO_BTN.set_button_label(FONT_SIZE, "ZERO");

    SPEED_TYPE_GALAXY_BTN = ToggleButton(FONT, sf::Vector2f((MENU_WIDTH - MARGIN_LEFT - MARGIN_RIGHT) / 2 - MARGIN_BETWEEN, BTN_HEIGHT), sf::Vector2f(MARGIN_LEFT + (MENU_WIDTH - MARGIN_LEFT - MARGIN_RIGHT) / 2 + MARGIN_BETWEEN, MARGIN_TOP + button_counter * (BTN_HEIGHT + MARGIN_BETWEEN) + title_counter * (TITLE_FONT_SIZE + MARGIN_BETWEEN) + label_counter * (FONT_SIZE + MARGIN_BETWEEN) + block_counter * MARGIN_BLOCK), settings.SPEED_TYPE == SpeedType::Galaxy);
    SPEED_TYPE_GALAXY_BTN.set_button_label(FONT_SIZE, "GALAXY");
    button_counter++;
    block_counter++;

    // Border settings
    BORDER_TXT.setString("BORDER SETTINGS");
    BORDER_TXT.setFillColor(sf::Color::White);
    BORDER_TXT.setPosition(MARGIN_LEFT, MARGIN_TOP + button_counter * (BTN_HEIGHT + MARGIN_BETWEEN) + title_counter * (TITLE_FONT_SIZE + MARGIN_BETWEEN) + label_counter * (FONT_SIZE + MARGIN_BETWEEN) + block_counter * MARGIN_BLOCK);
    BORDER_TXT.setFont(FONT);
    BORDER_TXT.setCharacterSize(TITLE_FONT_SIZE);
    title_counter++;

    HAS_BORDERS_BTN = ToggleButton(FONT, sf::Vector2f(MENU_WIDTH - MARGIN_LEFT - MARGIN_RIGHT, BTN_HEIGHT), sf::Vector2f(MARGIN_LEFT, MARGIN_TOP + button_counter * (BTN_HEIGHT + MARGIN_BETWEEN) + title_counter * (TITLE_FONT_SIZE + MARGIN_BETWEEN) + label_counter * (FONT_SIZE + MARGIN_BETWEEN) + block_counter * MARGIN_BLOCK), settings.HAS_BORDERS);
    HAS_BORDERS_BTN.set_button_label(FONT_SIZE, "BORDERS ON/OFF");
    button_counter++;
    block_counter++;

    // Gravity settings
    GRAVITY_TXT.setString("GRAVITY SETTINGS");
    GRAVITY_TXT.setFillColor(sf::Color::White);
    GRAVITY_TXT.setPosition(MARGIN_LEFT, MARGIN_TOP + button_counter * (BTN_HEIGHT + MARGIN_BETWEEN) + title_counter * (TITLE_FONT_SIZE + MARGIN_BETWEEN) + label_counter * (FONT_SIZE + MARGIN_BETWEEN) + block_counter * MARGIN_BLOCK);
    GRAVITY_TXT.setFont(FONT);
    GRAVITY_TXT.setCharacterSize(TITLE_FONT_SIZE);
    title_counter++;

    HAS_GRAVITY_BTN = ToggleButton(FONT, sf::Vector2f(MENU_WIDTH - MARGIN_LEFT - MARGIN_RIGHT, BTN_HEIGHT), sf::Vector2f(MARGIN_LEFT, MARGIN_TOP + button_counter * (BTN_HEIGHT + MARGIN_BETWEEN) + title_counter * (TITLE_FONT_SIZE + MARGIN_BETWEEN) + label_counter * (FONT_SIZE + MARGIN_BETWEEN) + block_counter * MARGIN_BLOCK), settings.HAS_GRAVITY);
    HAS_GRAVITY_BTN.set_button_label(FONT_SIZE, "GRAVITY ON/OFF");
    button_counter++;
    block_counter++;

    // Damping settings
    DAMPING_TXT.setString("DAMPING SETTINGS");
    DAMPING_TXT.setFillColor(sf::Color::White);
    DAMPING_TXT.setPosition(MARGIN_LEFT, MARGIN_TOP + button_counter * (BTN_HEIGHT + MARGIN_BETWEEN) + title_counter * (TITLE_FONT_SIZE + MARGIN_BETWEEN) + label_counter * (FONT_SIZE + MARGIN_BETWEEN) + block_counter * MARGIN_BLOCK);
    DAMPING_TXT.setFont(FONT);
    DAMPING_TXT.setCharacterSize(TITLE_FONT_SIZE);
    title_counter++;

    HAS_DAMPING_BTN = ToggleButton(FONT, sf::Vector2f(MENU_WIDTH - MARGIN_LEFT - MARGIN_RIGHT, BTN_HEIGHT), sf::Vector2f(MARGIN_LEFT, MARGIN_TOP + button_counter * (BTN_HEIGHT + MARGIN_BETWEEN) + title_counter * (TITLE_FONT_SIZE + MARGIN_BETWEEN) + label_counter * (FONT_SIZE + MARGIN_BETWEEN) + block_counter * MARGIN_BLOCK), settings.HAS_DAMPING);
    HAS_DAMPING_BTN.set_button_label(FONT_SIZE, "DAMPING ON/OFF");
    button_counter++;

    DAMPING_DIST_TXT.setString("DISTANCE");
    DAMPING_DIST_TXT.setFillColor(sf::Color::White);
    DAMPING_DIST_TXT.setPosition(MARGIN_LEFT, MARGIN_TOP + button_counter * (BTN_HEIGHT + MARGIN_BETWEEN) + title_counter * (TITLE_FONT_SIZE + MARGIN_BETWEEN) + label_counter * (FONT_SIZE + MARGIN_BETWEEN) + block_counter * MARGIN_BLOCK);
    DAMPING_DIST_TXT.setFont(FONT);
    DAMPING_DIST_TXT.setCharacterSize(FONT_SIZE);

    DAMPING_COEFF_TXT.setString("COEFFICIENT");
    DAMPING_COEFF_TXT.setFillColor(sf::Color::White);
    DAMPING_COEFF_TXT.setPosition(MARGIN_LEFT + (MENU_WIDTH - MARGIN_LEFT - MARGIN_RIGHT) / 2 + MARGIN_BETWEEN, MARGIN_TOP + button_counter * (BTN_HEIGHT + MARGIN_BETWEEN) + title_counter * (TITLE_FONT_SIZE + MARGIN_BETWEEN) + label_counter * (FONT_SIZE + MARGIN_BETWEEN) + block_counter * MARGIN_BLOCK);
    DAMPING_COEFF_TXT.setFont(FONT);
    DAMPING_COEFF_TXT.setCharacterSize(FONT_SIZE);
    label_counter++;

    DAMPING_DIST_TB = TextBox(FONT, sf::Vector2f((MENU_WIDTH - MARGIN_LEFT - MARGIN_RIGHT) / 2, BTN_HEIGHT), sf::Vector2f(MARGIN_LEFT, MARGIN_TOP + button_counter * (BTN_HEIGHT + MARGIN_BETWEEN) + title_counter * (TITLE_FONT_SIZE + MARGIN_BETWEEN) + label_counter * (FONT_SIZE + MARGIN_BETWEEN) + block_counter * MARGIN_BLOCK), settings.DAMPING_DIST, "double");
    DAMPING_DIST_TB.set_button_label(FONT_SIZE, std::to_string(settings.DAMPING_DIST));

    DAMPING_COEFF_TB = TextBox(FONT, sf::Vector2f((MENU_WIDTH - MARGIN_LEFT - MARGIN_RIGHT) / 2 - MARGIN_BETWEEN, BTN_HEIGHT), sf::Vector2f(MARGIN_LEFT + (MENU_WIDTH - MARGIN_LEFT - MARGIN_RIGHT) / 2 + MARGIN_BETWEEN, MARGIN_TOP + button_counter * (BTN_HEIGHT + MARGIN_BETWEEN) + title_counter * (TITLE_FONT_SIZE + MARGIN_BETWEEN) + label_counter * (FONT_SIZE + MARGIN_BETWEEN) + block_counter * MARGIN_BLOCK), settings.DAMPING_COEFF, "double");
    DAMPING_COEFF_TB.set_button_label(FONT_SIZE, std::to_string(settings.DAMPING_COEFF));
    button_counter++;
    block_counter++;

    if (!settings.HAS_DAMPING)
    {
        DAMPING_DIST_TB.is_active = false;
        DAMPING_COEFF_TB.is_active = false;
    }

    // Collision settings
    COLLISION_TXT.setString("COLLISION SETTINGS");
    COLLISION_TXT.setFillColor(sf::Color::White);
    COLLISION_TXT.setPosition(MARGIN_LEFT, MARGIN_TOP + button_counter * (BTN_HEIGHT + MARGIN_BETWEEN) + title_counter * (TITLE_FONT_SIZE + MARGIN_BETWEEN) + label_counter * (FONT_SIZE + MARGIN_BETWEEN) + block_counter * MARGIN_BLOCK);
    COLLISION_TXT.setFont(FONT);
    COLLISION_TXT.setCharacterSize(TITLE_FONT_SIZE);
    title_counter++;

    HAS_COLLISIONS_BTN = ToggleButton(FONT, sf::Vector2f(MENU_WIDTH - MARGIN_LEFT - MARGIN_RIGHT, BTN_HEIGHT), sf::Vector2f(MARGIN_LEFT, MARGIN_TOP + button_counter * (BTN_HEIGHT + MARGIN_BETWEEN) + title_counter * (TITLE_FONT_SIZE + MARGIN_BETWEEN) + label_counter * (FONT_SIZE + MARGIN_BETWEEN) + block_counter * MARGIN_BLOCK), settings.HAS_COLLISIONS);
    HAS_COLLISIONS_BTN.set_button_label(FONT_SIZE, "COLLISIONS ON/OFF");
    button_counter++;
    
    COLLISION_THRESHOLD_TXT.setString("THRESHOLD");
    COLLISION_THRESHOLD_TXT.setFillColor(sf::Color::White);
    COLLISION_THRESHOLD_TXT.setPosition(MARGIN_LEFT, MARGIN_TOP + button_counter * (BTN_HEIGHT + MARGIN_BETWEEN) + title_counter * (TITLE_FONT_SIZE + MARGIN_BETWEEN) + label_counter * (FONT_SIZE + MARGIN_BETWEEN) + block_counter * MARGIN_BLOCK);
    COLLISION_THRESHOLD_TXT.setFont(FONT);
    COLLISION_THRESHOLD_TXT.setCharacterSize(FONT_SIZE);

    COLLISION_ITERATIONS_TXT.setString("ITERATIONS");
    COLLISION_ITERATIONS_TXT.setFillColor(sf::Color::White);
    COLLISION_ITERATIONS_TXT.setPosition(MARGIN_LEFT + (MENU_WIDTH - MARGIN_LEFT - MARGIN_RIGHT) / 2 + MARGIN_BETWEEN, MARGIN_TOP + button_counter * (BTN_HEIGHT + MARGIN_BETWEEN) + title_counter * (TITLE_FONT_SIZE + MARGIN_BETWEEN) + label_counter * (FONT_SIZE + MARGIN_BETWEEN) + block_counter * MARGIN_BLOCK);
    COLLISION_ITERATIONS_TXT.setFont(FONT);
    COLLISION_ITERATIONS_TXT.setCharacterSize(FONT_SIZE);
    label_counter++;

    COLLISION_THRESHOLD_TB = TextBox(FONT, sf::Vector2f((MENU_WIDTH - MARGIN_LEFT - MARGIN_RIGHT) / 2, BTN_HEIGHT), sf::Vector2f(MARGIN_LEFT, MARGIN_TOP + button_counter * (BTN_HEIGHT + MARGIN_BETWEEN) + title_counter * (TITLE_FONT_SIZE + MARGIN_BETWEEN) + label_counter * (FONT_SIZE + MARGIN_BETWEEN) + block_counter * MARGIN_BLOCK), settings.COLLISION_THRESHOLD, "double");
    COLLISION_THRESHOLD_TB.set_button_label(FONT_SIZE, std::to_string(settings.COLLISION_THRESHOLD));

    COLLISION_ITERATIONS_TB = TextBox(FONT, sf::Vector2f((MENU_WIDTH - MARGIN_LEFT - MARGIN_RIGHT) / 2 - MARGIN_BETWEEN, BTN_HEIGHT), sf::Vector2f(MARGIN_LEFT + (MENU_WIDTH - MARGIN_LEFT - MARGIN_RIGHT) / 2 + MARGIN_BETWEEN, MARGIN_TOP + button_counter * (BTN_HEIGHT + MARGIN_BETWEEN) + title_counter * (TITLE_FONT_SIZE + MARGIN_BETWEEN) + label_counter * (FONT_SIZE + MARGIN_BETWEEN) + block_counter * MARGIN_BLOCK), settings.COLLISION_ITERATIONS, "int");
    COLLISION_ITERATIONS_TB.set_button_label(FONT_SIZE, std::to_string(settings.COLLISION_ITERATIONS));
    button_counter++;

    COLLISION_IMPULSE_COEFF_TXT.setString("IMPULSE COEFFICIENT");
    COLLISION_IMPULSE_COEFF_TXT.setFillColor(sf::Color::White);
    COLLISION_IMPULSE_COEFF_TXT.setPosition(MARGIN_LEFT, MARGIN_TOP + button_counter * (BTN_HEIGHT + MARGIN_BETWEEN) + title_counter * (TITLE_FONT_SIZE + MARGIN_BETWEEN) + label_counter * (FONT_SIZE + MARGIN_BETWEEN) + block_counter * MARGIN_BLOCK);
    COLLISION_IMPULSE_COEFF_TXT.setFont(FONT);
    COLLISION_IMPULSE_COEFF_TXT.setCharacterSize(FONT_SIZE);
    label_counter++;

    COLLISION_IMPULSE_COEFF_TB = TextBox(FONT, sf::Vector2f(MENU_WIDTH - MARGIN_LEFT - MARGIN_RIGHT, BTN_HEIGHT), sf::Vector2f(MARGIN_LEFT, MARGIN_TOP + button_counter * (BTN_HEIGHT + MARGIN_BETWEEN) + title_counter * (TITLE_FONT_SIZE + MARGIN_BETWEEN) + label_counter * (FONT_SIZE + MARGIN_BETWEEN) + block_counter * MARGIN_BLOCK), settings.COLLISION_IMPULSE_COEFF, "double");
    COLLISION_IMPULSE_COEFF_TB.set_button_label(FONT_SIZE, std::to_string(settings.COLLISION_IMPULSE_COEFF));
    button_counter++;
    block_counter++;

    if (!settings.HAS_COLLISIONS)
    {
        COLLISION_THRESHOLD_TB.is_active = false;
        COLLISION_ITERATIONS_TB.is_active = false;
        COLLISION_IMPULSE_COEFF_TB.is_active = false;
    }

    // Restart simulation
    RELOAD_REQUIRED_TXT.setString("RELOAD REQUIRED");
    RELOAD_REQUIRED_TXT.setFillColor(sf::Color::Red);
    RELOAD_REQUIRED_TXT.setPosition(MARGIN_LEFT, HEIGHT - MARGIN_BOTTOM - BTN_HEIGHT - MARGIN_BETWEEN - FONT_SIZE);
    RELOAD_REQUIRED_TXT.setFont(FONT);
    RELOAD_REQUIRED_TXT.setCharacterSize(FONT_SIZE);

    RELOAD_BTN = SimpleButton(FONT, sf::Vector2f(MENU_WIDTH - MARGIN_LEFT - MARGIN_RIGHT, BTN_HEIGHT), sf::Vector2f(MARGIN_LEFT, HEIGHT - BTN_HEIGHT - MARGIN_BOTTOM));
    RELOAD_BTN.set_button_label(FONT_SIZE, "RELOAD");
    button_counter++;

    // RIGHT MENU
    button_counter = 0;
    title_counter = 0;
    label_counter = 0;
    block_counter = 0;

    // Display title
    DISPLAY_TITLE.setString("DISPLAY");
    DISPLAY_TITLE.setFillColor(sf::Color::White);
    DISPLAY_TITLE.setPosition(WIDTH - MENU_WIDTH + MARGIN_LEFT, MARGIN_TOP + button_counter * (BTN_HEIGHT + MARGIN_BETWEEN) + title_counter * (TITLE_FONT_SIZE + MARGIN_BETWEEN) + label_counter * (FONT_SIZE + MARGIN_BETWEEN) + block_counter * MARGIN_BLOCK);
    DISPLAY_TITLE.setFont(FONT);
    DISPLAY_TITLE.setCharacterSize(2 * TITLE_FONT_SIZE);
    title_counter++;
    block_counter++;

    // Animation settings
    ANIMATION_SETTINGS_TXT.setString("ANIMATION SETTINGS");
    ANIMATION_SETTINGS_TXT.setFillColor(sf::Color::White);
    ANIMATION_SETTINGS_TXT.setPosition(WIDTH - MENU_WIDTH + MARGIN_LEFT, MARGIN_TOP + button_counter * (BTN_HEIGHT + MARGIN_BETWEEN) + title_counter * (TITLE_FONT_SIZE + MARGIN_BETWEEN) + label_counter * (FONT_SIZE + MARGIN_BETWEEN) + block_counter * MARGIN_BLOCK);
    ANIMATION_SETTINGS_TXT.setFont(FONT);
    ANIMATION_SETTINGS_TXT.setCharacterSize(TITLE_FONT_SIZE);
    title_counter++;
    
    TIMESTEP_TXT.setString("TIMESTEP");
    TIMESTEP_TXT.setFillColor(sf::Color::White);
    TIMESTEP_TXT.setPosition(WIDTH - MENU_WIDTH + MARGIN_LEFT, MARGIN_TOP + button_counter * (BTN_HEIGHT + MARGIN_BETWEEN) + title_counter * (TITLE_FONT_SIZE + MARGIN_BETWEEN) + label_counter * (FONT_SIZE + MARGIN_BETWEEN) + block_counter * MARGIN_BLOCK);
    TIMESTEP_TXT.setFont(FONT);
    TIMESTEP_TXT.setCharacterSize(FONT_SIZE);

    FPS_LIMIT_TXT.setString("FPS LIMIT");
    FPS_LIMIT_TXT.setFillColor(sf::Color::White);
    FPS_LIMIT_TXT.setPosition(WIDTH - MENU_WIDTH + MARGIN_LEFT + (MENU_WIDTH - MARGIN_LEFT - MARGIN_RIGHT) / 2 + MARGIN_BETWEEN, MARGIN_TOP + button_counter * (BTN_HEIGHT + MARGIN_BETWEEN) + title_counter * (TITLE_FONT_SIZE + MARGIN_BETWEEN) + label_counter * (FONT_SIZE + MARGIN_BETWEEN) + block_counter * MARGIN_BLOCK);
    FPS_LIMIT_TXT.setFont(FONT);
    FPS_LIMIT_TXT.setCharacterSize(FONT_SIZE);
    label_counter++;

    TIMESTEP_TB = TextBox(FONT, sf::Vector2f((MENU_WIDTH - MARGIN_LEFT - MARGIN_RIGHT) / 2, BTN_HEIGHT), sf::Vector2f(WIDTH - MENU_WIDTH + MARGIN_LEFT, MARGIN_TOP + button_counter * (BTN_HEIGHT + MARGIN_BETWEEN) + title_counter * (TITLE_FONT_SIZE + MARGIN_BETWEEN) + label_counter * (FONT_SIZE + MARGIN_BETWEEN) + block_counter * MARGIN_BLOCK), settings.TIMESTEP, "double");
    TIMESTEP_TB.set_button_label(FONT_SIZE, std::to_string(settings.TIMESTEP));

    FPS_LIMIT_TB = TextBox(FONT, sf::Vector2f((MENU_WIDTH - MARGIN_LEFT - MARGIN_RIGHT) / 2 - MARGIN_BETWEEN, BTN_HEIGHT), sf::Vector2f(WIDTH - MENU_WIDTH + MARGIN_LEFT + (MENU_WIDTH - MARGIN_LEFT - MARGIN_RIGHT) / 2 + MARGIN_BETWEEN, MARGIN_TOP + button_counter * (BTN_HEIGHT + MARGIN_BETWEEN) + title_counter * (TITLE_FONT_SIZE + MARGIN_BETWEEN) + label_counter * (FONT_SIZE + MARGIN_BETWEEN) + block_counter * MARGIN_BLOCK), settings.FPS_LIMIT, "int");
    FPS_LIMIT_TB.set_button_label(FONT_SIZE, std::to_string(settings.FPS_LIMIT));
    button_counter++;
    block_counter++;

    // Trail settings
    TRAIL_TXT.setString("TRAIL SETTINGS");
    TRAIL_TXT.setFillColor(sf::Color::White);
    TRAIL_TXT.setPosition(WIDTH - MENU_WIDTH + MARGIN_LEFT, MARGIN_TOP + button_counter * (BTN_HEIGHT + MARGIN_BETWEEN) + title_counter * (TITLE_FONT_SIZE + MARGIN_BETWEEN) + label_counter * (FONT_SIZE + MARGIN_BETWEEN) + block_counter * MARGIN_BLOCK);
    TRAIL_TXT.setFont(FONT);
    TRAIL_TXT.setCharacterSize(TITLE_FONT_SIZE);
    title_counter++;

    HAS_TRAIL_BTN = ToggleButton(FONT, sf::Vector2f(MENU_WIDTH - MARGIN_LEFT - MARGIN_RIGHT, BTN_HEIGHT), sf::Vector2f(WIDTH - MENU_WIDTH + MARGIN_LEFT, MARGIN_TOP + button_counter * (BTN_HEIGHT + MARGIN_BETWEEN) + title_counter * (TITLE_FONT_SIZE + MARGIN_BETWEEN) + label_counter * (FONT_SIZE + MARGIN_BETWEEN) + block_counter * MARGIN_BLOCK), settings.HAS_TRAIL);
    HAS_TRAIL_BTN.set_button_label(FONT_SIZE, "TRAILS ON/OFF");
    button_counter++;
    block_counter++;

    // Optimization title
    OPTIMIZATION_TITLE.setString("OPTIMIZATION");
    OPTIMIZATION_TITLE.setFillColor(sf::Color::White);
    OPTIMIZATION_TITLE.setPosition(WIDTH - MENU_WIDTH + MARGIN_LEFT, MARGIN_TOP + button_counter * (BTN_HEIGHT + MARGIN_BETWEEN) + title_counter * (TITLE_FONT_SIZE + MARGIN_BETWEEN) + label_counter * (FONT_SIZE + MARGIN_BETWEEN) + block_counter * MARGIN_BLOCK);
    OPTIMIZATION_TITLE.setFont(FONT);
    OPTIMIZATION_TITLE.setCharacterSize(2 * TITLE_FONT_SIZE);
    title_counter++;
    block_counter++;

    // Collision optimization settings
    COLLISION_OPTIMIZATION_TXT.setString("COLLISION OPTIMIZATION");
    COLLISION_OPTIMIZATION_TXT.setFillColor(sf::Color::White);
    COLLISION_OPTIMIZATION_TXT.setPosition(WIDTH - MENU_WIDTH + MARGIN_LEFT, MARGIN_TOP + button_counter * (BTN_HEIGHT + MARGIN_BETWEEN) + title_counter * (TITLE_FONT_SIZE + MARGIN_BETWEEN) + label_counter * (FONT_SIZE + MARGIN_BETWEEN) + block_counter * MARGIN_BLOCK);
    COLLISION_OPTIMIZATION_TXT.setFont(FONT);
    COLLISION_OPTIMIZATION_TXT.setCharacterSize(TITLE_FONT_SIZE);
    title_counter++;

    VISUALIZE_GRID_BTN = ToggleButton(FONT, sf::Vector2f(MENU_WIDTH - MARGIN_LEFT - MARGIN_RIGHT, BTN_HEIGHT), sf::Vector2f(WIDTH - MENU_WIDTH + MARGIN_LEFT, MARGIN_TOP + button_counter * (BTN_HEIGHT + MARGIN_BETWEEN) + title_counter * (TITLE_FONT_SIZE + MARGIN_BETWEEN) + label_counter * (FONT_SIZE + MARGIN_BETWEEN) + block_counter * MARGIN_BLOCK), settings.VISUALIZE_COLLISION_GRID);
    VISUALIZE_GRID_BTN.set_button_label(FONT_SIZE, "VISUALIZE GRID ON/OFF");
    button_counter++;

    VISUALIZE_PARTICLE_CELL_BTN = ToggleButton(FONT, sf::Vector2f(MENU_WIDTH - MARGIN_LEFT - MARGIN_RIGHT, BTN_HEIGHT), sf::Vector2f(WIDTH - MENU_WIDTH + MARGIN_LEFT, MARGIN_TOP + button_counter * (BTN_HEIGHT + MARGIN_BETWEEN) + title_counter * (TITLE_FONT_SIZE + MARGIN_BETWEEN) + label_counter * (FONT_SIZE + MARGIN_BETWEEN) + block_counter * MARGIN_BLOCK), settings.VISUALIZE_COLLISION_PARTICLE_CELL);
    VISUALIZE_PARTICLE_CELL_BTN.set_button_label(FONT_SIZE, "VISUALIZE PARTICLES' CELL ON/OFF");
    button_counter++;

    VISUALIZE_CELL_MASS_BTN = ToggleButton(FONT, sf::Vector2f(MENU_WIDTH - MARGIN_LEFT - MARGIN_RIGHT, BTN_HEIGHT), sf::Vector2f(WIDTH - MENU_WIDTH + MARGIN_LEFT, MARGIN_TOP + button_counter * (BTN_HEIGHT + MARGIN_BETWEEN) + title_counter * (TITLE_FONT_SIZE + MARGIN_BETWEEN) + label_counter * (FONT_SIZE + MARGIN_BETWEEN) + block_counter * MARGIN_BLOCK), settings.VISUALIZE_COLLISION_CELL_MASS);
    VISUALIZE_CELL_MASS_BTN.set_button_label(FONT_SIZE, "VISUALIZE CELLS' MASS ON/OFF");
    button_counter++;

    VISUALIZE_COM_BTN = ToggleButton(FONT, sf::Vector2f(MENU_WIDTH - MARGIN_LEFT - MARGIN_RIGHT, BTN_HEIGHT), sf::Vector2f(WIDTH - MENU_WIDTH + MARGIN_LEFT, MARGIN_TOP + button_counter * (BTN_HEIGHT + MARGIN_BETWEEN) + title_counter * (TITLE_FONT_SIZE + MARGIN_BETWEEN) + label_counter * (FONT_SIZE + MARGIN_BETWEEN) + block_counter * MARGIN_BLOCK), settings.VISUALIZE_COLLISION_COM);
    VISUALIZE_COM_BTN.set_button_label(FONT_SIZE, "VISUALIZE CELLS' CENTER OF MASS ON/OFF");
    button_counter++;

    COLLISION_CELL_SIZE_TXT.setString("CELL SIZE");
    COLLISION_CELL_SIZE_TXT.setFillColor(sf::Color::White);
    COLLISION_CELL_SIZE_TXT.setPosition(WIDTH - MENU_WIDTH + MARGIN_LEFT, MARGIN_TOP + button_counter * (BTN_HEIGHT + MARGIN_BETWEEN) + title_counter * (TITLE_FONT_SIZE + MARGIN_BETWEEN) + label_counter * (FONT_SIZE + MARGIN_BETWEEN) + block_counter * MARGIN_BLOCK);
    COLLISION_CELL_SIZE_TXT.setFont(FONT);
    COLLISION_CELL_SIZE_TXT.setCharacterSize(FONT_SIZE);
    label_counter++;

    COLLISION_CELL_SIZE_TB = TextBox(FONT, sf::Vector2f(MENU_WIDTH - MARGIN_LEFT - MARGIN_RIGHT, BTN_HEIGHT), sf::Vector2f(WIDTH - MENU_WIDTH + MARGIN_LEFT, MARGIN_TOP + button_counter * (BTN_HEIGHT + MARGIN_BETWEEN) + title_counter * (TITLE_FONT_SIZE + MARGIN_BETWEEN) + label_counter * (FONT_SIZE + MARGIN_BETWEEN) + block_counter * MARGIN_BLOCK), settings.COLLISION_CELL_SIZE, "int");
    COLLISION_CELL_SIZE_TB.set_button_label(FONT_SIZE, std::to_string(settings.COLLISION_CELL_SIZE));
    button_counter++;
    block_counter++;

    if (!settings.VISUALIZE_COLLISION_GRID)
    {
        VISUALIZE_PARTICLE_CELL_BTN.is_active = settings.VISUALIZE_COLLISION_GRID;
        VISUALIZE_CELL_MASS_BTN.is_active = settings.VISUALIZE_COLLISION_GRID;
        VISUALIZE_COM_BTN.is_active = settings.VISUALIZE_COLLISION_GRID;
    }

    // Gravity optimization settings
    GRAVITY_OPTIMIZATION_TXT.setString("GRAVITY OPTIMIZATION");
    GRAVITY_OPTIMIZATION_TXT.setFillColor(sf::Color::White);
    GRAVITY_OPTIMIZATION_TXT.setPosition(WIDTH - MENU_WIDTH + MARGIN_LEFT, MARGIN_TOP + button_counter * (BTN_HEIGHT + MARGIN_BETWEEN) + title_counter * (TITLE_FONT_SIZE + MARGIN_BETWEEN) + label_counter * (FONT_SIZE + MARGIN_BETWEEN) + block_counter * MARGIN_BLOCK);
    GRAVITY_OPTIMIZATION_TXT.setFont(FONT);
    GRAVITY_OPTIMIZATION_TXT.setCharacterSize(TITLE_FONT_SIZE);
    title_counter++;

    VISUALIZE_GRAVITY_TREE_BTN = ToggleButton(FONT, sf::Vector2f(MENU_WIDTH - MARGIN_LEFT - MARGIN_RIGHT, BTN_HEIGHT), sf::Vector2f(WIDTH - MENU_WIDTH + MARGIN_LEFT, MARGIN_TOP + button_counter * (BTN_HEIGHT + MARGIN_BETWEEN) + title_counter * (TITLE_FONT_SIZE + MARGIN_BETWEEN) + label_counter * (FONT_SIZE + MARGIN_BETWEEN) + block_counter * MARGIN_BLOCK), settings.VISUALIZE_GRAVITY_TREE);
    VISUALIZE_GRAVITY_TREE_BTN.set_button_label(FONT_SIZE, "VISUALIZE QUADTREE ON/OFF");
    button_counter++;

    QUADTREE_THETA_TXT.setString("COEFFICIENT (THETA)");
    QUADTREE_THETA_TXT.setFillColor(sf::Color::White);
    QUADTREE_THETA_TXT.setPosition(WIDTH - MENU_WIDTH + MARGIN_LEFT, MARGIN_TOP + button_counter * (BTN_HEIGHT + MARGIN_BETWEEN) + title_counter * (TITLE_FONT_SIZE + MARGIN_BETWEEN) + label_counter * (FONT_SIZE + MARGIN_BETWEEN) + block_counter * MARGIN_BLOCK);
    QUADTREE_THETA_TXT.setFont(FONT);
    QUADTREE_THETA_TXT.setCharacterSize(FONT_SIZE);
    label_counter++;

    QUADTREE_THETA_TB = TextBox(FONT, sf::Vector2f(MENU_WIDTH - MARGIN_LEFT - MARGIN_RIGHT, BTN_HEIGHT), sf::Vector2f(WIDTH - MENU_WIDTH + MARGIN_LEFT, MARGIN_TOP + button_counter * (BTN_HEIGHT + MARGIN_BETWEEN) + title_counter * (TITLE_FONT_SIZE + MARGIN_BETWEEN) + label_counter * (FONT_SIZE + MARGIN_BETWEEN) + block_counter * MARGIN_BLOCK), settings.THETA, "double");
    QUADTREE_THETA_TB.set_button_label(FONT_SIZE, std::to_string(settings.THETA));
    button_counter++;
    block_counter++;

    // Multithreading
    MULTITHREADING_TXT.setString("MULTITHREADING SETTINGS");
    MULTITHREADING_TXT.setFillColor(sf::Color::White);
    MULTITHREADING_TXT.setPosition(WIDTH - MENU_WIDTH + MARGIN_LEFT, MARGIN_TOP + button_counter * (BTN_HEIGHT + MARGIN_BETWEEN) + title_counter * (TITLE_FONT_SIZE + MARGIN_BETWEEN) + label_counter * (FONT_SIZE + MARGIN_BETWEEN) + block_counter * MARGIN_BLOCK);
    MULTITHREADING_TXT.setFont(FONT);
    MULTITHREADING_TXT.setCharacterSize(TITLE_FONT_SIZE);
    title_counter++;

    // Thread number
    THREAD_NUM_TXT.setString("NUMBER OF THREADS");
    THREAD_NUM_TXT.setFillColor(sf::Color::White);
    THREAD_NUM_TXT.setPosition(WIDTH - MENU_WIDTH + MARGIN_LEFT, MARGIN_TOP + button_counter * (BTN_HEIGHT + MARGIN_BETWEEN) + title_counter * (TITLE_FONT_SIZE + MARGIN_BETWEEN) + label_counter * (FONT_SIZE + MARGIN_BETWEEN) + block_counter * MARGIN_BLOCK);
    THREAD_NUM_TXT.setFont(FONT);
    THREAD_NUM_TXT.setCharacterSize(FONT_SIZE);
    label_counter++;

    THREAD_NUM_TB = TextBox(FONT, sf::Vector2f(MENU_WIDTH - MARGIN_LEFT - MARGIN_RIGHT, BTN_HEIGHT), sf::Vector2f(WIDTH - MENU_WIDTH + MARGIN_LEFT, MARGIN_TOP + button_counter * (BTN_HEIGHT + MARGIN_BETWEEN) + title_counter * (TITLE_FONT_SIZE + MARGIN_BETWEEN) + label_counter * (FONT_SIZE + MARGIN_BETWEEN) + block_counter * MARGIN_BLOCK), settings.THREAD_NUM, "int");
    THREAD_NUM_TB.set_button_label(FONT_SIZE, std::to_string(settings.THREAD_NUM));
    button_counter++;
    block_counter++;

    // Audio title
    AUDIO_TITLE.setString("AUDIO");
    AUDIO_TITLE.setFillColor(sf::Color::White);
    AUDIO_TITLE.setPosition(WIDTH - MENU_WIDTH + MARGIN_LEFT, MARGIN_TOP + button_counter * (BTN_HEIGHT + MARGIN_BETWEEN) + title_counter * (TITLE_FONT_SIZE + MARGIN_BETWEEN) + label_counter * (FONT_SIZE + MARGIN_BETWEEN) + block_counter * MARGIN_BLOCK);
    AUDIO_TITLE.setFont(FONT);
    AUDIO_TITLE.setCharacterSize(2 * TITLE_FONT_SIZE);
    title_counter++;
    block_counter++;

    // Sound settings
    SOUND_TXT.setString("SOUNDS");
    SOUND_TXT.setFillColor(sf::Color::White);
    SOUND_TXT.setPosition(WIDTH - MENU_WIDTH + MARGIN_LEFT, MARGIN_TOP + button_counter * (BTN_HEIGHT + MARGIN_BETWEEN) + title_counter * (TITLE_FONT_SIZE + MARGIN_BETWEEN) + label_counter * (FONT_SIZE + MARGIN_BETWEEN) + block_counter * MARGIN_BLOCK);
    SOUND_TXT.setFont(FONT);
    SOUND_TXT.setCharacterSize(TITLE_FONT_SIZE);
    title_counter++;

    SOUND_BTN = ToggleButton(FONT, sf::Vector2f((MENU_WIDTH - MARGIN_LEFT - MARGIN_RIGHT) / 2, BTN_HEIGHT), sf::Vector2f(WIDTH - MENU_WIDTH + MARGIN_LEFT, MARGIN_TOP + button_counter * (BTN_HEIGHT + MARGIN_BETWEEN) + title_counter * (TITLE_FONT_SIZE + MARGIN_BETWEEN) + label_counter * (FONT_SIZE + MARGIN_BETWEEN) + block_counter * MARGIN_BLOCK), settings.HAS_SOUND);
    SOUND_BTN.set_button_label(FONT_SIZE, "SOUNDS ON/OFF");

    SOUND_VOLUME_TB = TextBox(FONT, sf::Vector2f((MENU_WIDTH - MARGIN_LEFT - MARGIN_RIGHT) / 2 - MARGIN_BETWEEN, BTN_HEIGHT), sf::Vector2f(WIDTH - MENU_WIDTH + MARGIN_LEFT + (MENU_WIDTH - MARGIN_LEFT - MARGIN_RIGHT) / 2 + MARGIN_BETWEEN, MARGIN_TOP + button_counter * (BTN_HEIGHT + MARGIN_BETWEEN) + title_counter * (TITLE_FONT_SIZE + MARGIN_BETWEEN) + label_counter * (FONT_SIZE + MARGIN_BETWEEN) + block_counter * MARGIN_BLOCK), settings.SOUND_VOLUME, "int");
    SOUND_VOLUME_TB.set_button_label(FONT_SIZE, std::to_string(settings.SOUND_VOLUME));
    SOUND_VOLUME_TB.is_active = settings.HAS_SOUND;
    button_counter++;
    block_counter++;

    // Music settings
    MUSIC_TXT.setString("MUSIC");
    MUSIC_TXT.setFillColor(sf::Color::White);
    MUSIC_TXT.setPosition(WIDTH - MENU_WIDTH + MARGIN_LEFT, MARGIN_TOP + button_counter * (BTN_HEIGHT + MARGIN_BETWEEN) + title_counter * (TITLE_FONT_SIZE + MARGIN_BETWEEN) + label_counter * (FONT_SIZE + MARGIN_BETWEEN) + block_counter * MARGIN_BLOCK);
    MUSIC_TXT.setFont(FONT);
    MUSIC_TXT.setCharacterSize(TITLE_FONT_SIZE);
    title_counter++;

    MUSIC_BTN = ToggleButton(FONT, sf::Vector2f((MENU_WIDTH - MARGIN_LEFT - MARGIN_RIGHT) / 2, BTN_HEIGHT), sf::Vector2f(WIDTH - MENU_WIDTH + MARGIN_LEFT, MARGIN_TOP + button_counter * (BTN_HEIGHT + MARGIN_BETWEEN) + title_counter * (TITLE_FONT_SIZE + MARGIN_BETWEEN) + label_counter * (FONT_SIZE + MARGIN_BETWEEN) + block_counter * MARGIN_BLOCK), settings.HAS_MUSIC);
    MUSIC_BTN.set_button_label(FONT_SIZE, "MUSIC ON/OFF");

    MUSIC_VOLUME_TB = TextBox(FONT, sf::Vector2f((MENU_WIDTH - MARGIN_LEFT - MARGIN_RIGHT) / 2 - MARGIN_BETWEEN, BTN_HEIGHT), sf::Vector2f(WIDTH - MENU_WIDTH + MARGIN_LEFT + (MENU_WIDTH - MARGIN_LEFT - MARGIN_RIGHT) / 2 + MARGIN_BETWEEN, MARGIN_TOP + button_counter * (BTN_HEIGHT + MARGIN_BETWEEN) + title_counter * (TITLE_FONT_SIZE + MARGIN_BETWEEN) + label_counter * (FONT_SIZE + MARGIN_BETWEEN) + block_counter * MARGIN_BLOCK), settings.MUSIC_VOLUME, "int");
    MUSIC_VOLUME_TB.set_button_label(FONT_SIZE, std::to_string(settings.MUSIC_VOLUME));
    MUSIC_VOLUME_TB.is_active = settings.HAS_MUSIC;
    button_counter++;
    block_counter++;

    // Exit
    EXIT_BTN = SimpleButton(FONT, sf::Vector2f(MENU_WIDTH - MARGIN_LEFT - MARGIN_RIGHT, BTN_HEIGHT), sf::Vector2f(WIDTH - MENU_WIDTH + MARGIN_LEFT, HEIGHT - BTN_HEIGHT - MARGIN_BOTTOM));
    EXIT_BTN.set_button_label(FONT_SIZE, "EXIT");
}

bool check_reload_required()
{
    if (settings.PLACEMENT_TYPE != current_settings.PLACEMENT_TYPE || settings.R != current_settings.R
        || settings.SPEED_TYPE != current_settings.SPEED_TYPE || settings.N != current_settings.N
        || settings.RADIUS != current_settings.RADIUS || settings.MASS != current_settings.MASS
        || settings.SINGULARITY_MASS != current_settings.SINGULARITY_MASS
        || settings.COLLISION_CELL_SIZE != current_settings.COLLISION_CELL_SIZE)
        return true;

    return false;
}

void draw_menu(sf::RenderWindow& window)
{
    // Left menu background
    sf::RectangleShape menu_left_background(sf::Vector2f(MENU_WIDTH, HEIGHT));
    menu_left_background.setPosition(0, 0);
    menu_left_background.setFillColor(sf::Color(12, 12, 12, 200));
    window.draw(menu_left_background);

    // Simulation settings elements
    window.draw(SIMULATION_TITLE);

    window.draw(PARTICLE_NUM_TXT);
    PARTICLE_NUM_TB.draw(window);

    window.draw(PARTICLE_PROPS_TXT);
    window.draw(PARTICLE_RADIUS_TXT);
    PARTICLE_RADIUS_TB.draw(window);
    window.draw(PARTICLE_MASS_TXT);
    PARTICLE_MASS_TB.draw(window);

    window.draw(SINGULARITY_MASS_TXT);
    SINGULARITY_MASS_TB.draw(window);

    window.draw(PLACEMENT_TYPE_TXT);
    PLACEMENT_TYPE_CIRCULAR_BTN.draw(window);
    PLACEMENT_TYPE_FULLSCREEN_BTN.draw(window);
    window.draw(PLACEMENT_RADIUS_TXT);
    PLACEMENT_RADIUS_TB.draw(window);

    window.draw(SPEED_TYPE_TXT);
    SPEED_TYPE_ANGULAR_BTN.draw(window);
    SPEED_TYPE_RANDOM_BTN.draw(window);
    SPEED_TYPE_ZERO_BTN.draw(window);
    SPEED_TYPE_GALAXY_BTN.draw(window);

    window.draw(BORDER_TXT);
    HAS_BORDERS_BTN.draw(window);

    window.draw(GRAVITY_TXT);
    HAS_GRAVITY_BTN.draw(window);

    window.draw(DAMPING_TXT);
    HAS_DAMPING_BTN.draw(window);
    window.draw(DAMPING_DIST_TXT);
    DAMPING_DIST_TB.draw(window);
    window.draw(DAMPING_COEFF_TXT);
    DAMPING_COEFF_TB.draw(window);

    window.draw(COLLISION_TXT);
    HAS_COLLISIONS_BTN.draw(window);
    window.draw(COLLISION_THRESHOLD_TXT);
    COLLISION_THRESHOLD_TB.draw(window);
    window.draw(COLLISION_ITERATIONS_TXT);
    COLLISION_ITERATIONS_TB.draw(window);
    window.draw(COLLISION_IMPULSE_COEFF_TXT);
    COLLISION_IMPULSE_COEFF_TB.draw(window);

    if (check_reload_required())
        window.draw(RELOAD_REQUIRED_TXT);

    RELOAD_BTN.draw(window);

    // Right menu background
    sf::RectangleShape menu_right_background(sf::Vector2f(MENU_WIDTH, HEIGHT));
    menu_right_background.setPosition(WIDTH - MENU_WIDTH, 0);
    menu_right_background.setFillColor(sf::Color(12, 12, 12, 200));
    window.draw(menu_right_background);

    // Display settings elements
    window.draw(DISPLAY_TITLE);

    window.draw(ANIMATION_SETTINGS_TXT);
    window.draw(TIMESTEP_TXT);
    TIMESTEP_TB.draw(window);
    window.draw(FPS_LIMIT_TXT);
    FPS_LIMIT_TB.draw(window);

    window.draw(TRAIL_TXT);
    HAS_TRAIL_BTN.draw(window);

    // Optimization settings elements
    window.draw(OPTIMIZATION_TITLE);

    window.draw(COLLISION_OPTIMIZATION_TXT);
    VISUALIZE_GRID_BTN.draw(window);
    VISUALIZE_PARTICLE_CELL_BTN.draw(window);
    VISUALIZE_CELL_MASS_BTN.draw(window);
    VISUALIZE_COM_BTN.draw(window);
    window.draw(COLLISION_CELL_SIZE_TXT);
    COLLISION_CELL_SIZE_TB.draw(window);

    window.draw(GRAVITY_OPTIMIZATION_TXT);
    VISUALIZE_GRAVITY_TREE_BTN.draw(window);
    window.draw(QUADTREE_THETA_TXT);
    QUADTREE_THETA_TB.draw(window);

    // Multithreading settings elements
    window.draw(MULTITHREADING_TXT);
    window.draw(THREAD_NUM_TXT);
    THREAD_NUM_TB.draw(window);

    // Audio settings elements
    window.draw(AUDIO_TITLE);

    window.draw(SOUND_TXT);
    SOUND_BTN.draw(window);
    SOUND_VOLUME_TB.draw(window);

    window.draw(MUSIC_TXT);
    MUSIC_BTN.draw(window);
    MUSIC_VOLUME_TB.draw(window);

    EXIT_BTN.draw(window);
}

void draw_fps(sf::RenderWindow& window)
{
    // FPS
    window.draw(FPS_TXT);

    // Performance
    GRAV_COUNT_TXT.setString("GRAVITATION CALCULATION PER FRAME: " + std::to_string(GRAV_CALC_COUNT));
    window.draw(GRAV_COUNT_TXT);
    QUADTREE_DEPTH_TXT.setString("QUADTREE DEPTH: " + std::to_string(QUADTREE_DEPTH));
    window.draw(QUADTREE_DEPTH_TXT);
    QUADTREE_NODES_TXT.setString("QUADTREE NODES: " + std::to_string(QUADTREE_NODES));
    window.draw(QUADTREE_NODES_TXT);
    QUADTREE_LEAVES_TXT.setString("QUADTREE LEAVES: " + std::to_string(QUADTREE_LEAVES));
    window.draw(QUADTREE_LEAVES_TXT);
    COLL_COUNT_TXT.setString("COLLISION CALCULATION PER FRAME: " + std::to_string(COLL_CALC_COUNT));
    window.draw(COLL_COUNT_TXT);
}

void draw_help(sf::RenderWindow& window)
{
    window.draw(HELP_TXT);
    window.draw(HELP2_TXT);
}

void untoggle_textboxes(sf::RenderWindow& window)
{
    // Simulation settings
    PARTICLE_NUM_TB.set_toggle(false);
    current_settings.N = (int)PARTICLE_NUM_TB.value;

    PARTICLE_RADIUS_TB.set_toggle(false);
    current_settings.RADIUS = (int)PARTICLE_RADIUS_TB.value;
    PARTICLE_MASS_TB.set_toggle(false);
    current_settings.MASS = PARTICLE_MASS_TB.value;

    SINGULARITY_MASS_TB.set_toggle(false);
    current_settings.SINGULARITY_MASS = SINGULARITY_MASS_TB.value;

    PLACEMENT_RADIUS_TB.set_toggle(false);
    current_settings.R = PLACEMENT_RADIUS_TB.value;

    COLLISION_THRESHOLD_TB.set_toggle(false);
    current_settings.COLLISION_THRESHOLD = COLLISION_THRESHOLD_TB.value;
    settings.COLLISION_THRESHOLD = COLLISION_THRESHOLD_TB.value;
    COLLISION_ITERATIONS_TB.set_toggle(false);
    current_settings.COLLISION_ITERATIONS = (int)COLLISION_ITERATIONS_TB.value;
    settings.COLLISION_ITERATIONS = (int)COLLISION_ITERATIONS_TB.value;
    COLLISION_IMPULSE_COEFF_TB.set_toggle(false);
    current_settings.COLLISION_IMPULSE_COEFF = COLLISION_IMPULSE_COEFF_TB.value;
    settings.COLLISION_IMPULSE_COEFF = COLLISION_IMPULSE_COEFF_TB.value;

    DAMPING_DIST_TB.set_toggle(false);
    current_settings.DAMPING_DIST = DAMPING_DIST_TB.value;
    settings.DAMPING_DIST = DAMPING_DIST_TB.value;
    DAMPING_COEFF_TB.set_toggle(false);
    current_settings.DAMPING_COEFF = DAMPING_COEFF_TB.value;
    settings.DAMPING_COEFF = DAMPING_COEFF_TB.value;

    // Display settings
    TIMESTEP_TB.set_toggle(false);
    current_settings.TIMESTEP = TIMESTEP_TB.value;
    settings.TIMESTEP = TIMESTEP_TB.value;
    current_settings.update_damping_coeff();
    settings.update_damping_coeff();
    DAMPING_COEFF_TB.value = settings.DAMPING_COEFF;
    DAMPING_COEFF_TB.set_button_label(FONT_SIZE, std::to_string(settings.DAMPING_COEFF));
    FPS_LIMIT_TB.set_toggle(false);
    settings.FPS_LIMIT = FPS_LIMIT_TB.value;
    current_settings.FPS_LIMIT = FPS_LIMIT_TB.value;
    window.setFramerateLimit(FPS_LIMIT_TB.value);

    // Optimization settings
    COLLISION_CELL_SIZE_TB.set_toggle(false);
    current_settings.COLLISION_CELL_SIZE = COLLISION_CELL_SIZE_TB.value;

    QUADTREE_THETA_TB.set_toggle(false);
    current_settings.THETA = QUADTREE_THETA_TB.value;
    settings.THETA = QUADTREE_THETA_TB.value;

    // Thread number setting
    THREAD_NUM_TB.set_toggle(false);
    current_settings.THREAD_NUM = THREAD_NUM_TB.value;
    settings.THREAD_NUM = THREAD_NUM_TB.value;

    // Audio settings
    SOUND_VOLUME_TB.set_toggle(false);
    if (settings.HAS_SOUND)
    {
        set_sound_volume(SOUND_VOLUME_TB.value);
        current_settings.SOUND_VOLUME = SOUND_VOLUME_TB.value;
        settings.SOUND_VOLUME = SOUND_VOLUME_TB.value;
    }

    MUSIC_VOLUME_TB.set_toggle(false);
    if (settings.HAS_MUSIC)
    {
        set_music_volume(MUSIC_VOLUME_TB.value);
        current_settings.MUSIC_VOLUME = MUSIC_VOLUME_TB.value;
        settings.MUSIC_VOLUME = MUSIC_VOLUME_TB.value;
    }
}

void handle_textbox_input(const sf::Event& event)
{
    // Simulation settings
    PARTICLE_NUM_TB.handle_input(event);
    PARTICLE_RADIUS_TB.handle_input(event);
    PARTICLE_MASS_TB.handle_input(event);
    SINGULARITY_MASS_TB.handle_input(event);

    PLACEMENT_RADIUS_TB.handle_input(event);

    COLLISION_THRESHOLD_TB.handle_input(event);
    COLLISION_ITERATIONS_TB.handle_input(event);
    COLLISION_IMPULSE_COEFF_TB.handle_input(event);

    DAMPING_DIST_TB.handle_input(event);
    DAMPING_COEFF_TB.handle_input(event);

    // Display settings
    TIMESTEP_TB.handle_input(event);
    FPS_LIMIT_TB.handle_input(event);

    // Optimization settings
    COLLISION_CELL_SIZE_TB.handle_input(event);
    QUADTREE_THETA_TB.handle_input(event);
    
    // Thread number setting
    THREAD_NUM_TB.handle_input(event);

    // Audio settings
    SOUND_VOLUME_TB.handle_input(event);
    MUSIC_VOLUME_TB.handle_input(event);
}

void update_button_statuses(sf::RenderWindow& window, sf::Event& event)
{
    // Simulation settings
    PARTICLE_NUM_TB.get_button_status(window, event);

    PARTICLE_RADIUS_TB.get_button_status(window, event);
    PARTICLE_MASS_TB.get_button_status(window, event);

    SINGULARITY_MASS_TB.get_button_status(window, event);

    PLACEMENT_TYPE_CIRCULAR_BTN.get_button_status(window, event);
    PLACEMENT_TYPE_FULLSCREEN_BTN.get_button_status(window, event);
    PLACEMENT_RADIUS_TB.get_button_status(window, event);

    SPEED_TYPE_ANGULAR_BTN.get_button_status(window, event);
    SPEED_TYPE_RANDOM_BTN.get_button_status(window, event);
    SPEED_TYPE_ZERO_BTN.get_button_status(window, event);
    SPEED_TYPE_GALAXY_BTN.get_button_status(window, event);

    HAS_BORDERS_BTN.get_button_status(window, event);

    HAS_GRAVITY_BTN.get_button_status(window, event);

    HAS_DAMPING_BTN.get_button_status(window, event);
    DAMPING_DIST_TB.get_button_status(window, event);
    DAMPING_COEFF_TB.get_button_status(window, event);

    HAS_COLLISIONS_BTN.get_button_status(window, event);
    COLLISION_THRESHOLD_TB.get_button_status(window, event);
    COLLISION_ITERATIONS_TB.get_button_status(window, event);
    COLLISION_IMPULSE_COEFF_TB.get_button_status(window, event);

    RELOAD_BTN.get_button_status(window, event);

    // Display settings
    TIMESTEP_TB.get_button_status(window, event);
    FPS_LIMIT_TB.get_button_status(window, event);

    HAS_TRAIL_BTN.get_button_status(window, event);

    // Optimization settings
    VISUALIZE_GRID_BTN.get_button_status(window, event);
    VISUALIZE_PARTICLE_CELL_BTN.get_button_status(window, event);
    VISUALIZE_CELL_MASS_BTN.get_button_status(window, event);
    VISUALIZE_COM_BTN.get_button_status(window, event);
    COLLISION_CELL_SIZE_TB.get_button_status(window, event);

    VISUALIZE_GRAVITY_TREE_BTN.get_button_status(window, event);
    QUADTREE_THETA_TB.get_button_status(window, event);

    // Thread number setting
    THREAD_NUM_TB.get_button_status(window, event);

    // Audio settings
    SOUND_BTN.get_button_status(window, event);
    SOUND_VOLUME_TB.get_button_status(window, event);
    MUSIC_BTN.get_button_status(window, event);
    MUSIC_VOLUME_TB.get_button_status(window, event);

    EXIT_BTN.get_button_status(window, event);
}

void reload_sim(Grid& optim_grid)
{
    // Load new settings
    settings = current_settings;
    settings.update_dynamic_properties();

    // Init ui
    init_ui();

    // Init particles
    particles = generate_particles(settings.SPAWN_MARGIN, CANVAS_WIDTH - settings.SPAWN_MARGIN, settings.SPAWN_MARGIN, HEIGHT - settings.SPAWN_MARGIN);

    // Init optimization grid
    optim_grid = Grid(settings.COLLISION_CELL_SIZE);
    init_optim_grid(optim_grid);
}

void handle_button_clicks(sf::RenderWindow& window, sf::Event& event, Grid& optim_grid)
{
    // Simulation settings

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
    else if (SINGULARITY_MASS_TB.is_pressed)
    {
        SINGULARITY_MASS_TB.set_toggle(true);
    }

    else if (PLACEMENT_TYPE_CIRCULAR_BTN.is_pressed)
    {
        PLACEMENT_TYPE_CIRCULAR_BTN.set_toggle(true);
        PLACEMENT_TYPE_FULLSCREEN_BTN.set_toggle(false);
        current_settings.PLACEMENT_TYPE = PlacementType::Circular;
        PLACEMENT_RADIUS_TB.is_active = true;
        PLACEMENT_RADIUS_TB.get_button_status(window, event);
    }
    else if (PLACEMENT_TYPE_FULLSCREEN_BTN.is_pressed)
    {
        PLACEMENT_TYPE_CIRCULAR_BTN.set_toggle(false);
        PLACEMENT_TYPE_FULLSCREEN_BTN.set_toggle(true);
        current_settings.PLACEMENT_TYPE = PlacementType::Fullscreen;
        PLACEMENT_RADIUS_TB.is_active = false;
        PLACEMENT_RADIUS_TB.get_button_status(window, event);
    }
    else if (PLACEMENT_RADIUS_TB.is_pressed)
    {
        PLACEMENT_RADIUS_TB.set_toggle(true);
    }

    else if (SPEED_TYPE_ANGULAR_BTN.is_pressed)
    {
        SPEED_TYPE_ANGULAR_BTN.set_toggle(true);
        SPEED_TYPE_RANDOM_BTN.set_toggle(false);
        SPEED_TYPE_ZERO_BTN.set_toggle(false);
        SPEED_TYPE_GALAXY_BTN.set_toggle(false);
        current_settings.SPEED_TYPE = SpeedType::Angular;
    }
    else if (SPEED_TYPE_RANDOM_BTN.is_pressed)
    {
        SPEED_TYPE_ANGULAR_BTN.set_toggle(false);
        SPEED_TYPE_RANDOM_BTN.set_toggle(true);
        SPEED_TYPE_ZERO_BTN.set_toggle(false);
        SPEED_TYPE_GALAXY_BTN.set_toggle(false);
        current_settings.SPEED_TYPE = SpeedType::Random;
    }
    else if (SPEED_TYPE_ZERO_BTN.is_pressed)
    {
        SPEED_TYPE_ANGULAR_BTN.set_toggle(false);
        SPEED_TYPE_RANDOM_BTN.set_toggle(false);
        SPEED_TYPE_ZERO_BTN.set_toggle(true);
        SPEED_TYPE_GALAXY_BTN.set_toggle(false);
        current_settings.SPEED_TYPE = SpeedType::Zero;
    }
    else if (SPEED_TYPE_GALAXY_BTN.is_pressed)
    {
        SPEED_TYPE_ANGULAR_BTN.set_toggle(false);
        SPEED_TYPE_RANDOM_BTN.set_toggle(false);
        SPEED_TYPE_ZERO_BTN.set_toggle(false);
        SPEED_TYPE_GALAXY_BTN.set_toggle(true);
        current_settings.SPEED_TYPE = SpeedType::Galaxy;
        current_settings.HAS_DAMPING = false;
    }

    else if (HAS_BORDERS_BTN.is_pressed)
    {
        current_settings.HAS_BORDERS = !current_settings.HAS_BORDERS;
        settings.HAS_BORDERS = current_settings.HAS_BORDERS;
    }

    else if (HAS_GRAVITY_BTN.is_pressed)
    {
        current_settings.HAS_GRAVITY = !current_settings.HAS_GRAVITY;
        settings.HAS_GRAVITY = current_settings.HAS_GRAVITY;
    }

    else if (HAS_DAMPING_BTN.is_pressed)
    {
        current_settings.HAS_DAMPING = !current_settings.HAS_DAMPING;
        settings.HAS_DAMPING = current_settings.HAS_DAMPING;

        DAMPING_DIST_TB.is_active = current_settings.HAS_DAMPING;
        DAMPING_DIST_TB.get_button_status(window, event);
        DAMPING_COEFF_TB.is_active = current_settings.HAS_DAMPING;
        DAMPING_COEFF_TB.get_button_status(window, event);
    }
    else if (DAMPING_DIST_TB.is_pressed)
    {
        DAMPING_DIST_TB.set_toggle(true);
    }
    else if (DAMPING_COEFF_TB.is_pressed)
    {
        DAMPING_COEFF_TB.set_toggle(true);
    }

    else if (HAS_COLLISIONS_BTN.is_pressed)
    {
        current_settings.HAS_COLLISIONS = !current_settings.HAS_COLLISIONS;
        settings.HAS_COLLISIONS = current_settings.HAS_COLLISIONS;

        COLLISION_THRESHOLD_TB.is_active = current_settings.HAS_COLLISIONS;
        COLLISION_THRESHOLD_TB.get_button_status(window, event);
        COLLISION_ITERATIONS_TB.is_active = current_settings.HAS_COLLISIONS;
        COLLISION_ITERATIONS_TB.get_button_status(window, event);
        COLLISION_IMPULSE_COEFF_TB.is_active = current_settings.HAS_COLLISIONS;
        COLLISION_IMPULSE_COEFF_TB.get_button_status(window, event);
    }
    else if (COLLISION_THRESHOLD_TB.is_pressed)
    {
        COLLISION_THRESHOLD_TB.set_toggle(true);
    }
    else if (COLLISION_ITERATIONS_TB.is_pressed)
    {
        COLLISION_ITERATIONS_TB.set_toggle(true);
    }
    else if (COLLISION_IMPULSE_COEFF_TB.is_pressed)
    {
        COLLISION_IMPULSE_COEFF_TB.set_toggle(true);
    }

    else if (RELOAD_BTN.is_pressed)
    {
        reload_sim(optim_grid);
        update_button_statuses(window, event);
    }

    // Display settings

    else if (TIMESTEP_TB.is_pressed)
        TIMESTEP_TB.set_toggle(true);
    
    else if (FPS_LIMIT_TB.is_pressed)
        FPS_LIMIT_TB.set_toggle(true);

    else if (HAS_TRAIL_BTN.is_pressed)
    {
        current_settings.HAS_TRAIL = !current_settings.HAS_TRAIL;
        settings.HAS_TRAIL = current_settings.HAS_TRAIL;
    }

    // Optimization settings
    else if (VISUALIZE_GRID_BTN.is_pressed)
    {
        current_settings.VISUALIZE_COLLISION_GRID = !current_settings.VISUALIZE_COLLISION_GRID;
        settings.VISUALIZE_COLLISION_GRID = current_settings.VISUALIZE_COLLISION_GRID;

        VISUALIZE_PARTICLE_CELL_BTN.is_active = current_settings.VISUALIZE_COLLISION_GRID;
        VISUALIZE_PARTICLE_CELL_BTN.get_button_status(window, event);
        VISUALIZE_CELL_MASS_BTN.is_active = current_settings.VISUALIZE_COLLISION_GRID;
        VISUALIZE_CELL_MASS_BTN.get_button_status(window, event);
        VISUALIZE_COM_BTN.is_active = current_settings.VISUALIZE_COLLISION_GRID;
        VISUALIZE_COM_BTN.get_button_status(window, event);
    }
    else if (VISUALIZE_PARTICLE_CELL_BTN.is_pressed)
    {
        current_settings.VISUALIZE_COLLISION_PARTICLE_CELL = !current_settings.VISUALIZE_COLLISION_PARTICLE_CELL;
        settings.VISUALIZE_COLLISION_PARTICLE_CELL = current_settings.VISUALIZE_COLLISION_PARTICLE_CELL;
    }
    else if (VISUALIZE_CELL_MASS_BTN.is_pressed)
    {
        current_settings.VISUALIZE_COLLISION_CELL_MASS = !current_settings.VISUALIZE_COLLISION_CELL_MASS;
        settings.VISUALIZE_COLLISION_CELL_MASS = current_settings.VISUALIZE_COLLISION_CELL_MASS;
    }
    else if (VISUALIZE_COM_BTN.is_pressed)
    {
        current_settings.VISUALIZE_COLLISION_COM = !current_settings.VISUALIZE_COLLISION_COM;
        settings.VISUALIZE_COLLISION_COM = current_settings.VISUALIZE_COLLISION_COM;
    }

    else if (COLLISION_CELL_SIZE_TB.is_pressed)
        COLLISION_CELL_SIZE_TB.set_toggle(true);

    else if (VISUALIZE_GRAVITY_TREE_BTN.is_pressed)
    {
        current_settings.VISUALIZE_GRAVITY_TREE = !current_settings.VISUALIZE_GRAVITY_TREE;
        settings.VISUALIZE_GRAVITY_TREE = current_settings.VISUALIZE_GRAVITY_TREE;
    }
    else if (QUADTREE_THETA_TB.is_pressed)
        QUADTREE_THETA_TB.set_toggle(true);

    // Thread number setting
    else if (THREAD_NUM_TB.is_pressed)
        THREAD_NUM_TB.set_toggle(true);
    

    // Audio settings
    else if (SOUND_BTN.is_pressed)
    {
        current_settings.HAS_SOUND = !current_settings.HAS_SOUND;
        settings.HAS_SOUND = current_settings.HAS_SOUND;

        set_sound_volume(current_settings.HAS_SOUND ? SOUND_VOLUME_TB.value : 0);

        SOUND_VOLUME_TB.is_active = current_settings.HAS_SOUND;
        SOUND_VOLUME_TB.get_button_status(window, event);
    }
    else if (SOUND_VOLUME_TB.is_pressed)
        SOUND_VOLUME_TB.set_toggle(true);

    else if (MUSIC_BTN.is_pressed)
    {
        current_settings.HAS_MUSIC = !current_settings.HAS_MUSIC;
        settings.HAS_MUSIC = current_settings.HAS_MUSIC;

        set_music_volume(current_settings.HAS_MUSIC ? MUSIC_VOLUME_TB.value : 0);

        MUSIC_VOLUME_TB.is_active = current_settings.HAS_MUSIC;
        MUSIC_VOLUME_TB.get_button_status(window, event);
    }
    else if (MUSIC_VOLUME_TB.is_pressed)
        MUSIC_VOLUME_TB.set_toggle(true);

    else if (EXIT_BTN.is_pressed)
        window.close();
}

#endif