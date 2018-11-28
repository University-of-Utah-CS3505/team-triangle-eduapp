#include "main_menu.h"

#include <SFML/Graphics.hpp>
#include <game_state.h>
#include <memory>
#include <QDebug>
#include <iostream>


const auto deg_radian_conv_factor = 0.017453292519943295769236907;

const auto scale = -100.0;

main_menu::main_menu(sf::RenderWindow& window)
    : _window(window), _world(b2Vec2(0.f, -1.f)) {

    auto& play_button = _items.emplace_back();
    play_button.texture.loadFromFile("../team-triangle-eduapp/assets/play_button.png");
    play_button.sprite.setTexture(play_button.texture);
    auto play_button_def = b2BodyDef();
    auto play_button_shape = b2PolygonShape();
    auto play_button_fix_def = b2FixtureDef();
    play_button_def.type = b2_dynamicBody;
    auto s = play_button.texture.getSize();
    play_button_shape.SetAsBox(s.x / scale, s.y / scale);
    play_button_fix_def.shape = &play_button_shape;
    play_button_def.position.Set(0.f, 0.f);
    play_button.body = _world.CreateBody(&play_button_def);
    play_button.body->CreateFixture(&play_button_fix_def);

    auto& level_button = _items.emplace_back();
    level_button.texture.loadFromFile("../team-triangle-eduapp/assets/levels_button.png");
    level_button.sprite.setTexture(level_button.texture);
    auto level_button_def = b2BodyDef();
    auto level_button_shape = b2PolygonShape();
    auto level_button_fix_def = b2FixtureDef();
    level_button_def.type = b2_dynamicBody;
    s = level_button.texture.getSize();
    level_button_shape.SetAsBox(s.x / scale, s.y / scale);
    level_button_fix_def.shape = &level_button_shape;
    level_button_def.position.Set(200.f, 200.f);
    level_button.body = _world.CreateBody(&level_button_def);
    level_button.body->CreateFixture(&level_button_fix_def);

    auto& quit_button = _items.emplace_back();
    quit_button.texture.loadFromFile("../team-triangle-eduapp/assets/quit_button.png");
    quit_button.sprite.setTexture(quit_button.texture);
    auto quit_button_def = b2BodyDef();
    auto quit_button_shape = b2PolygonShape();
    auto quit_button_fix_def = b2FixtureDef();
    quit_button_def.type = b2_dynamicBody;
    s = quit_button.texture.getSize();
    quit_button_shape.SetAsBox(s.x / scale, s.y / scale);
    quit_button_fix_def.shape = &quit_button_shape;
    quit_button_def.position.Set(400.f, 400.f);
    quit_button.body = _world.CreateBody(&quit_button_def);
    quit_button.body->CreateFixture(&quit_button_fix_def);

    auto size = _window.getSize();
    _items[0].sprite.setPosition(size.x/2-200, (size.y / 2) - 290);
    _items[1].sprite.setPosition(size.x/2-200, (size.y / 2) - 70);
    _items[2].sprite.setPosition(size.x/2-200, (size.y / 2) + 150);
}

main_menu::~main_menu() {}

void main_menu::update(std::unique_ptr<game_state>&) {
    _window.clear(sf::Color::Cyan);
    _world.Step(1 / 60.0f, 1, 1);
    for (auto& item : _items) {
//        auto pos = item.body->GetPosition();
//        item.sprite.setPosition(pos.x * scale, pos.y * scale);
//        item.sprite.setRotation(item.body->GetAngle() * deg_radian_conv_factor);
        _window.draw(item.sprite);
//        std::cout << item.sprite.getPosition().x << item.sprite.getPosition().y << std::endl;
    }
    _window.display();
}
