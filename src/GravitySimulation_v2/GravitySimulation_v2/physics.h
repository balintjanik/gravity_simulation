#ifndef PHYSICS_H
#define PHYSICS_H

#include <vector>
#include "particle.h"

void update_positions(std::vector<Particle>& particles, float timestep);

void update_gravity(std::vector<Particle>& particles);

void update_collisions(std::vector<Particle>& particles);
#endif
