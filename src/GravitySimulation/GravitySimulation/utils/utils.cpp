#include "utils.h"
#include "../grid/grid.h"
#include "../quadtree/quadtree.h"

using namespace std;

sf::Color hsv_to_rgb(double H, double S, double V)
{
    int Hi = int(H * 6) % 6;
    double f = H * 6 - Hi;
    double p = V * (1 - S);
    double q = V * (1 - f * S);
    double t = V * (1 - (1 - f) * S);

    switch (Hi)
    {
        case 0: return sf::Color(V * 255, t * 255, p * 255);
        case 1: return sf::Color(q * 255, V * 255, p * 255);
        case 2: return sf::Color(p * 255, V * 255, t * 255);
        case 3: return sf::Color(p * 255, q * 255, V * 255);
        case 4: return sf::Color(t * 255, p * 255, V * 255);
        case 5: return sf::Color(V * 255, p * 255, q * 255);
        default: return sf::Color::White;
    }
}

sf::Color map_forces_to_color(double all_forces)
{
    double normalized_forces = min(all_forces / settings.MAX_FORCES, 1.0);
    double hue = (1.0 - normalized_forces) * 0.65;
    double saturation = 1.0;
    double value = 1.0;

    return hsv_to_rgb(hue, saturation, value);
}

double generate_random_double(double min_value, double max_value)
{
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<double> dist(min_value, max_value);

    return dist(gen);
}

double v2f_distance(sf::Vector2f v1, sf::Vector2f v2)
{
    double dx = v2.x - v1.x;
    double dy = v2.y - v1.y;
    return sqrt(dx * dx + dy * dy);
}

double map_value(double value, double min_input, double max_input, double min_output, double max_output) {
    value = max(min_input, min(max_input, value));
    return min_output + (max_output - min_output) * (value - min_input) / (max_input - min_input);
}

vector<Particle> generate_particles(double min_x, double max_x, double min_y, double max_y)
{
    vector<Particle> particles;

    // Starting variables
    double x, y;
    double vx, vy;
    double r, theta;
    double ang_to_cent, angle, distance, speed, rand_x, rand_y;
    sf::Vector2f direction;

    sf::Vector2f center = sf::Vector2f(WIDTH / 2, HEIGHT / 2);

    // Singularity variables
    sf::Vector2f sin_pos = sf::Vector2f(WIDTH / 2, HEIGHT / 2);
    sf::Vector2f sin_vel = sf::Vector2f(0, 0);

    for (int i = 0; i < settings.N; i++)
    {
        // Add singularity
        if (settings.SPEED_TYPE == SpeedType::Galaxy && i == 0)
        {
            particles.push_back(Particle(sin_pos, sin_vel, SINGULARITY_COLOR, SINGULARITY_RADIUS, settings.SINGULARITY_MASS, true));
            center = sin_pos;
            id_counter++;
            continue;
        }

        // Set random position
        switch (settings.PLACEMENT_TYPE)
        {
            case PlacementType::Circular:
                r = settings.R * sqrt(generate_random_double(0, 1));
                theta = generate_random_double(0, 1) * 2 * PI;
                x = center.x + r * cos(theta);
                y = center.y + r * sin(theta);
                break;
            default: // FullScreen is default
                x = generate_random_double(min_x, max_x);
                y = generate_random_double(min_y, max_y);
                break;
        }
        sf::Vector2f initial_position(x, y);

        // Set velocity
        switch (settings.SPEED_TYPE)
        {
            case SpeedType::Random:
                vx = generate_random_double(-15.0, 15.0);
                vy = generate_random_double(-15.0, 15.0);
                break;
            case SpeedType::Angular:
                ang_to_cent = atan2(y - HEIGHT / 2, x - WIDTH / 2);
                angle = ang_to_cent + 90;
                distance = v2f_distance(sf::Vector2f(x, y), sf::Vector2f(WIDTH / 2, HEIGHT / 2));
                speed = map_value(distance, 0.0, settings.R, 0.0, settings.MASS*2.0);
                rand_x = generate_random_double(0.7, 1.4);
                rand_y = generate_random_double(0.7, 1.4);
                vx = speed * cos(angle) * rand_x;
                vy = speed * sin(angle) * rand_y;
                break;
            case SpeedType::Galaxy:
                distance = v2f_distance(initial_position, sin_pos);
                speed = sqrt(settings.SINGULARITY_MASS / distance);
                angle = atan2(y - sin_pos.y, x - sin_pos.x) + PI / 2;
                rand_x = 1;
                rand_y = 1;
                vx = sin_vel.x;
                vy = sin_vel.y;
                vx += speed * cos(angle) * rand_x;
                vy += speed * sin(angle) * rand_y;
                break;
            default: // Zero is default
                vx = 0.0;
                vy = 0.0;
                break;
        }
        sf::Vector2f initial_velocity(vx, vy);

        // Set color
        sf::Color particle_color(sf::Color::Blue);

        particles.push_back(Particle(initial_position, initial_velocity, particle_color, settings.RADIUS, settings.MASS));
        id_counter++;
    }

    return particles;
}

