#include <iostream>
#include <vector>

#include "settings.h"
#include "particle.h"
#include "utils.h"

using namespace std;

void updatePositions(vector<Particle> &particles, float timestep)
{
    // Calculate gravitational forces
    for (int i = 0; i < n; i++)
    {
        float all_force = 0.0f;

        Particle& p1 = particles[i];
        for (int j = 0; j < n; j++)
        {
            if (i == j) continue;

            Particle& p2 = particles[j];
            float ang = atan2(p1.position.y - p2.position.y, p1.position.x - p2.position.x);
            float dist = sqrt((p1.position.x - p2.position.x) * (p1.position.x - p2.position.x) + (p1.position.y - p2.position.y) * (p1.position.y - p2.position.y));
            float g = 1;
            float force = 1 / pow(dist, 2);


            p1.velocity.x -= force * cos(ang);
            p1.velocity.y -= force * sin(ang);
            all_force += force;
        }

        sf::Color updated_color = mapForcesToColor(all_force);
        p1.color = updated_color;

        p1.position = p1.position + p1.velocity;

        cout << "Current all_force of particle " << i << " is: " << all_force << " and velocity is: " << p1.velocity.x << "," << p1.velocity.y <<
            " and position is: " << p1.position.x << "," << p1.position.y << endl;
    }
}