#include "textedit.h"

textedit::textedit(int font_size, int w, int h) :
                    _font_size(font_size), _w(w), _h(h), _text(""){}

void textedit::insert_char(char c) { _text.push_back(c); }
void textedit::set_text(const std::string& text) { _text = text; }
std::string textedit::get_text() const { return _text; }
void textedit::backspace() {
    if(_text.size() == 0) return;
    else _text.pop_back();
}

void textedit::move_cursor(int x, int y) {
// I think we need to create another cpp for cursor to draw?
}

void textedit::draw(sf::RenderTarget& target, sf::RenderStates states) const {
   sf::Text text;
   text.setFont(_font);
   text.setString(_text);
   text.setCharacterSize(_font_size);
   target.draw(text, states);
}
