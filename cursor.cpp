#include "cursor.h"

cursor::cursor(int font_size) : _size(sf::Vector2f(2, font_size)){ }
void cursor::set_position(int x, int y) { _x = x; _y = y; }

void cursor::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    sf::RectangleShape rect;
    rect.setSize(_size);
    rect.setPosition(_x, _y);
    rect.setFillColor(sf::Color::Red);
    target.draw(rect);
}

int cursor::get_x_position(){return _x;};
int cursor:: get_y_position(){return _y;};
