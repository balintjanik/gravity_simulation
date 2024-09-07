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

    unsigned int calculate_forces(Particle& p, double& all_force)
    {
        return root->calculate_force(p, theta, all_force);
    }

    void draw(sf::RenderWindow& window)
    {
        root->draw(window);
    }

    unsigned int get_depth()
    {
        return root->get_depth();
    }

    unsigned int get_node_count()
    {
        return root->get_node_count();
    }

    unsigned int get_leaf_count()
    {
        return root->get_leaf_count();
    }
};

#endif