#ifndef MENU_UTILS_H
#define MENU_UTILS_H

#include "../globals/settings.h"
#include "../globals/globals.h"
#include "../utils/utils.h"
#include "../utils/key_conversion.h"

enum class Side
{
    Left,
    Right
};


void update_fps();

void recalc_sizes(int width, int height);

void init_ui();

bool check_reload_required();

void draw_menu(sf::RenderWindow& window);

void update_performance_position();

void handle_hotkeys(sf::RenderWindow& window, const sf::Event& event, Grid& collision_grid);

void draw_performance(sf::RenderWindow& window);

void draw_help(sf::RenderWindow& window);

void untoggle_textboxes(sf::RenderWindow& window);

void handle_textbox_input(const sf::Event& event);

void update_button_statuses(sf::RenderWindow& window, sf::Event& event);

void reload_sim(Grid& collision_grid);

void handle_pause();

void handle_framestep();

void handle_exit(sf::RenderWindow& window);

void handle_button_clicks(sf::RenderWindow& window, sf::Event& event, Grid& optim_grid);

#endif