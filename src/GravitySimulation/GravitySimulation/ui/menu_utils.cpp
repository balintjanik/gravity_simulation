#include "menu_utils.h"
#include "../grid/grid.h"

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

    final_limit = sf::Vector2f(WIDTH / 2, WIDTH - HEIGHT / 2);
}

int get_x_pos(Side side, int order = 0, int all = 1)
{
    switch (side)
    {
    case Side::Left:
        return MARGIN_LEFT + order * ((MENU_WIDTH - MARGIN_LEFT - MARGIN_RIGHT) / all + MARGIN_BETWEEN / 2);
    case Side::Right:
        return WIDTH - MENU_WIDTH + MARGIN_LEFT + order * ((MENU_WIDTH - MARGIN_LEFT - MARGIN_RIGHT) / all + MARGIN_BETWEEN / 2);
    default:
        break;
    }

    return 0;
}

int get_y_pos(int button_counter, int title_counter, int label_counter, int block_counter)
{
    return MARGIN_TOP + button_counter * (BTN_HEIGHT + MARGIN_BETWEEN) + title_counter * (TITLE_FONT_SIZE + MARGIN_BETWEEN) + label_counter * (FONT_SIZE + MARGIN_BETWEEN) + block_counter * MARGIN_BLOCK;
}

int get_btn_width(int all = 1)
{
    return (MENU_WIDTH - MARGIN_LEFT - MARGIN_RIGHT) / all - (all == 1 ? 0 : MARGIN_BETWEEN / 2);
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
        + key_to_string(PAUSE_KEY) + ": PAUSE\t"
        + key_to_string(FRAMESTEP_KEY) + ": STEP FRAME-BY-FRAME\t"
        + key_to_string(EXIT_KEY) + ": EXIT");
    HELP_TXT.setFillColor(sf::Color::White);
    HELP_TXT.setFont(FONT);
    HELP_TXT.setCharacterSize(TITLE_FONT_SIZE);
    sf::FloatRect help_txt_rect = HELP_TXT.getLocalBounds();
    HELP_TXT.setOrigin(help_txt_rect.width / 2.0f, help_txt_rect.height / 2.0f);
    HELP_TXT.setPosition(WIDTH / 2, HEIGHT - FONT_SIZE - MARGIN_BOTTOM);

    HELP2_TXT.setString(key_to_string(SHOW_MENU_KEY) + ": SHOW/HIDE MENU\t"
        + key_to_string(SHOW_HELP_KEY) + ": SHOW/HIDE HELP\t"
        + key_to_string(SHOW_PERFORMANCE_KEY) + ": SHOW/HIDE PERFORMANCE\t"
        + key_to_string(SHOW_ALL_KEY) + ": SHOW/HIDE EVERYTHING\t");
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
    SIMULATION_TITLE.setPosition(get_x_pos(Side::Left), get_y_pos(button_counter, title_counter, label_counter, block_counter));
    SIMULATION_TITLE.setFont(FONT);
    SIMULATION_TITLE.setCharacterSize(2 * TITLE_FONT_SIZE);
    title_counter++;
    block_counter++;

    // Particle properties settings
    PARTICLE_PROPS_TXT.setString("PARTICLE PROPERTIES");
    PARTICLE_PROPS_TXT.setFillColor(sf::Color::White);
    PARTICLE_PROPS_TXT.setPosition(get_x_pos(Side::Left), get_y_pos(button_counter, title_counter, label_counter, block_counter));
    PARTICLE_PROPS_TXT.setFont(FONT);
    PARTICLE_PROPS_TXT.setCharacterSize(TITLE_FONT_SIZE);
    title_counter++;

    PARTICLE_NUM_TXT.setString("NUMBER OF PARTICLES");
    PARTICLE_NUM_TXT.setFillColor(sf::Color::White);
    PARTICLE_NUM_TXT.setPosition(get_x_pos(Side::Left), get_y_pos(button_counter, title_counter, label_counter, block_counter));
    PARTICLE_NUM_TXT.setFont(FONT);
    PARTICLE_NUM_TXT.setCharacterSize(FONT_SIZE);
    label_counter++;

    PARTICLE_NUM_TB = TextBox(
        FONT,
        sf::Vector2f(get_btn_width(), BTN_HEIGHT),
        sf::Vector2f(get_x_pos(Side::Left), get_y_pos(button_counter, title_counter, label_counter, block_counter)),
        settings.N,
        "int");
    PARTICLE_NUM_TB.set_button_label(FONT_SIZE, std::to_string(settings.N));
    button_counter++;

    PARTICLE_RADIUS_TXT.setString("RADIUS");
    PARTICLE_RADIUS_TXT.setFillColor(sf::Color::White);
    PARTICLE_RADIUS_TXT.setPosition(get_x_pos(Side::Left), get_y_pos(button_counter, title_counter, label_counter, block_counter));
    PARTICLE_RADIUS_TXT.setFont(FONT);
    PARTICLE_RADIUS_TXT.setCharacterSize(FONT_SIZE);

    PARTICLE_MASS_TXT.setString("MASS");
    PARTICLE_MASS_TXT.setFillColor(sf::Color::White);
    PARTICLE_MASS_TXT.setPosition(get_x_pos(Side::Left, 1, 2), get_y_pos(button_counter, title_counter, label_counter, block_counter));
    PARTICLE_MASS_TXT.setFont(FONT);
    PARTICLE_MASS_TXT.setCharacterSize(FONT_SIZE);
    label_counter++;

    PARTICLE_RADIUS_TB = TextBox(
        FONT,
        sf::Vector2f(get_btn_width(2), BTN_HEIGHT),
        sf::Vector2f(get_x_pos(Side::Left, 0, 2), get_y_pos(button_counter, title_counter, label_counter, block_counter)),
        settings.RADIUS,
        "int");
    PARTICLE_RADIUS_TB.set_button_label(FONT_SIZE, std::to_string(settings.RADIUS));

    PARTICLE_MASS_TB = TextBox(
        FONT,
        sf::Vector2f(get_btn_width(2), BTN_HEIGHT),
        sf::Vector2f(get_x_pos(Side::Left, 1, 2), get_y_pos(button_counter, title_counter, label_counter, block_counter)),
        settings.MASS,
        "double");
    PARTICLE_MASS_TB.set_button_label(FONT_SIZE, std::to_string(settings.MASS));
    button_counter++;

    SINGULARITY_MASS_TXT.setString("BLACK HOLE MASS");
    SINGULARITY_MASS_TXT.setFillColor(sf::Color::White);
    SINGULARITY_MASS_TXT.setPosition(get_x_pos(Side::Left), get_y_pos(button_counter, title_counter, label_counter, block_counter));
    SINGULARITY_MASS_TXT.setFont(FONT);
    SINGULARITY_MASS_TXT.setCharacterSize(FONT_SIZE);
    label_counter++;

    SINGULARITY_MASS_TB = TextBox(
        FONT,
        sf::Vector2f(get_btn_width(), BTN_HEIGHT),
        sf::Vector2f(get_x_pos(Side::Left), get_y_pos(button_counter, title_counter, label_counter, block_counter)),
        settings.SINGULARITY_MASS,
        "double");
    SINGULARITY_MASS_TB.set_button_label(FONT_SIZE, std::to_string(settings.SINGULARITY_MASS));
    button_counter++;
    block_counter++;

    // Placement type settings
    PLACEMENT_TYPE_TXT.setString("PLACEMENT TYPE");
    PLACEMENT_TYPE_TXT.setFillColor(sf::Color::White);
    PLACEMENT_TYPE_TXT.setPosition(get_x_pos(Side::Left), get_y_pos(button_counter, title_counter, label_counter, block_counter));
    PLACEMENT_TYPE_TXT.setFont(FONT);
    PLACEMENT_TYPE_TXT.setCharacterSize(TITLE_FONT_SIZE);
    title_counter++;

    PLACEMENT_TYPE_CIRCULAR_BTN = ToggleButton(
        FONT,
        sf::Vector2f(get_btn_width(2), BTN_HEIGHT),
        sf::Vector2f(get_x_pos(Side::Left, 0, 2), get_y_pos(button_counter, title_counter, label_counter, block_counter)),
        settings.PLACEMENT_TYPE == PlacementType::Circular);
    PLACEMENT_TYPE_CIRCULAR_BTN.set_button_label(FONT_SIZE, "CIRCULAR");

    PLACEMENT_TYPE_FULLSCREEN_BTN = ToggleButton(
        FONT,
        sf::Vector2f(get_btn_width(2), BTN_HEIGHT),
        sf::Vector2f(get_x_pos(Side::Left, 1, 2), get_y_pos(button_counter, title_counter, label_counter, block_counter)),
        settings.PLACEMENT_TYPE == PlacementType::Fullscreen);
    PLACEMENT_TYPE_FULLSCREEN_BTN.set_button_label(FONT_SIZE, "FULLSCREEN");
    button_counter++;

    PLACEMENT_RADIUS_TXT.setString("RADIUS");
    PLACEMENT_RADIUS_TXT.setFillColor(sf::Color::White);
    PLACEMENT_RADIUS_TXT.setPosition(get_x_pos(Side::Left), get_y_pos(button_counter, title_counter, label_counter, block_counter));
    PLACEMENT_RADIUS_TXT.setFont(FONT);
    PLACEMENT_RADIUS_TXT.setCharacterSize(FONT_SIZE);
    label_counter++;

    PLACEMENT_RADIUS_TB = TextBox(
        FONT,
        sf::Vector2f(get_btn_width(), BTN_HEIGHT),
        sf::Vector2f(get_x_pos(Side::Left), get_y_pos(button_counter, title_counter, label_counter, block_counter)),
        settings.R,
        "int");
    PLACEMENT_RADIUS_TB.set_button_label(FONT_SIZE, std::to_string(settings.R));
    PLACEMENT_RADIUS_TB.is_active = settings.PLACEMENT_TYPE == PlacementType::Circular;
    button_counter++;

    SPAWN_MARGIN_TXT.setString("MARGIN");
    SPAWN_MARGIN_TXT.setFillColor(sf::Color::White);
    SPAWN_MARGIN_TXT.setPosition(get_x_pos(Side::Left), get_y_pos(button_counter, title_counter, label_counter, block_counter));
    SPAWN_MARGIN_TXT.setFont(FONT);
    SPAWN_MARGIN_TXT.setCharacterSize(FONT_SIZE);
    label_counter++;

    SPAWN_MARGIN_TB = TextBox(
        FONT,
        sf::Vector2f(get_btn_width(), BTN_HEIGHT),
        sf::Vector2f(get_x_pos(Side::Left), get_y_pos(button_counter, title_counter, label_counter, block_counter)),
        settings.SPAWN_MARGIN,
        "int");
    SPAWN_MARGIN_TB.set_button_label(FONT_SIZE, std::to_string(settings.SPAWN_MARGIN));
    SPAWN_MARGIN_TB.is_active = settings.PLACEMENT_TYPE == PlacementType::Fullscreen;
    button_counter++;
    block_counter++;

    // Speed type settings
    SPEED_TYPE_TXT.setString("SPEED TYPE");
    SPEED_TYPE_TXT.setFillColor(sf::Color::White);
    SPEED_TYPE_TXT.setPosition(get_x_pos(Side::Left), get_y_pos(button_counter, title_counter, label_counter, block_counter));
    SPEED_TYPE_TXT.setFont(FONT);
    SPEED_TYPE_TXT.setCharacterSize(TITLE_FONT_SIZE);
    title_counter++;

    SPEED_TYPE_ANGULAR_BTN = ToggleButton(
        FONT,
        sf::Vector2f(get_btn_width(2), BTN_HEIGHT),
        sf::Vector2f(get_x_pos(Side::Left, 0, 2), get_y_pos(button_counter, title_counter, label_counter, block_counter)),
        settings.SPEED_TYPE == SpeedType::Angular);
    SPEED_TYPE_ANGULAR_BTN.set_button_label(FONT_SIZE, "ANGULAR");

    SPEED_TYPE_RANDOM_BTN = ToggleButton(
        FONT,
        sf::Vector2f(get_btn_width(2), BTN_HEIGHT),
        sf::Vector2f(get_x_pos(Side::Left, 1, 2), get_y_pos(button_counter, title_counter, label_counter, block_counter)),
        settings.SPEED_TYPE == SpeedType::Random);
    SPEED_TYPE_RANDOM_BTN.set_button_label(FONT_SIZE, "RANDOM");
    button_counter++;

    SPEED_TYPE_ZERO_BTN = ToggleButton(
        FONT,
        sf::Vector2f(get_btn_width(2), BTN_HEIGHT),
        sf::Vector2f(get_x_pos(Side::Left, 0, 2), get_y_pos(button_counter, title_counter, label_counter, block_counter)),
        settings.SPEED_TYPE == SpeedType::Zero);
    SPEED_TYPE_ZERO_BTN.set_button_label(FONT_SIZE, "ZERO");

    SPEED_TYPE_GALAXY_BTN = ToggleButton(
        FONT,
        sf::Vector2f(get_btn_width(2), BTN_HEIGHT),
        sf::Vector2f(get_x_pos(Side::Left, 1, 2), get_y_pos(button_counter, title_counter, label_counter, block_counter)),
        settings.SPEED_TYPE == SpeedType::Galaxy);
    SPEED_TYPE_GALAXY_BTN.set_button_label(FONT_SIZE, "GALAXY");
    button_counter++;
    block_counter++;

    // Border settings
    BORDER_TXT.setString("BORDER SETTINGS");
    BORDER_TXT.setFillColor(sf::Color::White);
    BORDER_TXT.setPosition(get_x_pos(Side::Left), get_y_pos(button_counter, title_counter, label_counter, block_counter));
    BORDER_TXT.setFont(FONT);
    BORDER_TXT.setCharacterSize(TITLE_FONT_SIZE);
    title_counter++;

    HAS_BORDERS_BTN = ToggleButton(
        FONT,
        sf::Vector2f(get_btn_width(), BTN_HEIGHT),
        sf::Vector2f(get_x_pos(Side::Left), get_y_pos(button_counter, title_counter, label_counter, block_counter)),
        settings.HAS_BORDERS);
    HAS_BORDERS_BTN.set_button_label(FONT_SIZE, "BORDERS ON/OFF");
    button_counter++;
    block_counter++;

    // Gravity settings
    GRAVITY_TXT.setString("GRAVITY SETTINGS");
    GRAVITY_TXT.setFillColor(sf::Color::White);
    GRAVITY_TXT.setPosition(get_x_pos(Side::Left), get_y_pos(button_counter, title_counter, label_counter, block_counter));
    GRAVITY_TXT.setFont(FONT);
    GRAVITY_TXT.setCharacterSize(TITLE_FONT_SIZE);
    title_counter++;

    HAS_GRAVITY_BTN = ToggleButton(
        FONT,
        sf::Vector2f(get_btn_width(), BTN_HEIGHT),
        sf::Vector2f(get_x_pos(Side::Left), get_y_pos(button_counter, title_counter, label_counter, block_counter)),
        settings.HAS_GRAVITY);
    HAS_GRAVITY_BTN.set_button_label(FONT_SIZE, "GRAVITY ON/OFF");
    button_counter++;
    block_counter++;

    // Damping settings
    DAMPING_TXT.setString("DAMPING SETTINGS");
    DAMPING_TXT.setFillColor(sf::Color::White);
    DAMPING_TXT.setPosition(get_x_pos(Side::Left), get_y_pos(button_counter, title_counter, label_counter, block_counter));
    DAMPING_TXT.setFont(FONT);
    DAMPING_TXT.setCharacterSize(TITLE_FONT_SIZE);
    title_counter++;

    HAS_DAMPING_BTN = ToggleButton(
        FONT,
        sf::Vector2f(get_btn_width(), BTN_HEIGHT),
        sf::Vector2f(get_x_pos(Side::Left), get_y_pos(button_counter, title_counter, label_counter, block_counter)),
        settings.HAS_DAMPING);
    HAS_DAMPING_BTN.set_button_label(FONT_SIZE, "DAMPING ON/OFF");
    button_counter++;

    DAMPING_DIST_TXT.setString("DISTANCE");
    DAMPING_DIST_TXT.setFillColor(sf::Color::White);
    DAMPING_DIST_TXT.setPosition(get_x_pos(Side::Left, 0, 2), get_y_pos(button_counter, title_counter, label_counter, block_counter));
    DAMPING_DIST_TXT.setFont(FONT);
    DAMPING_DIST_TXT.setCharacterSize(FONT_SIZE);

    DAMPING_COEFF_TXT.setString("COEFFICIENT");
    DAMPING_COEFF_TXT.setFillColor(sf::Color::White);
    DAMPING_COEFF_TXT.setPosition(get_x_pos(Side::Left, 1, 2), get_y_pos(button_counter, title_counter, label_counter, block_counter));
    DAMPING_COEFF_TXT.setFont(FONT);
    DAMPING_COEFF_TXT.setCharacterSize(FONT_SIZE);
    label_counter++;

    DAMPING_DIST_TB = TextBox(
        FONT,
        sf::Vector2f(get_btn_width(2), BTN_HEIGHT),
        sf::Vector2f(get_x_pos(Side::Left, 0, 2), get_y_pos(button_counter, title_counter, label_counter, block_counter)),
        settings.DAMPING_DIST,
        "double");
    DAMPING_DIST_TB.is_active = settings.HAS_DAMPING;
    DAMPING_DIST_TB.set_button_label(FONT_SIZE, std::to_string(settings.DAMPING_DIST));

    DAMPING_COEFF_TB = TextBox(
        FONT,
        sf::Vector2f(get_btn_width(2), BTN_HEIGHT),
        sf::Vector2f(get_x_pos(Side::Left, 1, 2), get_y_pos(button_counter, title_counter, label_counter, block_counter)),
        settings.DAMPING_COEFF,
        "double");
    DAMPING_COEFF_TB.is_active = settings.HAS_DAMPING;
    DAMPING_COEFF_TB.set_button_label(FONT_SIZE, std::to_string(settings.DAMPING_COEFF));
    button_counter++;
    block_counter++;

    // Collision settings
    COLLISION_TXT.setString("COLLISION SETTINGS");
    COLLISION_TXT.setFillColor(sf::Color::White);
    COLLISION_TXT.setPosition(get_x_pos(Side::Left), get_y_pos(button_counter, title_counter, label_counter, block_counter));
    COLLISION_TXT.setFont(FONT);
    COLLISION_TXT.setCharacterSize(TITLE_FONT_SIZE);
    title_counter++;

    HAS_COLLISIONS_BTN = ToggleButton(
        FONT,
        sf::Vector2f(get_btn_width(), BTN_HEIGHT),
        sf::Vector2f(get_x_pos(Side::Left), get_y_pos(button_counter, title_counter, label_counter, block_counter)),
        settings.HAS_COLLISIONS);
    HAS_COLLISIONS_BTN.set_button_label(FONT_SIZE, "COLLISIONS ON/OFF");
    button_counter++;

    COLLISION_THRESHOLD_TXT.setString("THRESHOLD");
    COLLISION_THRESHOLD_TXT.setFillColor(sf::Color::White);
    COLLISION_THRESHOLD_TXT.setPosition(get_x_pos(Side::Left, 0, 2), get_y_pos(button_counter, title_counter, label_counter, block_counter));
    COLLISION_THRESHOLD_TXT.setFont(FONT);
    COLLISION_THRESHOLD_TXT.setCharacterSize(FONT_SIZE);

    COLLISION_ITERATIONS_TXT.setString("ITERATIONS");
    COLLISION_ITERATIONS_TXT.setFillColor(sf::Color::White);
    COLLISION_ITERATIONS_TXT.setPosition(get_x_pos(Side::Left, 1, 2), get_y_pos(button_counter, title_counter, label_counter, block_counter));
    COLLISION_ITERATIONS_TXT.setFont(FONT);
    COLLISION_ITERATIONS_TXT.setCharacterSize(FONT_SIZE);
    label_counter++;

    COLLISION_THRESHOLD_TB = TextBox(
        FONT,
        sf::Vector2f(get_btn_width(2), BTN_HEIGHT),
        sf::Vector2f(get_x_pos(Side::Left, 0, 2), get_y_pos(button_counter, title_counter, label_counter, block_counter)),
        settings.COLLISION_THRESHOLD,
        "double");
    COLLISION_THRESHOLD_TB.is_active = settings.HAS_COLLISIONS;
    COLLISION_THRESHOLD_TB.set_button_label(FONT_SIZE, std::to_string(settings.COLLISION_THRESHOLD));

    COLLISION_ITERATIONS_TB = TextBox(
        FONT,
        sf::Vector2f(get_btn_width(2), BTN_HEIGHT),
        sf::Vector2f(get_x_pos(Side::Left, 1, 2), get_y_pos(button_counter, title_counter, label_counter, block_counter)),
        settings.COLLISION_ITERATIONS,
        "int");
    COLLISION_ITERATIONS_TB.is_active = settings.HAS_COLLISIONS;
    COLLISION_ITERATIONS_TB.set_button_label(FONT_SIZE, std::to_string(settings.COLLISION_ITERATIONS));
    button_counter++;

    COLLISION_IMPULSE_COEFF_TXT.setString("IMPULSE COEFFICIENT");
    COLLISION_IMPULSE_COEFF_TXT.setFillColor(sf::Color::White);
    COLLISION_IMPULSE_COEFF_TXT.setPosition(get_x_pos(Side::Left), get_y_pos(button_counter, title_counter, label_counter, block_counter));
    COLLISION_IMPULSE_COEFF_TXT.setFont(FONT);
    COLLISION_IMPULSE_COEFF_TXT.setCharacterSize(FONT_SIZE);
    label_counter++;

    COLLISION_IMPULSE_COEFF_TB = TextBox(
        FONT,
        sf::Vector2f(get_btn_width(), BTN_HEIGHT),
        sf::Vector2f(get_x_pos(Side::Left), get_y_pos(button_counter, title_counter, label_counter, block_counter)),
        settings.COLLISION_IMPULSE_COEFF,
        "double");
    COLLISION_IMPULSE_COEFF_TB.is_active = settings.HAS_COLLISIONS;
    COLLISION_IMPULSE_COEFF_TB.set_button_label(FONT_SIZE, std::to_string(settings.COLLISION_IMPULSE_COEFF));
    button_counter++;
    block_counter++;

    // Restart simulation
    RELOAD_REQUIRED_TXT.setString("RELOAD REQUIRED");
    RELOAD_REQUIRED_TXT.setFillColor(sf::Color::Red);
    RELOAD_REQUIRED_TXT.setPosition(get_x_pos(Side::Left), HEIGHT - MARGIN_BOTTOM - BTN_HEIGHT - MARGIN_BETWEEN - FONT_SIZE);
    RELOAD_REQUIRED_TXT.setFont(FONT);
    RELOAD_REQUIRED_TXT.setCharacterSize(FONT_SIZE);

    RELOAD_BTN = SimpleButton(
        FONT,
        sf::Vector2f(get_btn_width(), BTN_HEIGHT),
        sf::Vector2f(get_x_pos(Side::Left), HEIGHT - BTN_HEIGHT - MARGIN_BOTTOM));
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
    DISPLAY_TITLE.setPosition(get_x_pos(Side::Right), get_y_pos(button_counter, title_counter, label_counter, block_counter));
    DISPLAY_TITLE.setFont(FONT);
    DISPLAY_TITLE.setCharacterSize(2 * TITLE_FONT_SIZE);
    title_counter++;
    block_counter++;

    // Animation settings
    ANIMATION_SETTINGS_TXT.setString("ANIMATION SETTINGS");
    ANIMATION_SETTINGS_TXT.setFillColor(sf::Color::White);
    ANIMATION_SETTINGS_TXT.setPosition(get_x_pos(Side::Right), get_y_pos(button_counter, title_counter, label_counter, block_counter));
    ANIMATION_SETTINGS_TXT.setFont(FONT);
    ANIMATION_SETTINGS_TXT.setCharacterSize(TITLE_FONT_SIZE);
    title_counter++;

    PAUSE_BTN = SimpleButton(
        FONT,
        sf::Vector2f(get_btn_width(2), BTN_HEIGHT),
        sf::Vector2f(get_x_pos(Side::Right, 0, 2), get_y_pos(button_counter, title_counter, label_counter, block_counter)));
    PAUSE_BTN.set_button_label(FONT_SIZE, (settings.IS_PLAYING ? "PAUSE" : "PLAY"));

    FRAMESTEP_BTN = SimpleButton(
        FONT,
        sf::Vector2f(get_btn_width(2), BTN_HEIGHT),
        sf::Vector2f(get_x_pos(Side::Right, 1, 2), get_y_pos(button_counter, title_counter, label_counter, block_counter)));
    FRAMESTEP_BTN.set_button_label(FONT_SIZE, "FRAME STEP");
    button_counter++;

    TIMESTEP_TXT.setString("TIMESTEP");
    TIMESTEP_TXT.setFillColor(sf::Color::White);
    TIMESTEP_TXT.setPosition(get_x_pos(Side::Right, 0, 2), get_y_pos(button_counter, title_counter, label_counter, block_counter));
    TIMESTEP_TXT.setFont(FONT);
    TIMESTEP_TXT.setCharacterSize(FONT_SIZE);

    FPS_LIMIT_TXT.setString("FPS LIMIT");
    FPS_LIMIT_TXT.setFillColor(sf::Color::White);
    FPS_LIMIT_TXT.setPosition(get_x_pos(Side::Right, 1, 2), get_y_pos(button_counter, title_counter, label_counter, block_counter));
    FPS_LIMIT_TXT.setFont(FONT);
    FPS_LIMIT_TXT.setCharacterSize(FONT_SIZE);
    label_counter++;

    TIMESTEP_TB = TextBox(
        FONT,
        sf::Vector2f(get_btn_width(2), BTN_HEIGHT),
        sf::Vector2f(get_x_pos(Side::Right, 0, 2), get_y_pos(button_counter, title_counter, label_counter, block_counter)),
        settings.TIMESTEP,
        "double");
    TIMESTEP_TB.set_button_label(FONT_SIZE, std::to_string(settings.TIMESTEP));

    FPS_LIMIT_TB = TextBox(
        FONT,
        sf::Vector2f(get_btn_width(2), BTN_HEIGHT),
        sf::Vector2f(get_x_pos(Side::Right, 1, 2), get_y_pos(button_counter, title_counter, label_counter, block_counter)),
        settings.FPS_LIMIT,
        "int");
    FPS_LIMIT_TB.set_button_label(FONT_SIZE, std::to_string(settings.FPS_LIMIT));
    button_counter++;
    block_counter++;

    // Trail settings
    TRAIL_TXT.setString("TRAIL SETTINGS");
    TRAIL_TXT.setFillColor(sf::Color::White);
    TRAIL_TXT.setPosition(get_x_pos(Side::Right), get_y_pos(button_counter, title_counter, label_counter, block_counter));
    TRAIL_TXT.setFont(FONT);
    TRAIL_TXT.setCharacterSize(TITLE_FONT_SIZE);
    title_counter++;

    HAS_TRAIL_BTN = ToggleButton(
        FONT,
        sf::Vector2f(get_btn_width(), BTN_HEIGHT),
        sf::Vector2f(get_x_pos(Side::Right), get_y_pos(button_counter, title_counter, label_counter, block_counter)),
        settings.HAS_TRAIL);
    HAS_TRAIL_BTN.set_button_label(FONT_SIZE, "TRAILS ON/OFF");
    button_counter++;
    block_counter++;

    // Optimization title
    OPTIMIZATION_TITLE.setString("OPTIMIZATION");
    OPTIMIZATION_TITLE.setFillColor(sf::Color::White);
    OPTIMIZATION_TITLE.setPosition(get_x_pos(Side::Right), get_y_pos(button_counter, title_counter, label_counter, block_counter));
    OPTIMIZATION_TITLE.setFont(FONT);
    OPTIMIZATION_TITLE.setCharacterSize(2 * TITLE_FONT_SIZE);
    title_counter++;
    block_counter++;

    // Collision optimization settings
    COLLISION_OPTIMIZATION_TXT.setString("COLLISION OPTIMIZATION");
    COLLISION_OPTIMIZATION_TXT.setFillColor(sf::Color::White);
    COLLISION_OPTIMIZATION_TXT.setPosition(get_x_pos(Side::Right), get_y_pos(button_counter, title_counter, label_counter, block_counter));
    COLLISION_OPTIMIZATION_TXT.setFont(FONT);
    COLLISION_OPTIMIZATION_TXT.setCharacterSize(TITLE_FONT_SIZE);
    title_counter++;

    SHOW_GRID_BTN = ToggleButton(
        FONT,
        sf::Vector2f(get_btn_width(), BTN_HEIGHT),
        sf::Vector2f(get_x_pos(Side::Right), get_y_pos(button_counter, title_counter, label_counter, block_counter)),
        settings.VISUALIZE_COLLISION_GRID);
    SHOW_GRID_BTN.set_button_label(FONT_SIZE, "SHOW GRID ON/OFF");
    button_counter++;

    SHOW_PARTICLE_CELL_BTN = ToggleButton(
        FONT,
        sf::Vector2f(get_btn_width(), BTN_HEIGHT),
        sf::Vector2f(get_x_pos(Side::Right), get_y_pos(button_counter, title_counter, label_counter, block_counter)),
        settings.VISUALIZE_COLLISION_PARTICLE_CELL);
    SHOW_PARTICLE_CELL_BTN.set_button_label(FONT_SIZE, "SHOW PARTICLES' CELL ON/OFF");
    SHOW_PARTICLE_CELL_BTN.is_active = settings.VISUALIZE_COLLISION_GRID;
    button_counter++;

    SHOW_CELL_MASS_BTN = ToggleButton(
        FONT,
        sf::Vector2f(get_btn_width(), BTN_HEIGHT),
        sf::Vector2f(get_x_pos(Side::Right), get_y_pos(button_counter, title_counter, label_counter, block_counter)),
        settings.VISUALIZE_COLLISION_CELL_MASS);
    SHOW_CELL_MASS_BTN.set_button_label(FONT_SIZE, "SHOW CELLS' MASS ON/OFF");
    SHOW_CELL_MASS_BTN.is_active = settings.VISUALIZE_COLLISION_GRID;
    button_counter++;

    SHOW_COM_BTN = ToggleButton(
        FONT,
        sf::Vector2f(get_btn_width(), BTN_HEIGHT),
        sf::Vector2f(get_x_pos(Side::Right), get_y_pos(button_counter, title_counter, label_counter, block_counter)),
        settings.VISUALIZE_COLLISION_COM);
    SHOW_COM_BTN.set_button_label(FONT_SIZE, "SHOW CELLS' CENTER OF MASS ON/OFF");
    SHOW_COM_BTN.is_active = settings.VISUALIZE_COLLISION_GRID;
    button_counter++;

    COLLISION_CELL_SIZE_TXT.setString("CELL SIZE");
    COLLISION_CELL_SIZE_TXT.setFillColor(sf::Color::White);
    COLLISION_CELL_SIZE_TXT.setPosition(get_x_pos(Side::Right), get_y_pos(button_counter, title_counter, label_counter, block_counter));
    COLLISION_CELL_SIZE_TXT.setFont(FONT);
    COLLISION_CELL_SIZE_TXT.setCharacterSize(FONT_SIZE);
    label_counter++;

    COLLISION_CELL_SIZE_TB = TextBox(
        FONT,
        sf::Vector2f(get_btn_width(), BTN_HEIGHT),
        sf::Vector2f(get_x_pos(Side::Right), get_y_pos(button_counter, title_counter, label_counter, block_counter)),
        settings.COLLISION_CELL_SIZE,
        "int");
    COLLISION_CELL_SIZE_TB.set_button_label(FONT_SIZE, std::to_string(settings.COLLISION_CELL_SIZE));
    button_counter++;
    block_counter++;

    // Gravity optimization settings
    GRAVITY_OPTIMIZATION_TXT.setString("GRAVITY OPTIMIZATION");
    GRAVITY_OPTIMIZATION_TXT.setFillColor(sf::Color::White);
    GRAVITY_OPTIMIZATION_TXT.setPosition(get_x_pos(Side::Right), get_y_pos(button_counter, title_counter, label_counter, block_counter));
    GRAVITY_OPTIMIZATION_TXT.setFont(FONT);
    GRAVITY_OPTIMIZATION_TXT.setCharacterSize(TITLE_FONT_SIZE);
    title_counter++;

    VISUALIZE_GRAVITY_TREE_BTN = ToggleButton(
        FONT,
        sf::Vector2f(get_btn_width(), BTN_HEIGHT),
        sf::Vector2f(get_x_pos(Side::Right), get_y_pos(button_counter, title_counter, label_counter, block_counter)),
        settings.VISUALIZE_GRAVITY_TREE);
    VISUALIZE_GRAVITY_TREE_BTN.set_button_label(FONT_SIZE, "SHOW QUADTREE ON/OFF");
    button_counter++;

    QUADTREE_THETA_TXT.setString("COEFFICIENT (THETA)");
    QUADTREE_THETA_TXT.setFillColor(sf::Color::White);
    QUADTREE_THETA_TXT.setPosition(get_x_pos(Side::Right), get_y_pos(button_counter, title_counter, label_counter, block_counter));
    QUADTREE_THETA_TXT.setFont(FONT);
    QUADTREE_THETA_TXT.setCharacterSize(FONT_SIZE);
    label_counter++;

    QUADTREE_THETA_TB = TextBox(
        FONT,
        sf::Vector2f(get_btn_width(), BTN_HEIGHT),
        sf::Vector2f(get_x_pos(Side::Right), get_y_pos(button_counter, title_counter, label_counter, block_counter)),
        settings.THETA,
        "double");
    QUADTREE_THETA_TB.set_button_label(FONT_SIZE, std::to_string(settings.THETA));
    button_counter++;
    block_counter++;

    // Multithreading
    MULTITHREADING_TXT.setString("MULTITHREADING SETTINGS");
    MULTITHREADING_TXT.setFillColor(sf::Color::White);
    MULTITHREADING_TXT.setPosition(get_x_pos(Side::Right), get_y_pos(button_counter, title_counter, label_counter, block_counter));
    MULTITHREADING_TXT.setFont(FONT);
    MULTITHREADING_TXT.setCharacterSize(TITLE_FONT_SIZE);
    title_counter++;

    // Thread number
    THREAD_NUM_TXT.setString("NUMBER OF THREADS");
    THREAD_NUM_TXT.setFillColor(sf::Color::White);
    THREAD_NUM_TXT.setPosition(get_x_pos(Side::Right), get_y_pos(button_counter, title_counter, label_counter, block_counter));
    THREAD_NUM_TXT.setFont(FONT);
    THREAD_NUM_TXT.setCharacterSize(FONT_SIZE);
    label_counter++;

    THREAD_NUM_TB = TextBox(
        FONT,
        sf::Vector2f(get_btn_width(), BTN_HEIGHT),
        sf::Vector2f(get_x_pos(Side::Right), get_y_pos(button_counter, title_counter, label_counter, block_counter)),
        settings.THREAD_NUM,
        "int");
    THREAD_NUM_TB.set_button_label(FONT_SIZE, std::to_string(settings.THREAD_NUM));
    button_counter++;
    block_counter++;

    // Audio title
    AUDIO_TITLE.setString("AUDIO");
    AUDIO_TITLE.setFillColor(sf::Color::White);
    AUDIO_TITLE.setPosition(get_x_pos(Side::Right), get_y_pos(button_counter, title_counter, label_counter, block_counter));
    AUDIO_TITLE.setFont(FONT);
    AUDIO_TITLE.setCharacterSize(2 * TITLE_FONT_SIZE);
    title_counter++;
    block_counter++;

    // Sound settings
    SOUND_TXT.setString("SOUNDS");
    SOUND_TXT.setFillColor(sf::Color::White);
    SOUND_TXT.setPosition(get_x_pos(Side::Right), get_y_pos(button_counter, title_counter, label_counter, block_counter));
    SOUND_TXT.setFont(FONT);
    SOUND_TXT.setCharacterSize(TITLE_FONT_SIZE);
    title_counter++;

    SOUND_BTN = ToggleButton(
        FONT,
        sf::Vector2f(get_btn_width(2), BTN_HEIGHT),
        sf::Vector2f(get_x_pos(Side::Right, 0, 2), get_y_pos(button_counter, title_counter, label_counter, block_counter)),
        settings.HAS_SOUND);
    SOUND_BTN.set_button_label(FONT_SIZE, "SOUNDS ON/OFF");

    SOUND_VOLUME_TB = TextBox(
        FONT,
        sf::Vector2f(get_btn_width(2), BTN_HEIGHT),
        sf::Vector2f(get_x_pos(Side::Right, 1, 2), get_y_pos(button_counter, title_counter, label_counter, block_counter)),
        settings.SOUND_VOLUME,
        "int");
    SOUND_VOLUME_TB.set_button_label(FONT_SIZE, std::to_string(settings.SOUND_VOLUME));
    SOUND_VOLUME_TB.is_active = settings.HAS_SOUND;
    button_counter++;
    block_counter++;

    // Music settings
    MUSIC_TXT.setString("MUSIC");
    MUSIC_TXT.setFillColor(sf::Color::White);
    MUSIC_TXT.setPosition(get_x_pos(Side::Right), get_y_pos(button_counter, title_counter, label_counter, block_counter));
    MUSIC_TXT.setFont(FONT);
    MUSIC_TXT.setCharacterSize(TITLE_FONT_SIZE);
    title_counter++;

    MUSIC_BTN = ToggleButton(
        FONT,
        sf::Vector2f(get_btn_width(2), BTN_HEIGHT),
        sf::Vector2f(get_x_pos(Side::Right, 0, 2), get_y_pos(button_counter, title_counter, label_counter, block_counter)),
        settings.HAS_MUSIC);
    MUSIC_BTN.set_button_label(FONT_SIZE, "MUSIC ON/OFF");

    MUSIC_VOLUME_TB = TextBox(
        FONT,
        sf::Vector2f(get_btn_width(2), BTN_HEIGHT),
        sf::Vector2f(get_x_pos(Side::Right, 1, 2), get_y_pos(button_counter, title_counter, label_counter, block_counter)),
        settings.MUSIC_VOLUME,
        "int");
    MUSIC_VOLUME_TB.set_button_label(FONT_SIZE, std::to_string(settings.MUSIC_VOLUME));
    MUSIC_VOLUME_TB.is_active = settings.HAS_MUSIC;
    button_counter++;
    block_counter++;

    // Exit
    EXIT_BTN = SimpleButton(
        FONT,
        sf::Vector2f(get_btn_width(), BTN_HEIGHT),
        sf::Vector2f(get_x_pos(Side::Right), HEIGHT - BTN_HEIGHT - MARGIN_BOTTOM));
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
    window.draw(SPAWN_MARGIN_TXT);
    SPAWN_MARGIN_TB.draw(window);

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
    PAUSE_BTN.draw(window);
    FRAMESTEP_BTN.draw(window);
    window.draw(TIMESTEP_TXT);
    TIMESTEP_TB.draw(window);
    window.draw(FPS_LIMIT_TXT);
    FPS_LIMIT_TB.draw(window);

    window.draw(TRAIL_TXT);
    HAS_TRAIL_BTN.draw(window);

    // Optimization settings elements
    window.draw(OPTIMIZATION_TITLE);

    window.draw(COLLISION_OPTIMIZATION_TXT);
    SHOW_GRID_BTN.draw(window);
    SHOW_PARTICLE_CELL_BTN.draw(window);
    SHOW_CELL_MASS_BTN.draw(window);
    SHOW_COM_BTN.draw(window);
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

