#include "level_menu.h"
#include <QDebug>
#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>
#include <iostream>
#include "gameplay.h"
#include "main_menu.h"

namespace pt = boost::property_tree;

const auto deg_radian_conv_factor = 0.017453292519943295769236907;

const auto scale = 100.0;

level_menu::menu_item::menu_item(b2World& world,
                                 const std::string& tex_path,
                                 std::function<bool()> f,
                                 int x,
                                 int y,
                                 int r)
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
    //body->ApplyLinearImpulse(b2Vec2(50, -10), body_def.position, true);
    body->SetTransform(b2Vec2(x, y), r);
}

level_menu::level_menu(engine& eng) : _engine(eng), _world(b2Vec2(0.f, 10.f)),
    _click_handle(_engine.add_event_listener(
            sf::Event::MouseButtonPressed,
            [this](auto e) { return _handle_click(e); })),
    _esc_menu(_engine.add_event_listener(
                  sf::Event::KeyPressed,
                  [this](auto e){
    if(e.key.code == sf::Keyboard::Escape){
        _to_state = std::make_unique<main_menu>(_engine);
        return true;
    }
})){

   auto root = pt::ptree();
    pt::read_json("../team-triangle-eduapp/levels/levels.json", root);

    int x = 2;
    int level_id = 0;
    for (pt::ptree::value_type& v : root.get_child("levels")) {
        auto preview_path = "../team-triangle-eduapp/levels" + v.second.data() + "preview.png";
        _items.emplace_back(_world,
                            preview_path,
                            [this, level_id]() { _to_state = std::make_unique<gameplay>(_engine, level_id); return true; },
                            x,
                            2,
                            0);
        x+=2;
        level_id++;
    }

    auto floor_def = b2BodyDef();
    auto floor_shape = b2PolygonShape();
    auto floor_fix_def = b2FixtureDef();
    floor_shape.SetAsBox(_engine.window().getSize().x / scale, 0);
    floor_fix_def.shape = &floor_shape;
    floor_fix_def.friction = 0.5;
    floor_def.position.Set(0, _engine.window().getSize().y / scale - 0.5);
    _world.CreateBody(&floor_def)->CreateFixture(&floor_fix_def);

    auto wall_def = b2BodyDef();
    auto wall_shape = b2PolygonShape();
    auto wall_fix_def = b2FixtureDef();
    wall_shape.SetAsBox(_engine.window().getSize().x / scale, 0);
    wall_fix_def.shape = &wall_shape;
    wall_fix_def.friction = 0.5;
    wall_def.position.Set(_engine.window().getSize().x / scale - 0.5, 0);
    _world.CreateBody(&wall_def)->CreateFixture(&wall_fix_def);
}

level_menu::~level_menu() {}

std::unique_ptr<game_state> level_menu::update() {
    _engine.window().clear(sf::Color::Yellow);
    _world.Step(1 / 60.0f, 1, 1);
    for (auto& item : _items) {
        auto pos = item.body->GetPosition();
        item.sprite.setPosition(pos.x * scale, pos.y * scale);
        item.sprite.setRotation(item.body->GetAngle() * deg_radian_conv_factor);
        _engine.window().draw(item.sprite);
    }
    _engine.window().display();
    return std::move(_to_state);
}

bool level_menu::_handle_click(sf::Event e){
    for (auto& item : _items) {
        if (item.body->GetFixtureList()->TestPoint(
                    b2Vec2(e.mouseButton.x / scale, e.mouseButton.y / scale))) {
            item.on_press();
            return true;
        }
    }
    return false;
}
