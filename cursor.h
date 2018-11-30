#ifndef CURSOR_H
#define CURSOR_H

#include <SFML/Graphics.hpp>

class cursor : public sf::Drawable {
public:
    cursor(int font_size);
    void set_position(int x, int y);

private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    sf::Vector2f _size;
    float _x, _y;
};

#endif // CURSOR_H