void update_performance_position()
{
    FPS_TXT.setPosition((SHOW_MENU ? MENU_WIDTH : 0) + MARGIN_LEFT, FPS_TXT.getPosition().y);
    GRAV_COUNT_TXT.setPosition((SHOW_MENU ? MENU_WIDTH : 0) + MARGIN_LEFT, GRAV_COUNT_TXT.getPosition().y);
    QUADTREE_DEPTH_TXT.setPosition((SHOW_MENU ? MENU_WIDTH : 0) + MARGIN_LEFT, QUADTREE_DEPTH_TXT.getPosition().y);
    QUADTREE_NODES_TXT.setPosition((SHOW_MENU ? MENU_WIDTH : 0) + MARGIN_LEFT, QUADTREE_NODES_TXT.getPosition().y);
    QUADTREE_LEAVES_TXT.setPosition((SHOW_MENU ? MENU_WIDTH : 0) + MARGIN_LEFT, QUADTREE_LEAVES_TXT.getPosition().y);
    COLL_COUNT_TXT.setPosition((SHOW_MENU ? MENU_WIDTH : 0) + MARGIN_LEFT, COLL_COUNT_TXT.getPosition().y);
}

void handle_hotkeys(sf::RenderWindow& window, const sf::Event& event, Grid& collision_grid)
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
        update_performance_position();

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
        update_performance_position();

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
    // Pause
    else if (event.key.code == PAUSE_KEY)
    {
        handle_pause();
    }
    // Framestep
    else if (event.key.code == FRAMESTEP_KEY)
    {
        handle_framestep();
    }
    // Exit
    else if (event.key.code == EXIT_KEY)
    {
        handle_exit(window);
    }
}

