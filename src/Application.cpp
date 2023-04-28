#include "Application.h"

#include <utility>

Application::Application(sf::VideoMode _size, std::string _title, unsigned int framerateLimit) {
    title = std::move(_title);
    screenSize = _size;
    window.create(screenSize, title, sf::Style::Fullscreen);
    window.setFramerateLimit(framerateLimit);
    watch.restart();
    running = true;
    font.loadFromFile(R"(C:\Windows\Fonts\Arial.ttf)");
    escapeLabel.setFont(font);
    escapeLabel.setString("Escape - Exit");
    escapeLabel.setCharacterSize(window.getSize().y / 60);
    escapeLabel.setPosition(0, 0);
    spaceLabel.setFont(font);
    spaceLabel.setString("Space - Clear");
    spaceLabel.setCharacterSize(window.getSize().y / 60);
    spaceLabel.setPosition(0, window.getSize().y / 30);

}

void Application::run() {
    while (running) {
        dispatchEvents();
        draw();
    }
}

void Application::dispatchEvents() {
    while (window.pollEvent(event)) {
        switch (event.type) {
            case sf::Event::Closed: {
                running = false;
                break;
            }
            case sf::Event::KeyReleased: {
                if (event.key.code == sf::Keyboard::Space)polygon.clear();
                if (event.key.code == sf::Keyboard::Escape)running = false;
                break;
            }
            case sf::Event::MouseButtonReleased: {
                if (event.mouseButton.button == sf::Mouse::Left)
                    polygon.addVertex(event.mouseButton.x, event.mouseButton.y);
                if (event.mouseButton.button == sf::Mouse::Right)
                    polygon.isCircled();
                break;
            }
        }
    }
}

void Application::draw() {
    window.clear();
    window.draw(polygon);
    window.draw(escapeLabel);
    window.draw(spaceLabel);
    window.draw(leftClickLabel);
    window.draw(rightClickLabel);
    window.display();
}
