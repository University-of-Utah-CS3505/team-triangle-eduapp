#include "level_menu.h"

const auto deg_radian_conv_factor = 0.017453292519943295769236907;

const auto scale = 100.0;

level_menu::level_menu(sf::RenderWindow& window)
    :_window(window), _world(b2Vec2(0.f, -1.f))
{

}

level_menu::~level_menu(){}

void level_menu::update(std::unique_ptr<game_state>&){
    _window.clear(sf::Color::Cyan);
    _world.Step(1/60.0f,1,1);
    for(auto& item:_items){}
    _window.display();
}
