#include "tank.h"
#include <stdlib.h>

/*tank::tank(std::string img) : _sprite(_texture, sf::IntRect(0, 0, 42, 46)) {
    _texture.loadFromFile(img);

    _sprite.setOrigin(21, 23);
    _sprite.setPosition(32, 32);
}

tank::rotate(char dir) {
    int rotation = _sprite.getRotation();
    switch (dir) {
    case 'u':
    case 'U': // 180
        if (rotation != 180) {
            if (rotation < 180) {
                rotation += 2;
            } else {
                rotation -= 2;
            }
        }
        break;
    case 'd':
    case 'D': // 0
        if (rotation != 0) {
            if (rotation > 180) {
                rotation += 2;
            } else {
                rotation -= 2;
            }
        }
        break;
    case 'l':
    case 'L': // 90
        if (rotation != 90) {
            if (rotation > 270 || rotation < 90) {
                rotation += 2;
            } else {
                rotation -= 2;
            }
        }
        break;
    case 'r':
    case 'R': // 270
        if (rotation != 270) {
            if (rotation < 90 || rotation > 270) {
                rotation -= 2;
            } else {
                rotation += 2;
            }
        }
        break;
    }

    // Change rotation to between 0 and 360
    if (rotation >= 360) {
        rotation = rotation % 360;
    } else {
        if (rotation < 0) {
            rotation = 360 + rotation;
        }
    }
    _sprite.setRotation(rotation);

    if (_current_move_pos = 90) {
        _current_move_pos = 0;
        return true;
    }
    _current_move_pos += 2;
    return false;
}

bool tank::move_forward() {
    int dx = 0;
    int dy = 0;

    switch ((int)_sprite.getRotation()) {
    case 0:
        dy = 1;
        break;
    case 90:
        dx = -1;
        break;
    case 180:
        dy = -1;
        break;
    case 270:
        dx = 1;
        break;
    default:
        break;
    }

    _sprite.setPosition((_sprite.getPosition().x) + dx,
                        (_sprite.getPosition().y) + dy);
    if (_current_move_pos = 64) {
        _current_move_pos = 0;
        return true;
    }
    _current_move_pos += abs(dx) + abs(dy);
    return false;
}

bool tank::shoot() {}

void tank::set_position(int x, int y) { _sprite.setPosition(x, y); }

int tank::get_x() { return _x; }

int tank::get_y() { return _y; }

sf::Sprite tank::get_sprite() { return _sprite; }*/