void add_singularity(Grid& collision_grid)
{
    Particle singularity = Particle(sf::Vector2f(sf::Mouse::getPosition().x, sf::Mouse::getPosition().y), sf::Vector2f(0, 0), SINGULARITY_COLOR, SINGULARITY_RADIUS, settings.SINGULARITY_MASS, true);
    particles.push_back(singularity);
    collision_grid.add_particle(particles.back());
    
    id_counter++;
}

void init_optim_grid(Grid& grid)
{
    for (auto& p : particles)
    {
        grid.add_particle(p);
    }
}

int get_idx_by_id(int id)
{
    int i = 0;
    while (i < particles.size() && particles[i].id != id)
    {
        i++;
    }
    if (i < particles.size())
    {
        return i;
    }
    return -1;
}

void handle_move(sf::Vector2f start_position, sf::Vector2f end_position)
{
    delta_move = end_position - start_position;
    map_offset += delta_move / zoom;

    float visible_width = WIDTH / zoom;
    float visible_height = HEIGHT / zoom;

    if (map_offset.x < -(final_limit.x - visible_width / 2))
        map_offset.x = -(final_limit.x - visible_width / 2);
    else if (map_offset.x > final_limit.x - visible_width / 2)
        map_offset.x = final_limit.x - visible_width / 2;

    if (map_offset.y < -(final_limit.y - visible_height / 2))
        map_offset.y = -(final_limit.y - visible_height / 2);
    else if (map_offset.y > final_limit.y - visible_height / 2)
        map_offset.y = final_limit.y - visible_height / 2;
}

