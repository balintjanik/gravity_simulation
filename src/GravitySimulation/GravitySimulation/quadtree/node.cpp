#include "node.h"

void Node::insert(Particle p)
{
	// Check if particle is within node's bounds
	if (!is_particle_within_bounds(p))
	{
		return;
	}

	if (is_leaf)
	{
		if (particle == nullptr)
		{
			particle = new Particle(p);
			mass = p.mass;
			com_x = p.position.x;
			com_y = p.position.y;
		}
		else
		{
			is_leaf = false;
			Particle old_particle = *particle;
			delete particle;
			particle = nullptr;

			int quadrant = get_quadrant(old_particle);
			if (children[quadrant] == nullptr)
			{
				children[quadrant] = get_new_region(x, y, width, quadrant);
			}
			children[quadrant]->insert(old_particle);
			insert(p);
		}
	}
	else
	{
		int quadrant = get_quadrant(p);
		if (children[quadrant] == nullptr)
		{
			children[quadrant] = get_new_region(x, y, width, quadrant);
		}
		children[quadrant]->insert(p);
	}
	update_mass_and_com(p);
}

bool Node::is_particle_within_bounds(const Particle& p) const {
	return (p.position.x >= x - width / 2.0 && p.position.x <= x + width / 2.0 &&
		p.position.y >= y - width / 2.0 && p.position.y <= y + width / 2.0);
}

unsigned int Node::calculate_force(Particle& p, double theta, double& all_force)
{
	int calculation_count = 0;

	if (is_leaf)
	{
		if (particle != nullptr && (particle->id != p.id))
		{
			calculation_count++;

			// Calculate distance and angle
			double angle = atan2(p.position.y - com_y, p.position.x - com_x);
			double distance = v2f_distance(p.position, sf::Vector2f(com_x, com_y));

			// Calculate gravitational force
			double g = 1;
			double force = (g * mass) / (pow(distance, 2) + pow(EPSYLON, 2));

			// Update velocity
			p.velocity.x -= force * cos(angle) * settings.TIMESTEP;
			p.velocity.y -= force * sin(angle) * settings.TIMESTEP;
			all_force += force;
		}
	}
	else
	{
		// Calculate distance and angle
		double angle = atan2(p.position.y - com_y, p.position.x - com_x);
		double distance = v2f_distance(p.position, sf::Vector2f(com_x, com_y));

		if (width / distance < theta) {
			calculation_count++;

			// Calculate gravitational force
			double g = 1;
			double force = (g * mass) / (pow(distance, 2) + pow(EPSYLON, 2));

			// Update velocity
			p.velocity.x -= force * cos(angle) * settings.TIMESTEP;
			p.velocity.y -= force * sin(angle) * settings.TIMESTEP;
			all_force += force;
		}
		else {
			for (auto& child : children) {
				if (child != nullptr) {
					calculation_count += child->calculate_force(p, theta, all_force);
				}
			}
		}
	}

	return calculation_count;
}

void Node::draw(sf::RenderWindow& window)
{
	sf::RectangleShape cell(sf::Vector2f(width, width));
	cell.setPosition(x - width / 2.0 + map_offset.x, y - width / 2.0 + map_offset.y);
	cell.setFillColor(sf::Color::Transparent);
	cell.setOutlineThickness(1);
	cell.setOutlineColor(sf::Color(20, 20, 20));
	window.draw(cell);

	for (int i = 0; i < 4; ++i) {
		if (children[i] != nullptr) {
			children[i]->draw(window);
		}
	}
}

unsigned int Node::get_depth()
{
	unsigned int max_depth = 0;

	for (int i = 0; i < 4; ++i) {
		if (children[i] == nullptr)
			continue;

		max_depth = std::max(max_depth, children[i]->get_depth());
	}

	return max_depth + 1;
}

unsigned int Node::get_node_count()
{
	unsigned int nodes = 1;

	for (int i = 0; i < 4; ++i) {
		if (children[i] == nullptr)
			continue;

		nodes += children[i]->get_node_count();
	}

	return nodes;
}

unsigned int Node::get_leaf_count()
{
	unsigned int leaves = 0;

	if (is_leaf)
		leaves = 1;
	else
	{
		for (int i = 0; i < 4; ++i) {
			if (children[i] == nullptr)
				continue;

			leaves += children[i]->get_leaf_count();
		}
	}

	return leaves;
}

int Node::get_quadrant(const Particle& p) {
	if (p.position.x < x && p.position.y < y) return 0;
	if (p.position.x >= x && p.position.y < y) return 1;
	if (p.position.x < x && p.position.y >= y) return 2;
	return 3;
}

Node* Node::get_new_region(double x, double y, double width, int quadrant) {
	double half_width = width / 2.0;
	if (quadrant == 0) return new Node(x - half_width / 2.0, y - half_width / 2.0, half_width);
	if (quadrant == 1) return new Node(x + half_width / 2.0, y - half_width / 2.0, half_width);
	if (quadrant == 2) return new Node(x - half_width / 2.0, y + half_width / 2.0, half_width);
	return new Node(x + half_width / 2.0, y + half_width / 2.0, half_width);
}

void Node::update_mass_and_com(const Particle& p) {
	double total_mass = mass + p.mass;
	com_x = (com_x * mass + p.position.x * p.mass) / total_mass;
	com_y = (com_y * mass + p.position.y * p.mass) / total_mass;
	mass = total_mass;
}