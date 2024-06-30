#include <vector>

#include "../globals/globals.h"
#include "physics.h"

#include <iostream>

using namespace std;

void update_gravity_quadtree_region(QuadTree& gravity_tree, int start, int end)
{
    // Calculate forces and update positions and velocities
    for (int i = start; i < end; i++) {
        Particle& p = particles[i];
        double all_force = 0.0;
        gravity_tree.calculate_forces(p, all_force);

        // Update color
        sf::Color updated_color = map_forces_to_color(all_force);
        if (!p.is_singularity)
            p.color = updated_color;
    }
}

void update_gravity_quadtree(sf::RenderWindow& window)
{
    // Create the tree
    QuadTree gravity_tree(WIDTH / 2, HEIGHT / 2, WIDTH, settings.THETA);

    // Insert all particles into the tree
    for (const auto& p : particles) {
        gravity_tree.insert(p);
    }

    // Draw quadtree if set
    if (settings.VISUALIZE_GRAVITY_TREE)
        gravity_tree.draw(window);

    // Calculate gravitational forces parallelly on multiple threads
    const int num_threads = settings.THREAD_NUM;
    vector<thread> threads;
    int part_size = particles.size() / num_threads;

    for (int i = 0; i < num_threads; i++) {
        int start = i * part_size;
        int end = (i == num_threads - 1) ? particles.size() : (i + 1) * part_size;

        threads.emplace_back(update_gravity_quadtree_region, ref(gravity_tree), start, end);
    }

    for (auto& t : threads) {
        t.join();
    }
}

void update_gravity_range(Grid& optim_grid, int start, int end) {
    for (int i = start; i < end; i++) {
        auto& p_1 = particles[i];
        double all_force = 0.0;
        int p_1_x = std::floor(p_1.position.x / optim_grid.cell_size);
        int p_1_y = std::floor(p_1.position.y / optim_grid.cell_size);

        for (int x = 0; x < optim_grid.width; x++) {
            for (int y = 0; y < optim_grid.height; y++) {
                if (abs(p_1_x - x) <= 1 && abs(p_1_y - y) <= 1)
                    continue;

                GRAV_CALC_COUNT++;

                const Cell& cell = optim_grid.get(x,y);
                if (cell.total_mass > 0.0) {
                    // Calculate distance and angle
                    double angle = atan2(p_1.position.y - cell.center_of_mass.y, p_1.position.x - cell.center_of_mass.x);
                    double distance = v2f_distance(p_1.position, cell.center_of_mass);

                    // Calculate gravitational force
                    double g = 1;
                    double force = (g * cell.total_mass) / (pow(distance, 2) + pow(EPSYLON, 2));

                    // Update velocity
                    p_1.velocity.x -= force * cos(angle);
                    p_1.velocity.y -= force * sin(angle);
                    all_force += force;
                }
            }
        }

        // Now calculate detailed interactions with neighboring cells
        for (int dx = -1; dx <= 1; ++dx) {
            for (int dy = -1; dy <= 1; ++dy) {
                
                if (p_1_x + dx < 0 || p_1_x + dx >= optim_grid.width
                    || p_1_y + dy < 0 || p_1_y + dy >= optim_grid.height)
                    continue;

                GRAV_CALC_COUNT++;

                const Cell& cell = optim_grid.get(p_1_x + dx, p_1_y + dy);
                for (int particle_id : cell.particle_indices) {
                    if (particle_id == p_1.id) continue;

                    int idx = get_idx_by_id(particle_id);
                    if (idx < 0)
                        continue;

                    const Particle& p_2 = particles[idx];

                    // Calculate distance and angle
                    double angle = atan2(p_1.position.y - p_2.position.y, p_1.position.x - p_2.position.x);
                    double distance = v2f_distance(p_1.position, p_2.position);

                    // Calculate gravitational force
                    double g = 1;
                    double force = (g * p_2.mass) / (pow(distance, 2) + pow(EPSYLON, 2));

                    // Update velocity
                    p_1.velocity.x -= force * cos(angle);
                    p_1.velocity.y -= force * sin(angle);
                    all_force += force;
                }
            }
        }

        // Update color based on amount of gravitational force
        sf::Color updated_color = map_forces_to_color(all_force);
        if (!p_1.is_singularity)
            p_1.color = updated_color;
    }
}

