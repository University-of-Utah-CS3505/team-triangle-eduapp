#include "main_menu.h"
#include "game_state.h"
#include "gameplay.h"
#include "level_menu.h"
#include "pre_game_options.h"
#include <QDebug>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <memory>

const auto deg_radian_conv_factor = 57.2957795130823208767981548;

auto scale = 100.0;

main_menu::menu_item::menu_item(b2World& world,
                                const std::string& tex_path,
                                std::function<void()> f,
                                float x,
                                float y,
                                float r)
    : on_press(f), texture(std::make_unique<sf::Texture>()) {
    texture->loadFromFile(tex_path);
    sprite.setTexture(*texture);
    sprite.setOrigin(texture->getSize().x / 2, texture->getSize().y / 2);
    auto body_def = b2BodyDef();
    auto shape = b2PolygonShape();
    auto fix_def = b2FixtureDef();
    fix_def.density = 1;
    fix_def.friction = 0.5;
    body_def.type = b2_dynamicBody;
    auto s = texture->getSize();
    shape.SetAsBox(s.x / scale / 2 - shape.m_radius,
                   s.y / scale / 2 - shape.m_radius);
    fix_def.shape = &shape;
    body = world.CreateBody(&body_def);
    body->CreateFixture(&fix_def);
    body->ApplyLinearImpulse(b2Vec2(40, -22), body_def.position, true);
    body->SetTransform(b2Vec2(x, y), r);
}

main_menu::main_menu(engine& eng)
    : _engine(eng), _world(b2Vec2(0.f, 10.f)),
      _click_handle(_engine.add_event_listener(
              sf::Event::MouseButtonPressed,
              [this](auto e) { return _handle_click(e); })) {
    // TODO this is a bad global
    if (_engine.window().getSize().x <= 1280) {
        scale = 82.0;
    }

    _items.emplace_back(
            _world,
            "../team-triangle-eduapp/assets/play_button.png",
            [this]() { _to_state = std::make_unique<gameplay>(_engine,0); },
            -2,
            2,
            0.5);

    _items.emplace_back(
            _world,
            "../team-triangle-eduapp/assets/levels_button.png",
            [this]() { _to_state = std::make_unique<level_menu>(_engine); },
            -4,
            5,
            1);

    _items.emplace_back(_world,
                        "../team-triangle-eduapp/assets/quit_button.png",
                        [this]() { _engine.window().close(); },
                        -2,
                        8,
                        5.15);

    auto floor_def = b2BodyDef();
    auto floor_shape = b2PolygonShape();
    auto floor_fix_def = b2FixtureDef();
    floor_shape.SetAsBox(_engine.window().getSize().x / scale, 0);
    floor_fix_def.shape = &floor_shape;
    floor_fix_def.friction = 0.7;
    floor_def.position.Set(0, _engine.window().getSize().y / scale - 0.5);
    _world.CreateBody(&floor_def)->CreateFixture(&floor_fix_def);
    std::cout<< _engine.window().getSize().y;
    auto wall_def = b2BodyDef();
    auto wall_shape = b2PolygonShape();
    auto wall_fix_def = b2FixtureDef();
    wall_shape.SetAsBox(_engine.window().getSize().x / scale, 0);
    wall_fix_def.shape = &wall_shape;
    wall_fix_def.friction = 0.5;
    wall_def.position.Set(_engine.window().getSize().x / scale - 0.5, 0);
    _world.CreateBody(&wall_def)->CreateFixture(&wall_fix_def);



   logo_tex.loadFromFile("../team-triangle-eduapp/assets/snaketanks.png");
   logo.setTexture(logo_tex);
   logo.setOrigin(logo.getTexture()->getSize().x/2,0);
   logo.setPosition(_engine.window().getSize().x/2, 20.0);

}

main_menu::~main_menu() {}

std::unique_ptr<game_state> main_menu::update() {
    _engine.window().clear(sf::Color::Cyan);
    _world.Step(1 / 60.0f, 1, 1);
    for (auto& item : _items) {
        auto pos = item.body->GetPosition();
        item.sprite.setPosition(pos.x * scale, pos.y * scale);
        item.sprite.setRotation(item.body->GetAngle() * deg_radian_conv_factor);
        _engine.window().draw(item.sprite);
    }

    _engine.window().draw(logo);
    return std::move(_to_state);
}

bool main_menu::_handle_click(sf::Event e) {
    for (auto& item : _items) {
        if (item.body->GetFixtureList()->TestPoint(
                    b2Vec2(e.mouseButton.x / scale, e.mouseButton.y / scale))) {
            item.on_press();
            return true;
        }
    }
    return false;
}
