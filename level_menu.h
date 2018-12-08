#ifndef LEVEL_MENU_H
#define LEVEL_MENU_H

#include "engine.h"
#include "game_state.h"
#include <Box2D/Box2D.h>
#include <Box2D/Dynamics/b2Fixture.h>
#include <Box2D/Dynamics/b2Fixture.h>
#include <SFML/Graphics.hpp>
#include <functional>
#include <memory>

class level_menu : public game_state {
public:
    level_menu(engine& window);
    ~level_menu() override;
    std::unique_ptr<game_state> update() override;

private:
    struct menu_item {
        menu_item(b2World& world,
                  const std::string& tex_path,
                  std::function<bool()> on_press,
                  int x,
                  int y,
                  int r);

        std::unique_ptr<sf::Texture> texture;
        sf::Sprite sprite;
        b2Body* body;
        std::function<bool()> on_press;
    };

    std::vector<menu_item> _items;
    engine& _engine;
    b2World _world;
    std::unique_ptr<game_state> _to_state;
    event_handle _click_handle;
    bool _handle_click(sf::Event);
    event_handle _esc_menu;

};

#endif // LEVEL_MENU_H
