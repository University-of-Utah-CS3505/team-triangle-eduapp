#include "textedit.h"

textedit::textedit(int font_size, int w, int h) :
                    _font_size(font_size), _w(w), _h(h), _text(""){
    // TODO: need to pull font from main
    _font.loadFromFile("../team-triangle-eduapp/arial.ttf");
}

void textedit::insert_char(char c) { _text.push_back(c); }
void textedit::set_text(const std::string& text) { _text = text; }
std::string textedit::get_text() const { return _text; }
void textedit::backspace() {
    if(_text.size() == 0) return;
    else _text.pop_back();
}

void textedit::move_cursor(int x, int y) {

}

void textedit::clear() { _text.clear(); }

void textedit::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    // will implement more for style later
    sf::RectangleShape rect;
    rect.setSize(sf::Vector2f(350, 700));
    rect.setFillColor(sf::Color(255, 255, 255));
    rect.setPosition(350, 10);
    sf::Text text;
    text.setFont(_font);
    text.setFillColor(sf::Color::Black);
    text.setString(_text);
    text.setCharacterSize(_font_size);
    text.setPosition(360, 30);
    target.draw(rect);
    target.draw(text);
}