void draw_performance(sf::RenderWindow& window)
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
    SPAWN_MARGIN_TB.set_toggle(false);
    current_settings.SPAWN_MARGIN = SPAWN_MARGIN_TB.value;

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
    SPAWN_MARGIN_TB.handle_input(event);

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
    SPAWN_MARGIN_TB.get_button_status(window, event);

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
    PAUSE_BTN.get_button_status(window, event);
    FRAMESTEP_BTN.get_button_status(window, event);
    TIMESTEP_TB.get_button_status(window, event);
    FPS_LIMIT_TB.get_button_status(window, event);

    HAS_TRAIL_BTN.get_button_status(window, event);

    // Optimization settings
    SHOW_GRID_BTN.get_button_status(window, event);
    SHOW_PARTICLE_CELL_BTN.get_button_status(window, event);
    SHOW_CELL_MASS_BTN.get_button_status(window, event);
    SHOW_COM_BTN.get_button_status(window, event);
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

void reload_sim(Grid& collision_grid)
{
    // Load new settings
    settings = current_settings;
    settings.update_dynamic_properties();

    // Init ui
    init_ui();

    // Init particles
    particles = generate_particles(settings.SPAWN_MARGIN, CANVAS_WIDTH - settings.SPAWN_MARGIN, settings.SPAWN_MARGIN, HEIGHT - settings.SPAWN_MARGIN);

    // Init optimization grid
    collision_grid = Grid(settings.COLLISION_CELL_SIZE);
    init_optim_grid(collision_grid);

    // Reset delta
    map_offset = sf::Vector2f(0, 0);
}

