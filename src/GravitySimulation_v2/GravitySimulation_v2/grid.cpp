#include "grid.h"

int Grid::get_cell_index(double x, double y) const
{
    int cell_x = std::floor((x + overflow_x / 2) / cell_size);
    int cell_y = std::floor((y + overflow_y / 2) / cell_size);
    return cell_y * width + cell_x;
}

void Grid::add_particle(const Particle& particle)
{
    int cell_index = get_cell_index(particle.position.x, particle.position.y);
    if (cell_index < cells.size())
    {
        cells[cell_index].particle_indices.insert(particle.id);
        update_cell_mass_and_com(cell_index);
    }
}

void Grid::remove_particle(const Particle& particle)
{
    int cell_index = get_cell_index(particle.position.x, particle.position.y);
    if (cell_index < cells.size())
    {
        cells[cell_index].particle_indices.erase(particle.id);
        update_cell_mass_and_com(cell_index);
    }
}

void Grid::update_particle_cell(Particle& particle)
{
    int old_cell_index = get_cell_index(particle.old_position.x, particle.old_position.y);
    int new_cell_index = get_cell_index(particle.position.x, particle.position.y);

    if (old_cell_index != new_cell_index) {
        if (old_cell_index < cells.size())
        {
            cells[old_cell_index].particle_indices.erase(particle.id);
            update_cell_mass_and_com(old_cell_index);
        }
        if (new_cell_index < cells.size())
        {
            cells[new_cell_index].particle_indices.insert(particle.id);
            update_cell_mass_and_com(new_cell_index);
        }
    }
}

void Grid::update_cell_mass_and_com(int cell_index) {
    Cell& cell = cells[cell_index];
    cell.total_mass = 0.0f;
    sf::Vector2f com = { 0.0f, 0.0f };

    for (int particle_id : cell.particle_indices) {
        int idx = get_idx_by_id(particle_id);
        if (idx < 0)
            continue;

        const Particle& particle = particles[idx];
        cell.total_mass += particle.mass;
        com += particle.position * particle.mass;
    }

    if (cell.total_mass > 0.0f) {
        cell.center_of_mass = com / cell.total_mass;
    }
    else {
        cell.center_of_mass = { 0.0f, 0.0f };
    }
}