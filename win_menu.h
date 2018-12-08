#ifndef WIN_MENU_H
#define WIN_MENU_H

#include "engine.h"
#include "game_state.h"
#include <SFML/Graphics.hpp>
#include <functional>
#include <memory>

class win_menu : public game_state {
public:
    win_menu(engine&);
    ~win_menu() override;
    std::unique_ptr<game_state> update() override;

private:
    bool _handle_click(sf::Event);

    struct menu_item {
        menu_item(const std::string& tex_path,
                  std::function<void()> on_press);
        std::unique_ptr<sf::Texture> texture;
        sf::Sprite sprite;
        std::function<void()> on_press;
    };

    sf::Sprite you_win;
    sf::Texture you_win_t;
    std::vector<menu_item> _items;
    engine& _engine;
    std::unique_ptr<game_state> _to_state;
    event_handle _click_handle;
};

#endif // WIN_MENU_H
