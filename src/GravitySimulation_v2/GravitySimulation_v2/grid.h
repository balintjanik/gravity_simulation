#ifndef GRID_H
#define GRID_H

#include <unordered_set>
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
    int get_cell_index(float x, float y) const
    {
        int cell_x = std::floor(x / cell_size);
        int cell_y = std::floor(y / cell_size);
        return cell_y * width + cell_x;
    }

    // Add particle to grid cell
    void add_particle(const Particle& particle)
    {
        int cell_index = get_cell_index(particle.position.x, particle.position.y);
        if (cell_index < cells.size())
            cells[cell_index].particle_indices.insert(particle.id);
    }

    // Remove particle from grid cell
    void remove_particle(const Particle& particle)
    {
        int cell_index = get_cell_index(particle.position.x, particle.position.y);
        if (cell_index < cells.size())
            cells[cell_index].particle_indices.erase(particle.id);
    }

    // Update particle cell (move from old to new cell if necessary)
    void update_particle_cell(Particle& particle)
    {
        int old_cell_index = get_cell_index(particle.old_position.x, particle.old_position.y);
        int new_cell_index = get_cell_index(particle.position.x, particle.position.y);

        if (old_cell_index != new_cell_index) {
            if (old_cell_index < cells.size())
                cells[old_cell_index].particle_indices.erase(particle.id);
            if (new_cell_index < cells.size())
                cells[new_cell_index].particle_indices.insert(particle.id);
        }
    }

private:
    float cell_size;

    std::vector<Cell> cells;
};

#endif
