#ifndef RGR2_APPLICATION_H
#define RGR2_APPLICATION_H

#include <SFML/Graphics.hpp>
#include "Polygon/Polygon.h"

class Application {
public:
    Application(sf::VideoMode size, std::string title, unsigned int framerateLimit);

    void run();

private:
    sf::RenderWindow window;
    sf::Clock watch;
    sf::Event event;
    sf::VideoMode screenSize;
    std::string title;
    sf::Font font;
    sf::Text spaceLabel, rightClickLabel, leftClickLabel, escapeLabel;
    bool running;
    Polygon polygon;


    void dispatchEvents();

    void draw();

};

#endif
