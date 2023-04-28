#include "src/Application.h"

int main() {
    auto *app = new Application(sf::VideoMode::getDesktopMode(), "Triangulation", 60);
    app->run();
    delete app;
    return 0;
}
