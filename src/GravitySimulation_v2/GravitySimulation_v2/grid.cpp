#include "grid.h"

int Grid::get_cell_index(float x, float y) const
{
    int cell_x = std::floor(x / cell_size);
    int cell_y = std::floor(y / cell_size);
    return cell_y * width + cell_x;
}

void Grid::add_particle(const Particle& particle)
{
    int cell_index = get_cell_index(particle.position.x, particle.position.y);
    if (cell_index < cells.size())
        cells[cell_index].particle_indices.insert(particle.id);
}

void Grid::remove_particle(const Particle& particle)
{
    int cell_index = get_cell_index(particle.position.x, particle.position.y);
    if (cell_index < cells.size())
        cells[cell_index].particle_indices.erase(particle.id);
}

void Grid::update_particle_cell(Particle& particle)
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