void handle_pause()
{
    current_settings.IS_PLAYING = !current_settings.IS_PLAYING;
    settings.IS_PLAYING = current_settings.IS_PLAYING;

    PAUSE_BTN.set_button_label(FONT_SIZE, (settings.IS_PLAYING ? "PAUSE" : "PLAY"));
}

void handle_framestep()
{
    settings.IS_FRAMESTEP = true;
}

void handle_exit(sf::RenderWindow& window)
{
    window.close();
}

void handle_button_clicks(sf::RenderWindow& window, sf::Event& event, Grid& optim_grid)
{
    // Simulation settings

    if (PLACEMENT_TYPE_CIRCULAR_BTN.is_pressed)
    {
        PLACEMENT_TYPE_CIRCULAR_BTN.set_toggle(true);
        PLACEMENT_TYPE_FULLSCREEN_BTN.set_toggle(false);
        current_settings.PLACEMENT_TYPE = PlacementType::Circular;
        PLACEMENT_RADIUS_TB.is_active = true;
        PLACEMENT_RADIUS_TB.get_button_status(window, event);
        SPAWN_MARGIN_TB.is_active = false;
        SPAWN_MARGIN_TB.get_button_status(window, event);
    }
    else if (PLACEMENT_TYPE_FULLSCREEN_BTN.is_pressed)
    {
        PLACEMENT_TYPE_CIRCULAR_BTN.set_toggle(false);
        PLACEMENT_TYPE_FULLSCREEN_BTN.set_toggle(true);
        current_settings.PLACEMENT_TYPE = PlacementType::Fullscreen;
        PLACEMENT_RADIUS_TB.is_active = false;
        PLACEMENT_RADIUS_TB.get_button_status(window, event);
        SPAWN_MARGIN_TB.is_active = true;
        SPAWN_MARGIN_TB.get_button_status(window, event);
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
        current_settings.HAS_DAMPING = !settings.HAS_DAMPING;
        settings.HAS_DAMPING = current_settings.HAS_DAMPING;

        DAMPING_DIST_TB.is_active = current_settings.HAS_DAMPING;
        DAMPING_DIST_TB.get_button_status(window, event);
        DAMPING_COEFF_TB.is_active = current_settings.HAS_DAMPING;
        DAMPING_COEFF_TB.get_button_status(window, event);
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

    else if (RELOAD_BTN.is_pressed)
    {
        reload_sim(optim_grid);
        update_button_statuses(window, event);
    }

    // Display settings
    else if (PAUSE_BTN.is_pressed)
    {
        handle_pause();
    }
    else if (FRAMESTEP_BTN.is_pressed)
    {
        handle_framestep();
    }
    else if (HAS_TRAIL_BTN.is_pressed)
    {
        current_settings.HAS_TRAIL = !current_settings.HAS_TRAIL;
        settings.HAS_TRAIL = current_settings.HAS_TRAIL;
    }

    // Optimization settings
    else if (SHOW_GRID_BTN.is_pressed)
    {
        current_settings.VISUALIZE_COLLISION_GRID = !current_settings.VISUALIZE_COLLISION_GRID;
        settings.VISUALIZE_COLLISION_GRID = current_settings.VISUALIZE_COLLISION_GRID;

        SHOW_PARTICLE_CELL_BTN.is_active = current_settings.VISUALIZE_COLLISION_GRID;
        SHOW_PARTICLE_CELL_BTN.get_button_status(window, event);
        SHOW_CELL_MASS_BTN.is_active = current_settings.VISUALIZE_COLLISION_GRID;
        SHOW_CELL_MASS_BTN.get_button_status(window, event);
        SHOW_COM_BTN.is_active = current_settings.VISUALIZE_COLLISION_GRID;
        SHOW_COM_BTN.get_button_status(window, event);

        // Turn off gravity tree automatically
        VISUALIZE_GRAVITY_TREE_BTN.set_toggle(false);
        current_settings.VISUALIZE_GRAVITY_TREE = false;
        settings.VISUALIZE_GRAVITY_TREE = false;
    }
    else if (SHOW_PARTICLE_CELL_BTN.is_pressed)
    {
        current_settings.VISUALIZE_COLLISION_PARTICLE_CELL = !current_settings.VISUALIZE_COLLISION_PARTICLE_CELL;
        settings.VISUALIZE_COLLISION_PARTICLE_CELL = current_settings.VISUALIZE_COLLISION_PARTICLE_CELL;
    }
    else if (SHOW_CELL_MASS_BTN.is_pressed)
    {
        current_settings.VISUALIZE_COLLISION_CELL_MASS = !current_settings.VISUALIZE_COLLISION_CELL_MASS;
        settings.VISUALIZE_COLLISION_CELL_MASS = current_settings.VISUALIZE_COLLISION_CELL_MASS;
    }
    else if (SHOW_COM_BTN.is_pressed)
    {
        current_settings.VISUALIZE_COLLISION_COM = !current_settings.VISUALIZE_COLLISION_COM;
        settings.VISUALIZE_COLLISION_COM = current_settings.VISUALIZE_COLLISION_COM;
    }

    else if (VISUALIZE_GRAVITY_TREE_BTN.is_pressed)
    {
        current_settings.VISUALIZE_GRAVITY_TREE = !current_settings.VISUALIZE_GRAVITY_TREE;
        settings.VISUALIZE_GRAVITY_TREE = current_settings.VISUALIZE_GRAVITY_TREE;

        // Turn off collision grid automatically
        current_settings.VISUALIZE_COLLISION_GRID = false;
        settings.VISUALIZE_COLLISION_GRID = false;

        SHOW_GRID_BTN.set_toggle(false);
        SHOW_PARTICLE_CELL_BTN.is_active = false;
        SHOW_PARTICLE_CELL_BTN.get_button_status(window, event);
        SHOW_CELL_MASS_BTN.is_active = false;
        SHOW_CELL_MASS_BTN.get_button_status(window, event);
        SHOW_COM_BTN.is_active = false;
        SHOW_COM_BTN.get_button_status(window, event);
    }

    // Audio settings
    else if (SOUND_BTN.is_pressed)
    {
        current_settings.HAS_SOUND = !current_settings.HAS_SOUND;
        settings.HAS_SOUND = current_settings.HAS_SOUND;

        set_sound_volume(current_settings.HAS_SOUND ? SOUND_VOLUME_TB.value : 0);

        SOUND_VOLUME_TB.is_active = current_settings.HAS_SOUND;
        SOUND_VOLUME_TB.get_button_status(window, event);
    }

    else if (MUSIC_BTN.is_pressed)
    {
        current_settings.HAS_MUSIC = !current_settings.HAS_MUSIC;
        settings.HAS_MUSIC = current_settings.HAS_MUSIC;

        set_music_volume(current_settings.HAS_MUSIC ? MUSIC_VOLUME_TB.value : 0);

        MUSIC_VOLUME_TB.is_active = current_settings.HAS_MUSIC;
        MUSIC_VOLUME_TB.get_button_status(window, event);
    }

    else if (EXIT_BTN.is_pressed)
        handle_exit(window);
}