#include <vector>

#include "globals.h"
#include "physics.h"

using namespace std;

/*void update_gravity()
{
    for (int i = 0; i < N; i++)
    {
        Particle& p_1 = particles[i];
        double all_force = 0.0f;

        for (int j = 0; j < N; j++)
        {
            if (i == j) continue;

            // Calculate distance and angle
            Particle& p_2 = particles[j];
            double angle = atan2(p_1.position.y - p_2.position.y, p_1.position.x - p_2.position.x);
            double distance = v2f_distance(p_1.position, p_2.position);
            
            // Calculate gravitational force
            double g = 1;
            double force = (g * p_1.mass * p_2.mass) / pow(distance, 2);

            // Dampen angular velocity for close particles
            double min_distance = p_1.radius + p_2.radius + COLLISION_THRESHOLD;
            if (distance < min_distance + DAMPING_DIST)
                angle = angle * (1 - DAMPING_COEFF);

            // Update velocity
            p_1.velocity.x -= force * cos(angle);
            p_1.velocity.y -= force * sin(angle);
            all_force += force;
        }

        // Update color based on amount of gravitational force
        sf::Color updated_color = map_forces_to_color(all_force);
        p_1.color = updated_color;
    }
}*/

void update_gravity(Grid& grid) {
    for (auto& p_1 : particles) {
        sf::Vector2f force = { 0.0f, 0.0f };
        int p1_cell_index = grid.get_cell_index(p_1.position.x, p_1.position.y);
        int p_1_x = std::floor(p_1.position.x / grid.cell_size);
        int p_1_y = std::floor(p_1.position.y / grid.cell_size);

        for (int x = 0; x < grid.width; x++) {
            for (int y = 0; y < grid.height; y++) {
                if (abs(p_1_x - x) <= 1 && abs(p_1_y - y) <= 1)
                    continue;

                const Cell& cell = grid.get(x,y);
                if (cell.total_mass > 0.0f) {
                    sf::Vector2f direction = cell.center_of_mass - p_1.position;
                    double distance = sqrt(direction.x * direction.x + direction.y * direction.y);
                    double g = 1;
                    double force_magnitude = (g * p_1.mass * cell.total_mass) / (distance * distance);
                    force += direction / distance * force_magnitude;
                }
            }
        }

        // Now calculate detailed interactions with neighboring cells
        for (int dx = -1; dx <= 1; ++dx) {
            for (int dy = -1; dy <= 1; ++dy) {
                
                if (p_1_x + dx < 0 || p_1_x + dx >= grid.width
                    || p_1_y + dy < 0 || p_1_y + dy >= grid.height)
                    continue;

                const Cell& cell = grid.get(p_1_x + dx, p_1_y + dy);
                for (int particle_id : cell.particle_indices) {
                    if (particle_id == p_1.id) continue;

                    int idx = get_idx_by_id(particle_id);
                    if (idx < 0)
                        continue;

                    const Particle& p2 = particles[idx];
                    sf::Vector2f direction = p2.position - p_1.position;
                    double distance = sqrt(direction.x * direction.x + direction.y * direction.y);
                    double g = 1;
                    double force_magnitude = (g * p_1.mass * p2.mass) / (distance * distance);
                    force += direction / distance * force_magnitude;
                }
            }
        }

        p_1.velocity += force;
    }
}

void check_cells_collision(Cell& cell_1, Cell& cell_2)
{
    int idx_1, idx_2;

    for (auto it1 = cell_1.particle_indices.begin(); it1 != cell_1.particle_indices.end(); ++it1)
    {
        idx_1 = get_idx_by_id(*it1);
        if (idx_1 < 0)
            continue;

        Particle& p_1 = particles[idx_1];

        for (auto it2 = cell_2.particle_indices.begin(); it2 != cell_2.particle_indices.end(); ++it2)
        {
            idx_2 = get_idx_by_id(*it2);
            if (idx_2 < 0)
                continue;

            Particle& p_2 = particles[idx_2];

            if (p_1.id == p_2.id)
                continue;

            // Calculate distances
            double dx = p_2.position.x - p_1.position.x;
            double dy = p_2.position.y - p_1.position.y;
            double distance = v2f_distance(p_1.position, p_2.position);
            double min_distance = p_1.radius + p_2.radius + COLLISION_THRESHOLD;

            // Check collision
            if (distance < min_distance)
            {
                if (HAS_OVERLAPCHECK)
                {
                    double displacement_x = (dx / distance) * (min_distance - distance) / 2.0f;
                    double displacement_y = (dy / distance) * (min_distance - distance) / 2.0f;

                    // Update position directly to avoid overlaps
                    p_1.position.x -= displacement_x;
                    p_1.position.y -= displacement_y;
                    p_2.position.x += displacement_x;
                    p_2.position.y += displacement_y;
                }

                if (HAS_BOUNCEOFF)
                {
                    // Calculate relative velocity
                    double relative_velocity_x = p_2.velocity.x - p_1.velocity.x;
                    double relative_velocity_y = p_2.velocity.y - p_1.velocity.y;

                    // Calculate normal vector
                    double normal_x = dx / distance;
                    double normal_y = dy / distance;

                    // Calculate impulse (change in velocity)
                    double impulse = 1.0f * (relative_velocity_x * normal_x + relative_velocity_y * normal_y) / (p_1.mass + p_2.mass);

                    // Update velocities based on impulse (conservation of momentum)
                    p_1.velocity.x += impulse * normal_x * p_2.mass;
                    p_1.velocity.y += impulse * normal_y * p_2.mass;
                    p_2.velocity.x -= impulse * normal_x * p_1.mass;
                    p_2.velocity.y -= impulse * normal_y * p_1.mass;
                }
            }
            // Dampen velocity of close particles to avoid too fast spinning of planets
            else if (distance < min_distance + DAMPING_DIST && p_1.id < p_2.id)
            {
                p_1.velocity *= (1 - DAMPING_COEFF);
            }
        }
    }
}

void update_collisions(Grid& collision_grid)
{
    for (int x = 1; x < collision_grid.width - 1; x++)
    {
        for (int y = 1; y < collision_grid.height - 1; y++)
        {
            auto& current_cell = collision_grid.get(x, y);
            for (int dx = -1; dx <= 1; dx++)
            {
                for (int dy = -1; dy <= 1; dy++)
                {
                    auto& other_cell = collision_grid.get(x + dx, y + dy);
                    check_cells_collision(current_cell, other_cell);
                }
            }
        }
    }
}

void update_trails()
{
    for (auto& p : particles)
    {
        if (p.trail.size() > TRAIL_SIZE)
            p.trail.pop_front();
        p.trail.push_back(p.position);
    }
}

void check_borders()
{
    for (auto& p : particles)
    {
        // Bounce back from borders if enabled
        if (p.position.x > WIDTH || p.position.x < 0) p.velocity.x = -p.velocity.x;
        if (p.position.y > HEIGHT || p.position.y < 0) p.velocity.y = -p.velocity.y;
    }
}

void update_positions(Grid& collision_grid)
{
    // Save old positions
    for (auto& p : particles)
    {
        p.old_position = p.position;
    }

    // Calculate collisions
    update_collisions(collision_grid);

    // Calculate gravitational forces
    update_gravity(collision_grid);

    // Update trails
    if (HAS_TRAIL)
        update_trails();

    // Check borders
    if (HAS_BORDERS) {
        check_borders();
    }

    // Calculate new positions
    for (auto& p : particles)
    {
        p.position += p.velocity * TIMESTEP;
        collision_grid.update_particle_cell(p);
    }
}