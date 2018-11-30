#ifndef TEXTEDIT_H
#define TEXTEDIT_H

#include <SFML/Graphics.hpp>
#include <string>
#include <QDebug>
#include "cursor.h"

class textedit : public sf::Drawable {
public:
    textedit(int font_size, int w, int h);
    void insert_char(char c);
    void backspace();
    void set_text(const std::string& text);
    sf::String get_text() const;
    void move_cursor(int x, int y);
    void clear();
private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    sf::Font _font;
    sf::Text _text;
    int _font_size, _w, _h;
    //std::string _text;
    int _originx, _originy;
    int MARGIN = 20;
    cursor _cursor;
};

#endif // TEXTEDIT_H
