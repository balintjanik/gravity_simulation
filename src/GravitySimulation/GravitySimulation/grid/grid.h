#ifndef GRID_H
#define GRID_H

#include <SFML/Graphics.hpp>
#include <unordered_set>
#include <cmath>
#include "../globals/globals.h"
#include "../utils/utils.h"
#include "../utils/double_vector_ops.h"
#include "../globals/settings.h"
#include "../physics/particle.h"

class Cell {
public:
    std::unordered_set<int> particle_indices;

    double total_mass = 0.0f;
    sf::Vector2f center_of_mass = { 0.0f, 0.0f };
};

class Grid {
public:
    int width, height;
    double cell_size;
    double overflow_x, overflow_y;

    Grid(double cell_size)
        : width(WIDTH / cell_size), height(HEIGHT / cell_size), cell_size(cell_size)
    {
        overflow_x = std::fmod(WIDTH, cell_size);
        overflow_y = std::fmod(HEIGHT, cell_size);
        if (overflow_x != 0)
            width++;
        if (overflow_y != 0)
            height++;
        cells.resize(width * height);
    }

    Cell& get(int x, int y)
    {
        return cells[y * width + x];
    }

    // Get cell index based on position
    int get_cell_index(double x, double y) const;

    // Add particle to grid cell
    void add_particle(const Particle& particle);

    // Remove particle from grid cell
    void remove_particle(const Particle& particle);

    // Update particle cell (move from old to new cell if necessary)
    void update_particle_cell(Particle& particle);

    void update_cell_mass_and_com(int cell_index);
    
private:
    std::vector<Cell> cells;
};

#endif