void draw_particles(sf::RenderWindow& window, Grid& collision_grid)
{
    // Draw trails first to avoid trails covering particles
    if (settings.HAS_TRAIL)
    {
        for (auto& p : particles)
        {
            sf::Color current_trail_color = settings.TRAIL_COLOR;
            for (int i = 0; i < p.trail.size(); i++)
            {
                sf::CircleShape circle(zoom * settings.TRAIL_RADIUS);
                current_trail_color.a = ((255 * i) / settings.TRAIL_SIZE);
                circle.setFillColor(current_trail_color);
                circle.setPosition(zoom * (p.trail[i].x - settings.TRAIL_RADIUS + map_offset.x - WIDTH / 2) + WIDTH / 2, zoom * (p.trail[i].y - settings.TRAIL_RADIUS + map_offset.y - HEIGHT / 2) + HEIGHT / 2);
                window.draw(circle);
            }
        }
    }

    // Draw particles
    // If not set otherwise, draw them the most effective way
    if (!(settings.VISUALIZE_COLLISION_GRID || settings.VISUALIZE_COLLISION_PARTICLE_CELL))
    {
        for (auto& p : particles)
        {
            sf::CircleShape circle(zoom * (p.radius - (p.is_singularity ? SINGULARITY_OUTLINE_THICKNESS : 0)));
            circle.setFillColor(p.color);

            if (p.is_singularity)
            {
                circle.setFillColor(sf::Color::Black);
                circle.setOutlineThickness(zoom * SINGULARITY_OUTLINE_THICKNESS);
                circle.setOutlineColor(p.color);
            }

            // setPosition sets the coordinates of top left corner
            circle.setPosition(zoom * (p.position.x - p.radius + map_offset.x - WIDTH / 2) + WIDTH / 2, zoom * (p.position.y - p.radius + map_offset.y - HEIGHT / 2) + HEIGHT / 2);

            window.draw(circle);
        }
    }
    // If set, draw grid and color particles accordingly
    else
    {
        // Draw grid
        if (settings.VISUALIZE_COLLISION_GRID)
        {
            for (int x = 0; x < collision_grid.width; x++)
            {
                for (int y = 0; y < collision_grid.height; y++)
                {
                    sf::Vector2f c_size(settings.COLLISION_CELL_SIZE, settings.COLLISION_CELL_SIZE);
                    sf::RectangleShape cell(zoom * c_size);

                    sf::Color fill_col = sf::Color::Transparent;
                    if (settings.VISUALIZE_COLLISION_CELL_MASS)
                    {
                        fill_col = map_forces_to_color(collision_grid.get(x, y).total_mass / settings.COLLISION_CELL_SIZE);
                        fill_col.a = 140;
                    }
                    cell.setFillColor(fill_col);

                    cell.setOutlineColor(sf::Color(20, 20, 20));
                    cell.setOutlineThickness(zoom * 0.5f);
                    cell.setPosition(zoom * (x * settings.COLLISION_CELL_SIZE - collision_grid.overflow_x / 2 + map_offset.x - WIDTH / 2) + WIDTH / 2, zoom * (y * settings.COLLISION_CELL_SIZE - collision_grid.overflow_y / 2 + map_offset.y - HEIGHT / 2) + HEIGHT / 2);
                    window.draw(cell);
                }
            }
        }

        // Draw particles of cells
        int idx;
        for (int x = 0; x < collision_grid.width; x++)
        {
            for (int y = 0; y < collision_grid.height; y++)
            {
                // Calculate color based on grid position
                sf::Color col = sf::Color::Green;
                if ((y % 2 == 0 && x % 2 == 1) || (y % 2 == 1 && x % 2 == 0))
                    col = sf::Color::Magenta;

                auto& current_cell = collision_grid.get(x, y);
                for (auto it1 = current_cell.particle_indices.begin(); it1 != current_cell.particle_indices.end(); ++it1)
                {
                    idx = get_idx_by_id(*it1);
                    if (idx < 0)
                        continue;

                    Particle& p = particles[idx];

                    sf::CircleShape circle(zoom * (p.radius - (p.is_singularity ? SINGULARITY_OUTLINE_THICKNESS : 0)));

                    // Set color based on custom settings
                    if (settings.VISUALIZE_COLLISION_PARTICLE_CELL)
                    {
                        circle.setFillColor(col);
                        if (p.is_singularity)
                        {
                            circle.setFillColor(sf::Color::Black);
                            circle.setOutlineThickness(zoom * 3);
                            circle.setOutlineColor(col);
                        }
                    }
                    else
                    {
                        circle.setFillColor(p.color);
                        if (p.is_singularity)
                        {
                            circle.setFillColor(sf::Color::Black);
                            circle.setOutlineThickness(zoom * SINGULARITY_OUTLINE_THICKNESS);
                            circle.setOutlineColor(p.color);
                        }
                    }

                    circle.setPosition(zoom * (p.position.x - p.radius + map_offset.x - WIDTH / 2) + WIDTH / 2, zoom * (p.position.y - p.radius + map_offset.y - HEIGHT / 2) + HEIGHT / 2);
                    window.draw(circle);
                }

                // draw center of mass
                if (settings.VISUALIZE_COLLISION_COM)
                {
                    sf::CircleShape com(zoom * 5, 3);
                    com.setFillColor(sf::Color::Red);
                    sf::Vector2f com_pos = collision_grid.get(x, y).center_of_mass;
                    if (com_pos.x == 0 && com_pos.y == 0)
                    {
                        int to_center = settings.COLLISION_CELL_SIZE / 2;
                        int correct_overflow_x = collision_grid.overflow_x / 2;
                        int correct_overflow_y = collision_grid.overflow_y / 2;
                        com.setPosition(zoom * (x * settings.COLLISION_CELL_SIZE + to_center - 5 - correct_overflow_x + map_offset.x - WIDTH / 2) + WIDTH / 2, zoom * (y * settings.COLLISION_CELL_SIZE + to_center - 5 - correct_overflow_y + map_offset.y - HEIGHT / 2) + HEIGHT / 2);
                    }
                    else
                    {
                        com.setPosition(zoom * (com_pos.x - 5 + map_offset.x - WIDTH / 2) + WIDTH / 2, zoom * (com_pos.y - 5 + map_offset.y - HEIGHT / 2) + HEIGHT / 2);
                    }
                    window.draw(com);
                }
            }
        }
    }
}

void draw_borders(sf::RenderWindow& window)
{
    // Draw quadtree border (final limit)
    int final_border_width = 8;
    sf::RectangleShape final_border(zoom * sf::Vector2f(2 * WIDTH - 2 * final_border_width, 2 * WIDTH - 2 * final_border_width));
    final_border.setPosition(zoom * (- WIDTH / 2 + map_offset.x + final_border_width - WIDTH / 2) + WIDTH / 2, zoom * (HEIGHT / 2 - WIDTH + map_offset.y + final_border_width - HEIGHT / 2) + HEIGHT / 2);
    final_border.setFillColor(sf::Color::Transparent);
    final_border.setOutlineThickness(zoom * final_border_width);
    final_border.setOutlineColor(sf::Color::Red);
    window.draw(final_border);

    // Draw grid border
    int grid_border_width = 4;
    sf::RectangleShape grid_border(zoom * sf::Vector2f(WIDTH, HEIGHT));
    grid_border.setPosition(zoom * (0 + map_offset.x - WIDTH / 2) + WIDTH / 2, zoom * (0 + map_offset.y - HEIGHT / 2) + HEIGHT / 2);
    grid_border.setFillColor(sf::Color::Transparent);
    grid_border.setOutlineThickness(zoom * grid_border_width);
    grid_border.setOutlineColor(sf::Color::White);
    window.draw(grid_border);
}

void draw_quadtree(sf::RenderWindow& window, QuadTree& tree)
{
    tree.draw(window);
}