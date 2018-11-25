#ifndef MAIN_MENU_H
#define MAIN_MENU_H

#include "game_state.h"
#include <SFML/Graphics.hpp>
#include <memory>

class main_menu : public game_state {
public:
    main_menu(sf::RenderWindow& window);
    ~main_menu() override;

    void update(std::unique_ptr<game_state>&) override;

private:
    sf::RenderWindow& _window;
};

#endif // MAIN_MENU_H
