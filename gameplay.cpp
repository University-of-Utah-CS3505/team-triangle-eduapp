#include "gameplay.h"
#include "tile.h"
#include <QDebug>
#include <stdlib.h>
#include <vector>

gameplay::gameplay(engine& eng)
    : _editor{20, 300, 300}, _engine{eng},
      _tank(_texture, sf::IntRect(432, 48, 42, 46)), _current_move{0} {
    _texture.loadFromFile("../team-triangle-eduapp/assets/Tanks/Spritesheet/"
                          "allSprites_default.png");
    _tank.setOrigin(21, 23);
    _tank.setPosition(32, 32);

    _tiles.emplace_back(new tile(0,
                                 "../team-triangle-eduapp/assets/Tanks/PNG/"
                                 "DefaultSize/tileGrass1.png",
                                 "grass"));
    _tiles.emplace_back(new tile(1,
                                 "../team-triangle-eduapp/assets/Tanks/PNG/"
                                 "DefaultSize/tileGrass_roadNorth.png",
                                 "road"));
    _tiles.emplace_back(new tile(2,
                                 "../team-triangle-eduapp/assets/Tanks/PNG/"
                                 "DefaultSize/tileGrass_roadEast.png",
                                 "road"));
    _tiles.emplace_back(new tile(3,
                                 "../team-triangle-eduapp/assets/Tanks/PNG/"
                                 "DefaultSize/tileGrass_roadCornerLL.png",
                                 "road"));
    _tiles.emplace_back(new tile(4,
                                 "../team-triangle-eduapp/assets/Tanks/PNG/"
                                 "DefaultSize/tileGrass_roadCornerLR.png",
                                 "road"));
    _tiles.emplace_back(new tile(5,
                                 "../team-triangle-eduapp/assets/Tanks/PNG/"
                                 "DefaultSize/tileGrass_roadCornerUL.png",
                                 "road"));
    _tiles.emplace_back(new tile(6,
                                 "../team-triangle-eduapp/assets/Tanks/PNG/"
                                 "DefaultSize/tileGrass_roadCornerUR.png",
                                 "road"));
    // editor hard coded for testing
    _editor.set_text("hello!\nTesting text for enter and space !");
}

int gameplay::move_tank(char dir, int current_move) {
    int delta_x = 0;
    int delta_y = 0;
    int delta_r = 0;
    int current_rotation = _tank.getRotation();
    if (current_rotation >= 360) {
        current_rotation = current_rotation % 360;
        _tank.setRotation(current_rotation);
    }
    switch (dir) {
    case 'u':
    case 'U':
        if (current_rotation == 180) {
            delta_y = -1;
        } else {
            if (current_rotation < 180) {
                delta_r = 2;
            } else {
                delta_r = -2;
            }
        }
        break;
    case 'd':
    case 'D':
        if (current_rotation == 0) {
            delta_y = 1;
        } else {
            if (current_rotation < 0) {
                delta_r = 2;
            } else {
                delta_r = -2;
            }
        }
        break;
    case 'l':
    case 'L':
        if (current_rotation == 90) {
            delta_x = -1;
        } else {
            if (current_rotation % 90 > 180) {
                delta_r = 2;
            } else {
                delta_r = -2;
            }
        }
        break;
    case 'r':
    case 'R':
        if (current_rotation == 270) {
            delta_x = 1;
        } else {
            if (current_rotation % 270 > 180) {
                delta_r = 2;
            } else {
                delta_r = -2;
            }
        }
        break;
    }

    _tank.setRotation(current_rotation + delta_r);
    _tank.setPosition((_tank.getPosition().x) + delta_x,
                      (_tank.getPosition().y) + delta_y);
    return current_move + abs(delta_x) + abs(delta_y);
}

std::unique_ptr<game_state> gameplay::update() {

    int tile_height = 5;
    int tile_width = 5;
    int tile_map[5][5] = {{1, 0, 0, 0, 0},
                          {1, 0, 0, 0, 0},
                          {6, 2, 2, 3, 0},
                          {0, 0, 0, 1, 0},
                          {0, 0, 0, 1, 0}};

    _engine.window().clear();
    for (int i = 0; i < tile_height; i++) {
        for (int j = 0; j < tile_width; j++) {
            _tiles[tile_map[i][j]]->set_sprite_position(j * 64, i * 64);
            _engine.window().draw(_tiles[tile_map[i][j]]->get_sprite());
        }
    }

    if (_current_move < 128) {
        _current_move = move_tank('d', _current_move);
    } else {
        if (_current_move < 192) {
            _current_move = move_tank('r', _current_move);
        } else {
            if (_current_move < 256) {
                _current_move = move_tank('u', _current_move);
            }
        }
    }

    _engine.window().draw(_tank);
    _engine.window().draw(_editor);
    return nullptr;
}
