#include <iostream>
#include <vector>

#include "settings.h"
#include "particle.h"
#include "utils.h"
#include "collision_grid.h"

using namespace std;

void update_gravity(vector<Particle>& particles)
{
    for (int i = 0; i < n; i++)
    {
        float all_force = 0.0f;

        Particle& p_1 = particles[i];
        for (int j = 0; j < n; j++)
        {
            if (i == j) continue;

            Particle& p_2 = particles[j];
            float ang = atan2(p_1.position.y - p_2.position.y, p_1.position.x - p_2.position.x);
            float dist = sqrt((p_1.position.x - p_2.position.x) * (p_1.position.x - p_2.position.x) + (p_1.position.y - p_2.position.y) * (p_1.position.y - p_2.position.y));
            float g = 1;
            float force = 1 / pow(dist, 2);


            p_1.velocity.x -= force * cos(ang);
            p_1.velocity.y -= force * sin(ang);
            all_force += force;
        }

        sf::Color updated_color = mapForcesToColor(all_force);
        p_1.color = updated_color;

        if (has_borders) {
            if (p_1.position.x > width || p_1.position.x < 0) p_1.velocity.x = -p_1.velocity.x;
            if (p_1.position.y > height || p_1.position.y < 0) p_1.velocity.y = -p_1.velocity.y;
        }
        // cout << "Current all_force of particle " << i << " is: " << all_force << " and velocity is: " << p1.velocity.x << "," << p1.velocity.y << " and position is: " << p1.position.x << "," << p1.position.y << endl;
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

            float dx = p_2.position.x - p_1.position.x;
            float dy = p_2.position.y - p_1.position.y;
            float distance = sqrt(dx * dx + dy * dy);
            float minDistance = p_1.radius + p_2.radius + 1;

            if (distance < minDistance) // Collision detected
            {
                // Calculate displacement vector
                float displacementX = (dx / distance) * (minDistance - distance) / 2.0f;
                float displacementY = (dy / distance) * (minDistance - distance) / 2.0f;

                // Move particles away from each other
                p_1.position.x -= displacementX;
                p_1.position.y -= displacementY;
                p_2.position.x += displacementX;
                p_2.position.y += displacementY;
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