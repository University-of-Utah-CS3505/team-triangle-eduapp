#ifndef MAIN_MENU_H
#define MAIN_MENU_H

#include "game_state.h"
#include <Box2D/Dynamics/b2Fixture.h>
#include <SFML/Graphics.hpp>
#include <functional>
#include <memory>
#include <Box2D/Dynamics/b2Fixture.h>
#include <Box2D/Box2D.h>

class main_menu : public game_state {
public:
    main_menu(sf::RenderWindow& window);
    ~main_menu() override;

    void update(std::unique_ptr<game_state>&) override;

private:
    struct menu_item {
        sf::Texture texture;
        sf::Sprite sprite;
        b2Body *body;
        std::function<bool()> on_press;
    };

    std::vector<menu_item> _items;
    sf::RenderWindow& _window;
    b2World _world;
};

#endif // MAIN_MENU_H
