#ifndef NODE_H
#define NODE_H

#include "../physics/particle.h"
#include "../utils/utils.h"

class Node {
public:
    double x, y; // Center of the region represented by this node
    double width; // Width of the region
    double mass;  // Total mass of particles in this node
    double com_x, com_y; // Center of mass
    bool is_leaf;
    Particle* particle;
    Node* children[4];

    Node(double x, double y, double width)
        : x(x), y(y), width(width), mass(0), com_x(0), com_y(0), is_leaf(true), particle(nullptr) {
        for(int i = 0; i < 4; i++) {
            children[i] = nullptr;
        };
    }

    ~Node() {
        delete particle;
        particle = nullptr;
        for (int i = 0; i < 4; ++i) {
            delete children[i];
            children[i] = nullptr;
        }
    }

    void insert(Particle p);
    void calculate_force(Particle& p, double theta, double& force_x); // double& force_x, double& force_y);
    void draw(sf::RenderWindow& window);
    
private:
    bool is_particle_within_bounds(const Particle& p) const;
    int get_quadrant(const Particle& p);
    Node* get_new_region(double x, double y, double width, int quadrant);
    void update_mass_and_com(const Particle& p);
};

#endif