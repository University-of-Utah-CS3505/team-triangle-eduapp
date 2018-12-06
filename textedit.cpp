#include "textedit.h"
#include <math.h>
#include <QDebug>
#include <iostream>

textedit::textedit(int font_size, int w, int h) :
                    _font_size(font_size), _w(w), _h(h),
                     _cursor(font_size) {
    // TODO: need to pull font from main
    _originx = 400;
    _originy = 10;
    _text_size = 0;
    _iswriting = false;
    _current_char_index = 0;
    _font.loadFromFile("../team-triangle-eduapp/assets/fonts/droid_sans_mono.ttf");
    _text.setFont(_font);
    _text.setFillColor(sf::Color::Black);
    _text.setCharacterSize(_font_size);
    _text.setPosition(_originx + MARGIN, _originy + MARGIN);
    _text.setString("");
    move_cursor(_originx + MARGIN, _originy + MARGIN);

    nums.setString("1\n");
    nums.setPosition(_originx-25, _originy+MARGIN);
    nums.setFont(_font);
    nums.setFillColor(sf::Color(100, 100, 100));
    nums.setCharacterSize(_font_size);
}

void textedit::insert_char(char c) {
    _iswriting = true;
//    auto char_pos_x = ((_cursor.get_x_position() - (_originx + MARGIN)) / _text.getCharacterSize());
//    auto char_pos_y = ((_cursor.get_y_position() - (_originy + MARGIN)) / _text.getCharacterSize());

//    int x = (_cursor.get_x_position()-_originx + MARGIN)/9;
//    int y = (_cursor.get_y_position()- _originy + MARGIN)/17;
//    sf::Vector2f new_cursor = _text.findCharacterPos(x+y);
    // std::cout << new_cursor.x << " " << new_cursor.y << std::endl;
    // In std::vector<std::string> it's _data[char_pos_y][char_pos_x]
    // To insert: std::insert(char_pos_x, _data[char_pos_y])
    // To delete: std::remove(char_pos_x, _data[char_pos_y])

    // In char buffer you need to get the full buffer and count '\n' characters to get line
    // get_offset -- count '\n' up to line_num and count all characters up to that point to get
    // line offset, then add x_char_pos
    // insert char at last index
    _data.insert_char(c);

    std::string s;
    for(int i = 0; i < _data.buffer_size(); i++){
        s = _data.get_char();
        _data.set_point(i+1);       
        _text_size++;
    }
    sf::String temp_str;
    temp_str = _text.getString().substring(0, _current_char_index);
    temp_str += s;
    temp_str = temp_str + _text.getString().substring(_current_char_index, _text.getString().getSize() - _current_char_index);
    _text.setString(temp_str);
    _current_char_index += s.size();
    move_cursor(_text.findCharacterPos(_current_char_index).x, _text.findCharacterPos(_current_char_index).y);

    //move_cursor(new_cursor.x, new_cursor.y);

    if(c == '\n' || c == '\r')
        nums.setString(get_line_numbers());
    _iswriting = false;
}

void textedit::set_text(const std::string& text) {
    // set x, y position of end of text
    if(_text.getString().getSize() != 0)
        clear();
    _text.setString(text);
    _text_size = _text.getString().getSize();
    _current_char_index = _text_size;
    _text_size = _text.getString().getSize();
    move_cursor(_text.findCharacterPos(_text_size).x,
                _text.findCharacterPos(_text_size).y);
}

sf::String textedit::get_text() const { return _text.getString(); }

sf::String textedit::wrap_text() {
    auto characters_per_line = _w / (_font.getKerning(0, 1, _font_size));
    std::cout << characters_per_line << std::endl;
    return _text.getString();
}

void textedit::backspace() {
    if(_text.getString().getSize() == 0){ return;}
    // remove last index string
    _iswriting = true;
    sf::String tmp_text = _text.getString();
    tmp_text.erase(_text.getString().getSize() - 1);
    _text.setString(tmp_text);
    _text_size--;
    _current_char_index--;
    move_cursor(_text.findCharacterPos(_text.getString().getSize()).x,
                _text.findCharacterPos(_text.getString().getSize()).y);
    _iswriting = false;
}

void textedit::move_cursor(float x, float y) {

    // auto new_x = ((x - (_originx+MARGIN))/_text.getCharacterSize()) * _text.getCharacterSize();
    // auto new_y = ((y - (_originy+ MARGIN))/ _text.getLineSpacing()) * _text.getLineSpacing();
    //std::cout << new_x << "," << new_y <<std::endl;
    //int new_x;
    //int new_y;
    // make boundary for texteditor
    if(_iswriting) {}
    else if(x < _originx + MARGIN || y < _originy + MARGIN ||
            x > _originx + MARGIN + _w || y > _originy + MARGIN + _h)
        return;
    else {
        if(y > _text.findCharacterPos(_text_size).y + _text.getCharacterSize()) {
            x = _text.findCharacterPos(_text_size).x;
            y = _text.findCharacterPos(_text_size).y;
            //_current_char_index = _text_size;
        }
        //else {
        // TODO: still need to make right position by line for clicking
        int closest_index = 0;
        int closest_dist = std::numeric_limits<int>::max();
        int closest_y = std::numeric_limits<int>::max();
        // find closest char
        for(int i = 0; i <= _text_size; i++) {
            sf::Vector2f position = _text.findCharacterPos(i);
            if(y < position.y)
                break;
            float dist_y = y - position.y;
            if(closest_y >= dist_y) {
                closest_y = dist_y;
                float dist = pow(x - position.x, 2) + pow(y - position.y, 2);
                if(closest_dist > dist) {
                    if(position.y <= y) {
                        closest_index = i;
                        closest_dist = dist;
                        _current_char_index = i;
                    }
                }
            }
        }
        x = _text.findCharacterPos(closest_index).x;
        y = _text.findCharacterPos(closest_index).y;
    //}
    }
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
    _text_size = 0;
    _current_char_index = 0;
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
