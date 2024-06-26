#ifndef QUADTREE_H
#define QUADTREE_H

#include "node.h"

class QuadTree {
public:
    Node* root;
    double theta;

    QuadTree(double x, double y, double width, double theta)
        : theta(theta)
    {
        root = new Node(x, y, width);
    }

    ~QuadTree() {
        delete root;
    }

    void insert(Particle p) {
        root->insert(p);
    }

    void calculate_forces(Particle& p, double& all_force)
    {
        root->calculate_force(p, theta, all_force);
    }

    void draw(sf::RenderWindow& window)
    {
        root->draw(window);
    }
};

#endif