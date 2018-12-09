#include "object_def.h"

object_def::object_def(std::string img, std::string type, sf::Vector2i position, sf::Vector2i size)
    : _img{img}, _position(position), _type(type),
      _sprite(_texture,sf::IntRect(0,0,size.x, size.y)), _size(size){
   _texture.loadFromFile(_img);
   _sprite.setOrigin(_size.x/2, _size.y/2);
   _sprite.setPosition((_position.x*64)+32, (_position.y*64)+32);
}

std::string object_def::get_img() { return _img; }

std::string object_def::get_type() { return _type; }

sf::Sprite object_def::get_sprite() { return _sprite; }

sf::Vector2i object_def::get_size(){ return _size; }

sf::Vector2f object_def::get_position() { return _sprite.getPosition(); }

sf::Vector2i object_def::get_location() { return _position; }

void object_def::set_offset(int x, int y) { _sprite.move(x,y); }
