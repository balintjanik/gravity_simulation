#include <iostream>
#include <vector>

#include "settings.h"
#include "particle.h"
#include "utils.h"

using namespace std;

void update_gravity(vector<Particle>& particles)
{
    for (int i = 0; i < N; i++)
    {
        Particle& p_1 = particles[i];
        float all_force = 0.0f;

        for (int j = 0; j < N; j++)
        {
            if (i == j) continue;

            // Calculate distance and angle
            Particle& p_2 = particles[j];
            float angle = atan2(p_1.position.y - p_2.position.y, p_1.position.x - p_2.position.x);
            float distance = v2f_distance(p_1.position, p_2.position);

            // Dampen angular velocity for close particles
            float min_distance = p_1.radius + p_2.radius + 1;
            if (distance < min_distance + DAMPING_DIST)
                angle = angle * (1 - DAMPING_COEFF);
            
            // Calculate gravitational force
            float g = 1;
            float force = (g * p_1.mass * p_2.mass) / pow(distance, 2);

            // Update velocity
            p_1.velocity.x -= force * cos(angle);
            p_1.velocity.y -= force * sin(angle);
            all_force += force;
        }

        // Update color based on amount of gravitational force
        sf::Color updated_color = map_forces_to_color(all_force);
        p_1.color = updated_color;

        // Bounce back from borders if enabled
        if (HAS_BORDERS) {
            if (p_1.position.x > WIDTH || p_1.position.x < 0) p_1.velocity.x = -p_1.velocity.x;
            if (p_1.position.y > HEIGHT || p_1.position.y < 0) p_1.velocity.y = -p_1.velocity.y;
        }
    }
}

void update_collisions(std::vector<Particle>& particles)
{
    for (int i = 0; i < N; i++)
    {
        Particle& p_1 = particles[i];

        for (int j = i + 1; j < N; j++)
        {
            Particle& p_2 = particles[j];

            // Calculate distances
            float dx = p_2.position.x - p_1.position.x;
            float dy = p_2.position.y - p_1.position.y;
            float distance = v2f_distance(p_1.position, p_2.position);
            float min_distance = p_1.radius + p_2.radius + COLLISION_THRESHOLD;

            // Check collision
            if (distance < min_distance)
            {
                if (HAS_OVERLAPCHECK)
                {
                    float displacement_x = (dx / distance) * (min_distance - distance) / 2.0f;
                    float displacement_y = (dy / distance) * (min_distance - distance) / 2.0f;

                    // Update position directly to avoid overlaps
                    p_1.position.x -= displacement_x;
                    p_1.position.y -= displacement_y;
                    p_2.position.x += displacement_x;
                    p_2.position.y += displacement_y;
                }

                if (HAS_BOUNCEOFF)
                {
                    // Calculate relative velocity
                    float relative_velocity_x = p_2.velocity.x - p_1.velocity.x;
                    float relative_velocity_y = p_2.velocity.y - p_1.velocity.y;

                    // Calculate normal vector
                    float normal_x = dx / distance;
                    float normal_y = dy / distance;

                    // Calculate impulse (change in velocity)
                    float impulse = 1.0f * (relative_velocity_x * normal_x + relative_velocity_y * normal_y) / (p_1.mass + p_2.mass);

                    // Update velocities based on impulse (conservation of momentum)
                    p_1.velocity.x += impulse * normal_x * p_2.mass;
                    p_1.velocity.y += impulse * normal_y * p_2.mass;
                    p_2.velocity.x -= impulse * normal_x * p_1.mass;
                    p_2.velocity.y -= impulse * normal_y * p_1.mass;
                }
            }
            // Dampen velocity of close particles to avoid too fast spinning of planets
            else if (distance < min_distance + DAMPING_DIST)
            {
                p_1.velocity *= (1 - DAMPING_COEFF);
            }
        }
    }
}

void update_trails(vector<Particle>& particles)
{
    for (auto& p : particles)
    {
        if (p.trail.size() > TRAIL_SIZE)
            p.trail.pop_front();
        sf::Vector2f old_position(p.position.x, p.position.y);
        p.trail.push_back(old_position);
    }
}

void update_positions(vector<Particle> &particles)
{
    // Calculate collisions
    update_collisions(particles);

    // Calculate gravitational forces
    update_gravity(particles);

    // Update trails
    if (HAS_TRAIL)
        update_trails(particles);

    // Calculate new positions
    for (auto& p : particles)
    {
        p.position += p.velocity * TIMESTEP;
    }
}