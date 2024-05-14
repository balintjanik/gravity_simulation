#ifndef SETTINGS_H
#define SETTINGS_H

// width and height of screen
const int width = 1200;
const int height = 800;

// timestep (speed of animation)
const float timestep = 0.001f;

// number of particles
const int n = 200;

// radius of particles
const int radius = 6;

// max force to expect per particle (for coloring purposes only)
const float max_forces = 0.1f;

// bounce back from edges of screen
const bool has_borders = true;

#endif
