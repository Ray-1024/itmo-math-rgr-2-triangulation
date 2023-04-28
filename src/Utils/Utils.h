#ifndef RGR2_UTILS_H
#define RGR2_UTILS_H

#include "SFML/Graphics.hpp"
#include <cmath>

float dot(const sf::Vector2f& a, const sf::Vector2f& b, const sf::Vector2f& c, const sf::Vector2f& d) {
	return (b.x - a.x) * (d.x - c.x) + (b.y - a.y) * (d.y - c.y);
}

float cross(const sf::Vector2f& a, const sf::Vector2f& b, const sf::Vector2f& c, const sf::Vector2f& d) {
	return (b.x - a.x) * (d.y - c.y) - (b.y - a.y) * (d.x - c.x);
}

float distance(const sf::Vector2f& a, const sf::Vector2f& b) {
	return std::sqrt((b.x - a.x) * (b.x - a.x) + (b.y - a.y) * (b.y - a.y));
}

bool intersects(const sf::Vector2f& a, const sf::Vector2f& b, const sf::Vector2f& c, const sf::Vector2f& d) {
	return (cross(a, b, a, c) * cross(a, b, a, d) < 0) && (cross(c, d, c, a) * cross(c, d, c, b) < 0);
}

int sign(float a) {
	return (a > 0) ? ((std::abs(a) < 1e-6f) ? 0 : 1) : -1;
}

float getAngle(const sf::Vector2f& a, const sf::Vector2f& b, const sf::Vector2f& c) {
	float ang = std::acos(dot(b, a, b, c) / (distance(a, b) * distance(b, c))) * sign(cross(a, b, b, c));
	return (ang < 0) ? ang + M_PI + M_PI : ang;
}

bool inTriangle(const sf::Vector2f& v, const sf::Vector2f& a, const sf::Vector2f& b, const sf::Vector2f& c) {
	int aa = sign(cross(a, b, a, v)), bb = sign(cross(b, c, b, v)), cc = sign(cross(c, a, c, v));
	return aa == bb && bb == cc;
}

#endif
