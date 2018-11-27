#ifndef TEXTEDIT_H
#define TEXTEDIT_H

#include <SFML/Graphics/Drawable.hpp>
#include <string>

class textedit : public sf::Drawable {
public:
    textedit(int font_size, int w, int h);

    void insert_char(char c);
    void backspace();

    void set_text(const std::string& text);
    std::string get_text() const;

    void move_cursor(int x, int y);

private:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};

#endif // TEXTEDIT_H
