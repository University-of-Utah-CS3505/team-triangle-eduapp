#ifndef ENGINE_H
#define ENGINE_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <functional>

class engine {
public:
    engine();

    void add_event_handler(sf::Event::EventType,
                           std::function<bool(sf::Event::EventType)> handler);
    void remove_event_handler(
            sf::Event::EventType,
            std::function<bool(sf::Event::EventType)> handler);

    sf::RenderWindow& window();

private:
    std::vector<std::function<bool(sf::Event::EventType)>> _event_handlers;
    sf::RenderWindow _window;
};

#endif // ENGINE_H
