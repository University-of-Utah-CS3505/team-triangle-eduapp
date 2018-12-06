#ifndef MAIN_MENU_H
#define MAIN_MENU_H

#include "engine.h"
#include "game_state.h"
#include <Box2D/Box2D.h>
#include <Box2D/Dynamics/b2Fixture.h>
#include <SFML/Graphics.hpp>
#include <functional>
#include <memory>

class main_menu : public game_state {
public:
    main_menu(engine&);
    ~main_menu() override;

    std::unique_ptr<game_state> update() override;

private:
    bool _handle_click(sf::Event);

    struct menu_item {
        menu_item(b2World& world,
                  const std::string& tex_path,
                  std::function<void()> on_press,
                  float x,
                  float y,
                  float r);

        std::unique_ptr<sf::Texture> texture;
        sf::Sprite sprite;
        b2Body* body;
        std::function<void()> on_press;
    };

    std::vector<menu_item> _items;
    engine& _engine;
    b2World _world;
    sf::Sprite logo;
    sf::Texture logo_tex;
    std::unique_ptr<game_state> _to_state;

    event_handle _click_handle;
};

#endif // MAIN_MENU_H
