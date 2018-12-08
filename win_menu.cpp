#include "win_menu.h"
#include "level_menu.h"
#include "game_state.h"
#include "gameplay.h"
#include <SFML/Graphics.hpp>
#include <functional>
#include <memory>

win_menu::menu_item::menu_item(const std::string& tex_path,
                               std::function<void()> f)
    : on_press(f), texture(std::make_unique<sf::Texture>()) {
    texture->loadFromFile(tex_path);
    sprite.setTexture(*texture);
    sprite.setOrigin(texture->getSize().x / 2, texture->getSize().y / 2);
}

win_menu::win_menu(engine& eng, int level)
    : _engine(eng), _level_won(level),
      _click_handle(_engine.add_event_listener(
                sf::Event::MouseButtonPressed,
                [this](auto e) { return _handle_click(e); })){
    _items.emplace_back(
                "../team-triangle-eduapp/assets/replay_button.png",
                [this]() { _to_state = std::make_unique<gameplay>(_engine, _level_won); });
    _items.emplace_back(
                "../team-triangle-eduapp/assets/next_level_button.png",
                [this]() { _to_state = std::make_unique<gameplay>(_engine, _level_won+1); });
    _items.emplace_back(
                "../team-triangle-eduapp/assets/levels_button.png",
                [this]() { _to_state = std::make_unique<level_menu>(_engine); });

    you_win_t.loadFromFile("../team-triangle-eduapp/assets/you_win.png");
    you_win.setTexture(you_win_t);
    you_win.setOrigin(you_win.getTexture()->getSize().x/2, 0);
//    you_win.setPosition(_engine.window().getSize().x/2, 20.0);
}

win_menu::~win_menu() {}

std::unique_ptr<game_state> win_menu::update() {
    _engine.window().clear(sf::Color::Cyan);

    // Menu items
    auto v_top = _engine.window().getSize().y / 3;
    auto spacing = 0;
    for (auto& item : _items) {
        item.sprite.setPosition(_engine.window().getSize().x / 2, v_top + spacing);
        spacing += 180;
        _engine.window().draw(item.sprite);
    }

    you_win.setPosition((_engine.window().getSize().x / 2), 20.f);
    _engine.window().draw(you_win);

    return std::move(_to_state);
}

bool win_menu::_handle_click(sf::Event e) {
    for (auto& item : _items) {
        auto click_pos = sf::Vector2f{e.mouseButton.x, e.mouseButton.y};
        if (item.sprite.getGlobalBounds().contains(click_pos)) {
            item.on_press();
            return true;
        }
    }
    return false;
}
