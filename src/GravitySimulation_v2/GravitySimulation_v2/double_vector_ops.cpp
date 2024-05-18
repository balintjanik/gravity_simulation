#include "double_vector_ops.h"

sf::Vector2f operator*(const sf::Vector2f& vector, double scalar) {
    return sf::Vector2f(vector.x * static_cast<float>(scalar), vector.y * static_cast<float>(scalar));
}

sf::Vector2f operator*(double scalar, const sf::Vector2f& vector) {
    return vector * scalar;
}

sf::Vector2f& operator*=(sf::Vector2f& vector, double scalar) {
    vector.x *= static_cast<double>(scalar);
    vector.y *= static_cast<double>(scalar);
    return vector;
}