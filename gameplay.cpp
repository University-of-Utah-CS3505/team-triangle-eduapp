#include "gameplay.h"
#include "object_def.h"
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

    _editor.set_text("hello!\nTesting text for enter and space !\n test cursor "
                     "position.");

    _objects.emplace_back(new object_def("../team-triangle-eduapp/assets/Tanks/PNG/DefaultSize/crateWood.png", "Temp", sf::Vector2i(100,100), sf::Vector2i(28,28)));
    _objects.emplace_back(new object_def("../team-triangle-eduapp/assets/Tanks/PNG/DefaultSize/crateWood.png", "Temp", sf::Vector2i(200,100), sf::Vector2i(28,28)));

    auto t = std::thread([this]() {
        //_tank.run_state(std::make_unique<tank::move>(true));
        //_tank.wait_until_idle();
        _tank.run_state(std::make_unique<tank::rot_turret>(300));
        _tank.wait_until_idle();
        _tank.run_state(std::make_unique<tank::shoot>());
        _tank.wait_until_idle();
        _tank.run_state(std::make_unique<tank::rot_turret>(290));
        _tank.wait_until_idle();
        _tank.run_state(std::make_unique<tank::shoot>());
        _tank.wait_until_idle();
    });
    t.detach();
}

std::unique_ptr<game_state> gameplay::update() {
    _engine.window().clear();

    //Draw tiles
    for (int i = 0; i < _level.get_location_matrix().shape()[0]; i++) {
        for (int j = 0; j < _level.get_location_matrix().shape()[1]; j++) {
            tile tile_to_draw =  _level.get_location_tile_def(i,j);
           tile_to_draw.set_sprite_position(j*64,i*64);
            _engine.window().draw((tile_to_draw.get_sprite()));
        }
    }

    //Draw objects
    for(int i = 0; i < _objects.size(); i++){
        _engine.window().draw(_objects[i]->get_sprite());
        //Hit detection
        if(_objects[i]->get_position().x - _objects[i]->get_size().x < _tank.get_bullet_pos().x){
            if(_objects[i]->get_position().x + _objects[i]->get_size().x > _tank.get_bullet_pos().x){
                if(_objects[i]->get_position().y - _objects[i]->get_size().y < _tank.get_bullet_pos().y){
                    if(_objects[i]->get_position().y + _objects[i]->get_size().y > _tank.get_bullet_pos().y){
                        _tank.bullet_hit();
                        _objects.erase(_objects.begin() + i);
                        i = 0;
                    }
                }
            }
        }
    }

    _tank.update();
    _engine.window().draw(_tank);
    _engine.window().draw(_editor);

    return nullptr;
}

bool gameplay::handle_keyboard(sf::Event event){
    qDebug() << event.key.code;
    if (event.key.code == BACKSPACE_KEY) {
        _editor.backspace();
    } else if (event.key.code == RETURN_KEY) {
        _editor.insert_char('\n');
        return true;
    } else if (event.key.code == 53) { // to test scroll "5" down
        _editor.scroll(_editor.SCROLL_DOWN);
    } else if (event.key.code == 54) { // to test scroll "6" up
        _editor.scroll(_editor.SCROLL_UP);
    }
    else {
        _editor.insert_char(event.text.unicode);
        return true;
    }
    return false;
}
