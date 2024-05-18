#ifndef GRID_H
#define GRID_H

#include <unordered_set>
#include "settings.h"
#include "particle.h"

struct Cell {
    std::unordered_set<int> particle_indices;
};

class Grid {
public:
    int width, height;

    Grid(float cell_size)
        : width(WIDTH / cell_size), height(HEIGHT / cell_size), cell_size(cell_size) {
        cells.resize((WIDTH / cell_size) * (HEIGHT / cell_size));
    }

    Cell& get(int x, int y)
    {
        return cells[y * width + x];
    }

    // Get cell index based on position
    int get_cell_index(float x, float y) const;

    // Add particle to grid cell
    void add_particle(const Particle& particle);

    // Remove particle from grid cell
    void remove_particle(const Particle& particle);

    // Update particle cell (move from old to new cell if necessary)
    void update_particle_cell(Particle& particle);

private:
    float cell_size;

    std::vector<Cell> cells;
};

#endif
