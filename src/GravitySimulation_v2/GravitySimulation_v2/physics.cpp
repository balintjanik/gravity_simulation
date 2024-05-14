#include <iostream>
#include <vector>

#include "settings.h"
#include "particle.h"
#include "utils.h"

using namespace std;

void update_gravity(vector<Particle>& particles)
{
    for (int i = 0; i < n; i++)
    {
        Particle& p_1 = particles[i];
        float all_force = 0.0f;

        for (int j = 0; j < n; j++)
        {
            if (i == j) continue;

            // Calculate distance and angle
            Particle& p_2 = particles[j];
            float angle = atan2(p_1.position.y - p_2.position.y, p_1.position.x - p_2.position.x);
            float distance = sqrt((p_1.position.x - p_2.position.x) * (p_1.position.x - p_2.position.x) + (p_1.position.y - p_2.position.y) * (p_1.position.y - p_2.position.y));
            
            // Calculate gravitational force
            float g = 1;
            float force = (g * p_1.mass * p_2.mass) / pow(distance, 2);

            // Update velocity
            p_1.velocity.x -= force * cos(angle);
            p_1.velocity.y -= force * sin(angle);
            all_force += force;
        }

        // Update color based on amount of gravitational force
        sf::Color updated_color = mapForcesToColor(all_force);
        p_1.color = updated_color;

        // Bounce back from borders if enabled
        if (has_borders) {
            if (p_1.position.x > width || p_1.position.x < 0) p_1.velocity.x = -p_1.velocity.x;
            if (p_1.position.y > height || p_1.position.y < 0) p_1.velocity.y = -p_1.velocity.y;
        }
    }
}

void update_collisions(std::vector<Particle>& particles)
{
    for (int i = 0; i < n; i++)
    {
        Particle& p_1 = particles[i];

        for (int j = i + 1; j < n; j++)
        {
            Particle& p_2 = particles[j];

            // Calculate distances
            float dx = p_2.position.x - p_1.position.x;
            float dy = p_2.position.y - p_1.position.y;
            float distance = sqrt(dx * dx + dy * dy);
            float minDistance = p_1.radius + p_2.radius + 1;

            // Check collision
            if (distance < minDistance)
            {
                float displacementX = (dx / distance) * (minDistance - distance) / 2.0f;
                float displacementY = (dy / distance) * (minDistance - distance) / 2.0f;

                // Update position directly to avoid overlaps
                p_1.position.x -= displacementX;
                p_1.position.y -= displacementY;
                p_2.position.x += displacementX;
                p_2.position.y += displacementY;

                // Calculate relative velocity
                float relativeVelocityX = p_2.velocity.x - p_1.velocity.x;
                float relativeVelocityY = p_2.velocity.y - p_1.velocity.y;

                // Calculate normal vector
                float normalX = dx / distance;
                float normalY = dy / distance;

                // Calculate impulse (change in velocity)
                float impulse = 0.8f * (relativeVelocityX * normalX + relativeVelocityY * normalY) / (p_1.mass + p_2.mass);

                // Update velocities based on impulse (conservation of momentum)
                p_1.velocity.x += impulse * normalX * p_2.mass;
                p_1.velocity.y += impulse * normalY * p_2.mass;
                p_2.velocity.x -= impulse * normalX * p_1.mass;
                p_2.velocity.y -= impulse * normalY * p_1.mass;
            }
        }
    }
}

void update_positions(vector<Particle> &particles, float timestep)
{
    // Calculate collisions
    update_collisions(particles);

    // Calculate gravitational forces
    update_gravity(particles);
    
    // Calculate new positions
    for (auto& p : particles)
    {
        p.position += p.velocity * timestep;
    }
}