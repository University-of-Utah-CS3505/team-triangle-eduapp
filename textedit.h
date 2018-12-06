#ifndef TEXTEDIT_H
#define TEXTEDIT_H

#include <SFML/Graphics.hpp>
#include <string>
#include <QDebug>
#include "cursor.h"
#include "gap_buffer.h"


class textedit : public sf::Drawable {
public:
    textedit(int font_size, int w, int h);
    void insert_char(char c);
    void backspace();
    void set_text(const std::string& text);
    sf::String get_text() const;
    sf::String wrap_text();
    void move_cursor(int x, int y);
    void scroll_up();
    void scroll_down();
    void scroll_left();
    void scroll_right();
    void clear();
    const bool SCROLL_DOWN = true;
    const bool SCROLL_UP = false;
private:
    virtual void draw(sf::RenderTarget& target,
                      sf::RenderStates states) const;
    sf::View _view; // This would be nice to use, but need separate rendertarget
    sf::Font _font;
    gap_buffer _data;
    sf::Text _text;
    sf::Text nums;
    int _font_size, _w, _h;
    //std::string _text;
    int _originx, _originy;
    int MARGIN = 20;
    cursor _cursor;
   std::string get_line_numbers() const;
   void update_line_numbers();

};

#endif // TEXTEDIT_H
