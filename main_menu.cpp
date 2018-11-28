#include "main_menu.h"

#include <SFML/Graphics.hpp>
#include <game_state.h>
#include <memory>
#include <QDebug>
#include <iostream>


const auto deg_radian_conv_factor = 0.017453292519943295769236907;

const auto scale = 100.0;

main_menu::main_menu(sf::RenderWindow& window)
    : _window(window), _world(b2Vec2(0.f, -1.f)) {

    auto& play_button = _items.emplace_back();
    play_button.texture.loadFromFile("assets/play_button.png");

    auto play_button_def = b2BodyDef();
    auto play_button_shape = b2PolygonShape();
    auto play_button_fix_def = b2FixtureDef();
    play_button_def.type = b2_dynamicBody;
    auto s = play_button.texture.getSize();
    play_button_shape.SetAsBox(s.x / scale, s.y / scale);
    play_button_fix_def.shape = &play_button_shape;
    play_button_def.position.Set(1.f, 1.f);
    play_button.body = _world.CreateBody(&play_button_def);
    play_button.body->CreateFixture(&play_button_fix_def);
}

main_menu::~main_menu() {}

void main_menu::update(std::unique_ptr<game_state>&) {
    _window.clear(sf::Color::Cyan);
    _world.Step(1 / 60.0f, 1, 1);
    for (auto& item : _items) {
        auto pos = item.body->GetPosition();
        item.sprite.setPosition(pos.x * scale, pos.y * scale);
        item.sprite.setRotation(item.body->GetAngle() * deg_radian_conv_factor);
        _window.draw(item.sprite);
        std::cout << item.sprite.getPosition().x << item.sprite.getPosition().y << std::endl;
    }
    _window.display();
}
