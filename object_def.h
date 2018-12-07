#ifndef OBJECT_DEF_H
#define OBJECT_DEF_H

#include <SFML/Graphics.hpp>

class object_def
{
public:
    object_def(std::string img, std::string type, sf::Vector2i position, sf::Vector2i size);
    std::string get_img();
    std::string get_type();
    sf::Sprite get_sprite();
    sf::Vector2i get_size();
    sf::Vector2f get_position();
    void set_sprite_position(int x, int y);
    void set_offset(int x, int y);

private:

    sf::Texture _texture;
    sf::Sprite _sprite;
    std::string _type;
    std::string _img;
    sf::Vector2i _size;
    sf::Vector2i _position;
};

#endif // OBJECT_DEF_H
