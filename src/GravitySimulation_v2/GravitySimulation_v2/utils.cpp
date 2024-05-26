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
                vx = generate_random_double(-1.0, 1.0);
                vy = generate_random_double(-1.0, 1.0);
                break;
            case SpeedType::Angular:
                ang_to_cent = atan2(y - HEIGHT / 2, x - CANVAS_WIDTH / 2);
                angle = ang_to_cent + 90;
                distance = v2f_distance(sf::Vector2f(x, y), sf::Vector2f(CANVAS_WIDTH / 2, HEIGHT / 2));
                speed = map_value(distance, 0.0, settings.R, 0.0, settings.MASS*8.0);
                rand_x = generate_random_double(0.7, 2.0);
                rand_y = generate_random_double(0.7, 2.0);
                vx = speed * cos(angle) * rand_x;
                vy = speed * sin(angle) * rand_y;
                break;
            case SpeedType::Central:
                direction = sf::Vector2f(CANVAS_WIDTH / 2 - x, HEIGHT / 2 - y);
                vx = direction.x / 10;
                vy = direction.y / 10;
                break;
            default: // Zero is default
                vx = 0.0;
                vy = 0.0;
                break;
        }
        sf::Vector2f initialVelocity(vx, vy);

        // set color
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