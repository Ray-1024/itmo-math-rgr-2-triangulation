#ifndef RGR2_POLYGON_H
#define RGR2_POLYGON_H

#include "SFML/Graphics.hpp"

class Polygon : public sf::Drawable {

private:
	sf::VertexArray arr;
	sf::VertexArray lines;
	sf::VertexArray points;

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	bool canAdd(float x, float y);

	void update();

	sf::Vector2f getVert(int ind);

	void addLine(int i, int j);

public:
	Polygon();

	void addVertex(float x, float y);

	void clear();

	void isCircled();
};

#endif //RGR2_POLYGON_H
