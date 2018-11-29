#ifndef TANK_H
#define TANK_H

#include <SFML/Graphics.hpp>
#include <string>

class tank
{
public:
    tank(std::string img);

    bool rotate(char dir);
    bool move_forward();
    bool shoot();
    void set_position(int x, int y);
    int get_x();
    int get_y();
    sf::Sprite get_sprite();

private:
    int _x;
    int _y;
    sf::Sprite _sprite;
    sf::Texture _texture;
    int _current_move_pos;

};

#endif // TANK_H
