#include "main_menu.h"

#include <game_state.h>
#include <memory>

main_menu::main_menu(sf::RenderWindow& window) : _window(window) {}
main_menu::~main_menu() {}

void main_menu::update(std::unique_ptr<game_state>&) {
    _window.clear(sf::Color::Cyan);
    _window.display();
}