void update_gravity(Grid& optim_grid)
{
    const int num_threads = settings.THREAD_NUM;
    vector<thread> threads;
    int part_size = particles.size() / num_threads;

    for (int i = 0; i < num_threads; i++) {
        int start = i * part_size;
        int end = (i == num_threads - 1) ? particles.size() : (i + 1) * part_size;

        threads.emplace_back(update_gravity_range, ref(optim_grid), start, end);
    }

    for (auto& t : threads) {
        t.join();
    }
}

void check_cells_collision(Cell& cell_1, Cell& cell_2)
{
    int idx_1, idx_2;

    for (int ids_1 : cell_1.particle_indices)
    {
        idx_1 = get_idx_by_id(ids_1);
        if (idx_1 < 0)
            continue;

        Particle& p_1 = particles[idx_1];

        for (int ids_2 : cell_2.particle_indices)
        {
            idx_2 = get_idx_by_id(ids_2);
            if (idx_2 < 0)
                continue;

            COLL_CALC_COUNT++;

            Particle& p_2 = particles[idx_2];

            if (p_1.id == p_2.id)
                continue;

            // Calculate distances
            double dx = p_2.position.x - p_1.position.x;
            double dy = p_2.position.y - p_1.position.y;
            double distance = v2f_distance(p_1.position, p_2.position);
            double min_distance = p_1.radius + p_2.radius + settings.COLLISION_THRESHOLD;

            // Check collision
            if (distance < min_distance)
            {
                double displacement_x = (dx / distance) * (min_distance - distance) / 2.0;
                double displacement_y = (dy / distance) * (min_distance - distance) / 2.0;

                // Update position directly to avoid overlaps
                if (p_1.is_singularity)
                {
                    p_2.position.x += 2 * displacement_x;
                    p_2.position.y += 2 * displacement_y;
                }
                else if (p_2.is_singularity)
                {
                    p_1.position.x -= 2 * displacement_x;
                    p_1.position.y -= 2 * displacement_y;
                }
                else
                {
                    p_1.position.x -= displacement_x;
                    p_1.position.y -= displacement_y;
                    p_2.position.x += displacement_x;
                    p_2.position.y += displacement_y;
                }

                // Calculate relative velocity
                double relative_velocity_x = p_2.velocity.x - p_1.velocity.x;
                double relative_velocity_y = p_2.velocity.y - p_1.velocity.y;

                // Calculate normal vector
                double normal_x = dx / distance;
                double normal_y = dy / distance;

                // Calculate impulse (change in velocity)
                double impulse = settings.COLLISION_IMPULSE_COEFF * (relative_velocity_x * normal_x + relative_velocity_y * normal_y) / (p_1.mass + p_2.mass);

                // Update velocities based on impulse (conservation of momentum)
                p_1.velocity.x += impulse * normal_x * p_2.mass * settings.TIMESTEP;
                p_1.velocity.y += impulse * normal_y * p_2.mass * settings.TIMESTEP;
                p_2.velocity.x -= impulse * normal_x * p_1.mass * settings.TIMESTEP;
                p_2.velocity.y -= impulse * normal_y * p_1.mass * settings.TIMESTEP;

                // Update color based on collision if gravity is off and collision is on
                if (settings.HAS_COLLISIONS && !settings.HAS_GRAVITY)
                {
                    if (!p_1.is_singularity)
                        p_1.color = sf::Color(255, 0, 0);
                    if (!p_2.is_singularity)
                        p_2.color = sf::Color(255, 0, 0);
                }
            }
            // Dampen velocity of close particles to avoid too fast spinning of planets (if enabled)
            else if (settings.HAS_DAMPING &&  distance < min_distance + settings.DAMPING_DIST && p_1.id < p_2.id && (!p_1.is_singularity && !p_2.is_singularity))
            {
                p_1.velocity *= (1 - ((settings.DAMPING_COEFF / 2) / pow(settings.COLLISION_ITERATIONS, 2)));
                p_2.velocity *= (1 - ((settings.DAMPING_COEFF / 2) / pow(settings.COLLISION_ITERATIONS, 2)));
            }
        }
    }
}

