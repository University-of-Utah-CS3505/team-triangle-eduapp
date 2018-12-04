#include "textedit.h"
#include <QDebug>

textedit::textedit(int font_size, int w, int h) :
                    _font_size(font_size), _w(w), _h(h),
                     _cursor(font_size) {
    // TODO: need to pull font from main
    _originx = 350;
    _originy = 10;
    _font.loadFromFile("../team-triangle-eduapp/assets/fonts/droid_sans_mono.ttf");
    _text.setFont(_font);
    _text.setFillColor(sf::Color::Black);
    _text.setCharacterSize(_font_size);
    _text.setPosition(_originx + MARGIN, _originy + MARGIN);
    _text.setString("");
}

void textedit::insert_char(char c) {
    // insert char at last index
    _text.setString(_text.getString() + c);
    move_cursor(_text.findCharacterPos(_text.getString().getSize()).x,
                _text.findCharacterPos(_text.getString().getSize()).y);
}

void textedit::set_text(const std::string& text) {
    // set x, y position of end of text
    if(_text.getString().getSize() != 0)
        clear();
    _text.setString(text);
    move_cursor(_text.findCharacterPos(_text.getString().getSize()).x,
                _text.findCharacterPos(_text.getString().getSize()).y);
}

sf::String textedit::get_text() const { return _text.getString(); }

void textedit::backspace() {
    if(_text.getString().getSize() == 0) return;
    // remove last index string
    sf::String tmp_text = _text.getString();
    tmp_text.erase(_text.getString().getSize() - 1);
    _text.setString(tmp_text);
    move_cursor(_text.findCharacterPos(_text.getString().getSize()).x,
                _text.findCharacterPos(_text.getString().getSize()).y);
}

void textedit::move_cursor(int x, int y) {
    _cursor.set_position(x, y);
}

void textedit::scroll(bool direction) {
    // TODO: top / bottom cases
    if (_text.getOrigin().y > _originy + MARGIN) { return; }
    if (direction) {
        move_cursor(_text.findCharacterPos(_text.getString().getSize()).x,
                    _text.findCharacterPos(_text.getString().getSize()).y-_text.getCharacterSize());
        _text.setPosition(_text.getPosition().x, _text.getPosition().y-_text.getCharacterSize());
    }
    else {
        move_cursor(_text.findCharacterPos(_text.getString().getSize()).x,
                    _text.findCharacterPos(_text.getString().getSize()).y+_text.getCharacterSize());
        _text.setPosition(_text.getPosition().x, _text.getPosition().y+_text.getCharacterSize());
    }
}

void textedit::clear() {
    // clean up every text
    _text.setString("");
    _cursor.set_position(_originx + MARGIN, _originy + MARGIN);
}

void textedit::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    // will implement more for style later
    sf::RectangleShape rect;
    rect.setSize(sf::Vector2f(_w, _h));
    rect.setFillColor(sf::Color(255, 255, 255));
    rect.setPosition(_originx, _originy);
    target.draw(rect);
    target.draw(_text);
    target.draw(_cursor);
}
