#include "gameplay.h"
#include "tile.h"
#include <QDebug>
#include <stdlib.h>
#include <vector>

gameplay::gameplay(engine& eng)
    : _editor{20, 300, 300}, _engine{eng} {

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

std::unique_ptr<game_state> gameplay::update() {

    //tank test;
    //test_tank.run_state(tank::move(true));
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


    //_engine.window().draw(_tank.get_sprite());
    _engine.window().draw(_editor);
    return nullptr;
}
