#ifndef TEXTEDIT_H
#define TEXTEDIT_H

#include <SFML/Graphics.hpp>
#include <string>

class textedit : public sf::Drawable {
public:
    textedit(int font_size, int w, int h);
    void insert_char(char c);
    void backspace();
    void set_text(const std::string& text);
    std::string get_text() const;
    void move_cursor(int x, int y);
    void clear();
private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    sf::Font _font;
    int _font_size, _w, _h;
    std::string _text;
};

#endif // TEXTEDIT_H
