#ifndef DBLVECTOR_OP
#define DBLVECTOR_OP

#include <SFML/Graphics.hpp>

sf::Vector2f operator*(const sf::Vector2f& vector, double scalar);

sf::Vector2f operator*(double scalar, const sf::Vector2f& vector);

sf::Vector2f& operator*=(sf::Vector2f& vector, double scalar);

sf::Vector2f operator/(const sf::Vector2f& vector, double scalar);

sf::Vector2f operator/(double scalar, const sf::Vector2f& vector);

sf::Vector2f& operator/=(sf::Vector2f& vector, double scalar);

sf::Vector2f operator+(const sf::Vector2f& vector, double scalar);

sf::Vector2f operator+(double scalar, const sf::Vector2f& vector);

sf::Vector2f& operator+=(sf::Vector2f& vector, double scalar);

sf::Vector2f operator-(const sf::Vector2f& vector, double scalar);

sf::Vector2f operator-(double scalar, const sf::Vector2f& vector);

sf::Vector2f& operator-=(sf::Vector2f& vector, double scalar);

#endif
