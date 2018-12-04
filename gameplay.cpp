#include "gameplay.h"
#include "tile.h"
#include <QDebug>
#include <stdlib.h>
#include <thread>
#include <vector>

gameplay::gameplay(engine& eng)
    : _editor{15, 400, 650}, _engine{eng},
      _tank(eng,
            sf::Sprite( eng.load_texture("../team-triangle-eduapp/assets/Tanks/PNG/"
                                         "DefaultSize/tankBody_blue.png")),
            sf::Sprite( eng.load_texture("../team-triangle-eduapp/assets/Tanks/PNG/"
                                         "DefaultSize/tankBlue_barrel2_outline.png")),
            sf::Sprite( eng.load_texture("../team-triangle-eduapp/assets/Tanks/PNG/"
                                         "DefaultSize/bulletBlue1_outline.png"))),
        _level(0), _keyboard_handle(
                       _engine.add_event_listener(sf::Event::TextEntered,
                              [this](auto e){return handle_keyboard(e);})){

//    _tiles.emplace_back(new tile(0,
//                                 "../team-triangle-eduapp/assets/Tanks/PNG/"
//                                 "DefaultSize/tileGrass1.png",
//                                 "grass"));
//    _tiles.emplace_back(new tile(1,
//                                 "../team-triangle-eduapp/assets/Tanks/PNG/"
//                                 "DefaultSize/tileGrass_roadNorth.png",
//                                 "road"));
//    _tiles.emplace_back(new tile(2,
//                                 "../team-triangle-eduapp/assets/Tanks/PNG/"
//                                 "DefaultSize/tileGrass_roadEast.png",
//                                 "road"));
//    _tiles.emplace_back(new tile(3,
//                                 "../team-triangle-eduapp/assets/Tanks/PNG/"
//                                 "DefaultSize/tileGrass_roadCornerLL.png",
//                                 "road"));
//    _tiles.emplace_back(new tile(4,
//                                 "../team-triangle-eduapp/assets/Tanks/PNG/"
//                                 "DefaultSize/tileGrass_roadCornerLR.png",
//                                 "road"));
//    _tiles.emplace_back(new tile(5,
//                                 "../team-triangle-eduapp/assets/Tanks/PNG/"
//                                 "DefaultSize/tileGrass_roadCornerUL.png",
//                                 "road"));
//    _tiles.emplace_back(new tile(6,
//                                 "../team-triangle-eduapp/assets/Tanks/PNG/"
//                                 "DefaultSize/tileGrass_roadCornerUR.png",
//                                 "road"));
//    // editor hard coded for testing
    _editor.set_text("hello!\nTesting text for enter and space !\n test cursor "
                     "position.");
    auto t = std::thread([this]() {
        _tank.run_state(std::make_unique<tank::move>(true));
        _tank.wait_until_idle();
        _tank.run_state(std::make_unique<tank::rot_turret>(90));
        _tank.wait_until_idle();
        _tank.run_state(std::make_unique<tank::move>(true));
        _tank.wait_until_idle();
        _tank.run_state(std::make_unique<tank::rot_turret>(270));
        _tank.wait_until_idle();
        _tank.run_state(std::make_unique<tank::rotate>(false));
        _tank.wait_until_idle();
        _tank.run_state(std::make_unique<tank::move>(true));
        _tank.wait_until_idle();
        _tank.run_state(std::make_unique<tank::rotate>(true));
        _tank.wait_until_idle();
        _tank.run_state(std::make_unique<tank::rotate>(true));
        _tank.wait_until_idle();
        _tank.run_state(std::make_unique<tank::move>(false));
        _tank.wait_until_idle();
        _tank.run_state(std::make_unique<tank::move>(false));
        _tank.wait_until_idle();
        _tank.run_state(std::make_unique<tank::shoot>());
        _tank.wait_until_idle();
        _tank.run_state(std::make_unique<tank::rot_turret>(180));
        _tank.wait_until_idle();
        _tank.run_state(std::make_unique<tank::shoot>());

    });
    t.detach();
}

std::unique_ptr<game_state> gameplay::update() {
//    int tile_height = 5;
//    int tile_width = 5;
//    int tile_map[5][5] = {{1, 0, 0, 0, 0},
//                          {1, 0, 0, 0, 0},
//                          {6, 2, 2, 3, 0},
//                          {0, 0, 0, 1, 0},
//                          {0, 0, 0, 1, 0}}; // get boost array

    _engine.window().clear();
    for (int i = 0; i < _level.get_location_matrix().shape()[0]; i++) {
        for (int j = 0; j < _level.get_location_matrix().shape()[1]; j++) {
            tile tile_to_draw =  _level.get_location_tile_def(i,j);
           tile_to_draw.set_sprite_position(j*64,i*64);
//            _tiles[tile_map[i][j]]->set_sprite_position(j * 64, i * 64);
            _engine.window().draw((tile_to_draw.get_sprite()));

//            _engine.window().draw(_tiles[tile_map[i][j]]->get_sprite());

        }
    }

    _tank.update();
    _engine.window().draw(_tank);
    _engine.window().draw(_editor);
    return nullptr;
}

bool gameplay::handle_keyboard(sf::Event event){
    qDebug() << event.key.code;
    // qDebug() << sf::Keyboard::BackSpace;
    if (event.key.code == BACKSPACE_KEY) {
        _editor.backspace();
    } else if (event.key.code == RETURN_KEY) {
        _editor.insert_char('\n');
        return true;
    } else if (event.key.code == 53) { // to test scroll "5" down
        _editor.scroll_down();
    } else if (event.key.code == 54) { // to test scroll "6" up
        _editor.scroll_up();
    } else if (event.key.code == 55) { // "7" left
        _editor.scroll_left();
    } else if (event.key.code == 56) { // "8" right
        _editor.scroll_right();
    }
    else {
        _editor.insert_char(event.text.unicode);
        return true;
    }
    return false;
}