void update_collisions_range(Grid& collision_grid, int start_col, int stride)
{
    for (int x = start_col; x < collision_grid.width; x+=stride)
    {
        for (int y = 0; y < collision_grid.height; y++)
        {
            auto& current_cell = collision_grid.get(x, y);
            if (current_cell.particle_indices.empty())
                continue;

            for (int dx = -1; dx <= 1; dx++)
            {
                for (int dy = -1; dy <= 1; dy++)
                {
                    if (x + dx < 0 || x + dx >= collision_grid.width
                        || y + dy < 0 || y + dy >= collision_grid.height)
                        continue;

                    auto& other_cell = collision_grid.get(x + dx, y + dy);

                    if (other_cell.particle_indices.empty())
                        continue;

                    check_cells_collision(current_cell, other_cell);
                }
            }
        }
    }
}

void update_collisions(Grid& collision_grid) {
    const int num_threads = settings.THREAD_NUM;
    vector<thread> threads;

    for (int i = 0; i < num_threads; i++) {
        threads.emplace_back(update_collisions_range, ref(collision_grid), i, num_threads);
    }

    for (auto& t : threads) {
        t.join();
    }
}

void update_trails()
{
    for (auto& p : particles)
    {
        if (p.trail.size() > settings.TRAIL_SIZE)
            p.trail.pop_front();
        p.trail.push_back(p.position);
    }
}

void update_positions(Grid& collision_grid, sf::RenderWindow& window)
{
    GRAV_CALC_COUNT = 0;
    COLL_CALC_COUNT = 0;

    // Update center of mass
    for (int i = 0; i < collision_grid.width; i++)
    {
        for (int j = 0; j < collision_grid.height; j++)
        {
            collision_grid.update_cell_mass_and_com(j * collision_grid.width + i);
        }
    }

    // Save old positions
    for (auto& p : particles)
    {
        p.old_position = p.position;
    }

    // Calculate collisions
    if (settings.HAS_COLLISIONS)
    {
        for (int i = 0; i < settings.COLLISION_ITERATIONS; i++)
        {
            update_collisions(collision_grid);
        }
    }


    // Calculate gravitational forces
    if (settings.HAS_GRAVITY)
    {
        // update_gravity(collision_grid);
        update_gravity_quadtree(window);
    }
    else // Update default coloring
    {
        for (auto& p : particles)
        {
            if (!p.is_singularity)
            {
                int new_val = (p.color.g > 255 - 10 ? 255 : p.color.g + 10);
                p.color = sf::Color(255, new_val, new_val);
            }
        }
    }

    // Update trails
    if (settings.HAS_TRAIL)
        update_trails();

    // Calculate new positions
    for (auto& p : particles)
    {
        p.position += p.velocity * settings.TIMESTEP;

        // Bounce back from borders if enabled
        if (settings.HAS_BORDERS)
        {
            if (p.position.x + p.radius >= CANVAS_WIDTH)
            {
                p.position.x = CANVAS_WIDTH - p.radius;
                p.velocity.x = -p.velocity.x;
            }
            else if (p.position.x - p.radius < 0)
            {
                p.position.x = p.radius;
                p.velocity.x = -p.velocity.x;
            }
            if (p.position.y + p.radius >= HEIGHT)
            {
                p.position.y = HEIGHT - p.radius;
                p.velocity.y = -p.velocity.y;
            }
            else if (p.position.y - p.radius < 0)
            {
                p.position.y = p.radius;
                p.velocity.y = -p.velocity.y;
            }
        }

        // Reassign to new cell in optimization grid if necessary
        collision_grid.update_particle_cell(p);
    }
}