#include "main_menu.h"

#include <SFML/Graphics.hpp>
#include <game_state.h>
#include <memory>

const auto deg_radian_conv_factor = 0.017453292519943295769236907;

const auto scale = 100;

main_menu::main_menu(sf::RenderWindow& window) : _window(window) {}
main_menu::~main_menu() {}

void main_menu::update(std::unique_ptr<game_state>&) {
    _window.clear(sf::Color::Cyan);
    for (auto& item : _items) {
        auto pos = item.body.GetPosition();
        item.sprite.setPosition(pos.x / scale, pos.y / scale);
        item.sprite.setRotation(item.body.GetAngle() * deg_radian_conv_factor);
    }
    _window.display();
}
