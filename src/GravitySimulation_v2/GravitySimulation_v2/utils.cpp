#include "utils.h"
#include "grid.h"

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

    double x, y;
    double vx, vy;
    double r, theta;
    double ang_to_cent, angle, distance, speed, rand_x, rand_y;
    sf::Vector2f direction;

    for (int i = 0; i < settings.N; i++)
    {
        // Add singularity
        if (settings.SPEED_TYPE == SpeedType::Galaxy && i == 0)
        {
            particles.push_back(Particle(sf::Vector2f(WIDTH / 2, HEIGHT / 2), sf::Vector2f(0, 0), sf::Color::White, 5, settings.SINGULARITY_MASS, true));
            id_counter++;
            continue;
        }

        // set random position
        switch (settings.PLACEMENT_TYPE)
        {
            case PlacementType::Circular:
                r = settings.R * sqrt(generate_random_double(0, 1));
                theta = generate_random_double(0, 1) * 2 * PI;
                x = CANVAS_WIDTH / 2 + r * cos(theta);
                y = HEIGHT / 2 + r * sin(theta);
                break;
            default: // FullScreen is default
                x = generate_random_double(min_x, max_x);
                y = generate_random_double(min_y, max_y);
                break;
        }
        sf::Vector2f initialPosition(x, y);

        // set velocity
        switch (settings.SPEED_TYPE)
        {
            case SpeedType::Random:
                vx = generate_random_double(-15.0, 15.0);
                vy = generate_random_double(-15.0, 15.0);
                break;
            case SpeedType::Angular:
                ang_to_cent = atan2(y - HEIGHT / 2, x - CANVAS_WIDTH / 2);
                angle = ang_to_cent + 90;
                distance = v2f_distance(sf::Vector2f(x, y), sf::Vector2f(CANVAS_WIDTH / 2, HEIGHT / 2));
                speed = map_value(distance, 0.0, settings.R, 0.0, settings.MASS*8.0);
                rand_x = generate_random_double(0.7, 1.4);
                rand_y = generate_random_double(0.7, 1.4);
                vx = speed * cos(angle) * rand_x;
                vy = speed * sin(angle) * rand_y;
                break;
            case SpeedType::Galaxy:
                distance = v2f_distance(sf::Vector2f(x, y), sf::Vector2f(WIDTH / 2, HEIGHT / 2));
                speed = 3 * sqrt(settings.SINGULARITY_MASS / distance);
                angle = atan2(y - HEIGHT / 2, x - WIDTH / 2) + PI / 2;
                rand_x = generate_random_double(0.9, 1.1);
                rand_y = generate_random_double(0.9, 1.1);
                vx = speed * cos(angle) * rand_x;
                vy = speed * sin(angle) * rand_y;
                break;
            default: // Zero is default
                vx = 0.0;
                vy = 0.0;
                break;
        }
        sf::Vector2f initialVelocity(vx, vy);

        // Set color
        sf::Color particleColor(sf::Color::Blue);

        particles.push_back(Particle(initialPosition, initialVelocity, particleColor, settings.RADIUS, settings.MASS));
        id_counter++;
    }

    return particles;
}

void init_optim_grid(Grid& optim_grid)
{
    for (auto& p : particles)
    {
        optim_grid.add_particle(p);
    }
}

int get_idx_by_id(int id)
{
    int i = 0;
    while (i < settings.N && particles[i].id != id)
    {
        i++;
    }
    if (i < settings.N)
    {
        return i;
    }
    return -1;
}

