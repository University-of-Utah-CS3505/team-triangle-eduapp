#include "textedit.h"
#include <QDebug>
#include <iostream>

textedit::textedit(int font_size, int w, int h) :
                    _font_size(font_size), _w(w), _h(h),
                     _cursor(font_size) {
    // TODO: need to pull font from main
    _originx = 400;
    _originy = 10;
    _font.loadFromFile("../team-triangle-eduapp/assets/fonts/droid_sans_mono.ttf");
    _text.setFont(_font);
    _text.setFillColor(sf::Color::Black);
    _text.setCharacterSize(_font_size);
    _text.setPosition(_originx + MARGIN, _originy + MARGIN);
    _text.setString("");

    nums.setString("1\n");
    nums.setPosition(_originx-25, _originy+MARGIN);
    nums.setFont(_font);
    nums.setFillColor(sf::Color(100, 100, 100));
    nums.setCharacterSize(_font_size);
}

void textedit::insert_char(char c) {
    // insert char at last index
    _data.insert_char(c);
    std::string s;
    for(int i = 0; i < _data.buffer_size(); i++){
        s = _data.get_char();
        _data.set_point(i+1);
    }
   _text.setString(_text.getString() + s);
   move_cursor(_text.findCharacterPos(_text.getString().getSize()).x,
                _text.findCharacterPos(_text.getString().getSize()).y);

   if(c == '\n' || c == '\r'){

       nums.setString(get_line_numbers());
   }
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

sf::String textedit::wrap_text() {
    auto characters_per_line = _w / (_font.getKerning(0, 1, _font_size));
    std::cout << characters_per_line << std::endl;
    return _text.getString();
}

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
    // TODO: align cursor to character pos and
    auto align_x = (x - MARGIN) % (int)(_text.getLetterSpacing() + _text.getCharacterSize());
    auto align_y = (y - MARGIN) % (int)(_text.getLetterSpacing() + _text.getCharacterSize());
    std::cout << x << "," << y << " " << _text.getCharacterSize()
              << " " << x-align_x << std::endl;
    _cursor.set_position(x, y);
}

void textedit::scroll_up() {
    move_cursor(_text.findCharacterPos(_text.getString().getSize()).x,
                _text.findCharacterPos(_text.getString().getSize()).y-_text.getCharacterSize());
    _text.setPosition(_text.getPosition().x, _text.getPosition().y-_text.getCharacterSize());
}

void textedit::scroll_down() {
    move_cursor(_text.findCharacterPos(_text.getString().getSize()).x,
                _text.findCharacterPos(_text.getString().getSize()).y+_text.getCharacterSize());
    _text.setPosition(_text.getPosition().x, _text.getPosition().y+_text.getCharacterSize());
}

void textedit::scroll_left() {
    move_cursor(_text.findCharacterPos(_text.getString().getSize()).x-_text.getCharacterSize(),
                _text.findCharacterPos(_text.getString().getSize()).y);
    _text.setPosition(_text.getPosition().x-_text.getCharacterSize(), _text.getPosition().y);
}

void textedit::scroll_right() {
    move_cursor(_text.findCharacterPos(_text.getString().getSize()).x+_text.getCharacterSize(),
                _text.findCharacterPos(_text.getString().getSize()).y);
    _text.setPosition(_text.getPosition().x+_text.getCharacterSize(), _text.getPosition().y);
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

    sf::RectangleShape line_numbers;
    line_numbers.setSize(sf::Vector2f(40.0, _h));
    line_numbers.setFillColor(sf::Color(230,230,230));
    line_numbers.setPosition(_originx-40,_originy);
    target.draw(line_numbers);




    target.draw(nums);
}

std::string textedit::get_line_numbers() const{
    std::string nums="1\n";
    int i = 2;
    for(char c: _text.getString()){
        if(c == '\n' || c=='\r'){

            nums += std::to_string(i)+'\n';
            i++;
        }

    }
    nums += std::to_string(i)+"\n";
    return nums;
}
