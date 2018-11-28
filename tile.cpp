#include "tile.h"

tile::tile(int index, std::string img, std::string type) : _index{index}, _img{img}, _type{type}, _sprite(_texture,sf::IntRect(0,0,64,64)){
    _texture.loadFromFile(_img);
    //sf::Sprite _sprite(_texture,sf::IntRect(0,0,64,64));
}

int tile::get_index(){ return _index; }

std::string tile::get_img(){ return _img; }

std::string tile::get_type(){ return _type; }

sf::Sprite tile::get_sprite(){ return _sprite; }

void tile::set_sprite_position(int x, int y)
{
    _sprite.setPosition(x,y);
}