void draw_particles(sf::RenderWindow& window)
{
    // Draw trails first to avoid trails covering particles
    if (settings.HAS_TRAIL)
    {
        for (auto& p : particles)
        {
            sf::Color current_trail_color = settings.TRAIL_COLOR;
            for (int i = 0; i < p.trail.size(); i++)
            {
                sf::CircleShape circle(settings.TRAIL_RADIUS);
                current_trail_color.a = ((255 * i) / settings.TRAIL_SIZE);
                circle.setFillColor(current_trail_color);
                circle.setPosition(p.trail[i].x - settings.TRAIL_RADIUS, p.trail[i].y - settings.TRAIL_RADIUS);
                window.draw(circle);
            }
        }
    }

    // Draw particles
    // If not set otherwise, draw them the most effective way
    if (!(settings.VISUALIZE_SPATIAL_GRID || settings.VISUALIZE_PARTICLE_CELL))
    {
        for (auto& p : particles)
        {
            sf::CircleShape circle(p.radius);
            circle.setFillColor(p.color);

            // setPosition sets the coordinates of top left corner
            circle.setPosition(p.position.x - p.radius, p.position.y - p.radius);

            window.draw(circle);
        }
    }
    // If set, draw grid and color particles accordingly
    else
    {
        // Draw grid
        if (settings.VISUALIZE_SPATIAL_GRID)
        {
            for (int x = 0; x < optim_grid.width; x++)
            {
                for (int y = 0; y < optim_grid.height; y++)
                {
                    sf::Vector2f c_size(settings.COLLISION_CELL_SIZE, settings.COLLISION_CELL_SIZE);
                    sf::RectangleShape cell(c_size);

                    sf::Color fill_col = sf::Color::Transparent;
                    if (settings.VISUALIZE_CELL_MASS)
                    {
                        fill_col = map_forces_to_color(optim_grid.get(x, y).total_mass / settings.COLLISION_CELL_SIZE);
                        fill_col.a = 140;
                    }
                    cell.setFillColor(fill_col);

                    cell.setOutlineColor(sf::Color(20, 20, 20));
                    cell.setOutlineThickness(0.5f);
                    cell.setPosition(x * settings.COLLISION_CELL_SIZE - optim_grid.overflow_x / 2, y * settings.COLLISION_CELL_SIZE - optim_grid.overflow_y / 2);
                    window.draw(cell);
                }
            }
        }

        // Draw particles of cells
        int idx;
        for (int x = 0; x < optim_grid.width; x++)
        {
            for (int y = 0; y < optim_grid.height; y++)
            {
                // Calculate color based on grid position
                sf::Color col = sf::Color::Green;
                if ((y % 2 == 0 && x % 2 == 1) || (y % 2 == 1 && x % 2 == 0))
                    col = sf::Color::Magenta;

                auto& current_cell = optim_grid.get(x, y);
                for (auto it1 = current_cell.particle_indices.begin(); it1 != current_cell.particle_indices.end(); ++it1)
                {
                    idx = get_idx_by_id(*it1);
                    if (idx < 0)
                        continue;

                    Particle& p = particles[idx];

                    sf::CircleShape circle(p.radius);

                    // Set color based on custom settings
                    if (settings.VISUALIZE_PARTICLE_CELL)
                        circle.setFillColor(col);
                    else
                        circle.setFillColor(p.color);

                    circle.setPosition(p.position.x - p.radius, p.position.y - p.radius);
                    window.draw(circle);
                }

                // draw center of mass
                if (settings.VISUALIZE_COM)
                {
                    sf::CircleShape com(5, 3);
                    com.setFillColor(sf::Color::Red);
                    sf::Vector2f com_pos = optim_grid.get(x, y).center_of_mass;
                    if (com_pos.x == 0 && com_pos.y == 0)
                    {
                        int to_center = settings.COLLISION_CELL_SIZE / 2;
                        int correct_overflow_x = optim_grid.overflow_x / 2;
                        int correct_overflow_y = optim_grid.overflow_y / 2;
                        com.setPosition(x * settings.COLLISION_CELL_SIZE + to_center - 5 - correct_overflow_x, y * settings.COLLISION_CELL_SIZE + to_center - 5 - correct_overflow_y);
                    }
                    else
                    {
                        com.setPosition(com_pos.x - 5, com_pos.y - 5);
                    }
                    window.draw(com);
                }
            }
        }
    }
}