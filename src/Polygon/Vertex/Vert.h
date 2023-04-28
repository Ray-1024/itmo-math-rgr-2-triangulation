#ifndef RGR2_VERT_H
#define RGR2_VERT_H


#include <SFML/Graphics.hpp>

class Vert {
public:
	sf::Vertex pos;
	float angle;
	Vert* realNext = nullptr, * realPrev = nullptr, * algNext = nullptr, * algPrev = nullptr;
};


#endif //RGR2_VERT_H
