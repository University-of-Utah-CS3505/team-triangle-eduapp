#ifndef TILE_H
#define TILE_H

#include <SFML/Graphics.hpp>
#include <string>

class tile
{
public:
    tile(int index, std::string img, std::string _type);
    int get_index();
    std::string get_img();
    std::string get_type();
    sf::Sprite get_sprite();
    void set_sprite_position(int x, int y);

private:
    int _index;
    std::string _img;
    std::string _type;
    sf::Texture _texture;
    sf::Sprite _sprite;
};

#endif // TILE_H
