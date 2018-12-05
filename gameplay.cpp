#include "gameplay.h"
#include "pyinqt.h"
#include "tile.h"
#include <iostream>
#include <thread>
#include <vector>

gameplay::gameplay(engine& eng)
    : _editor{15, 400, 650}, _engine{eng}, _level(0),
      _text_handle(_engine.add_event_listener(
              sf::Event::TextEntered,
              [this](auto e) { return _handle_text(e); })),
      _keyboard_handle(
              _engine.add_event_listener(sf::Event::KeyPressed, [this](auto e) {
                  return _handle_keyboard(e);
              })) {

    _editor.set_text("hello!\nTesting text for enter and space !\n test cursor "
                     "position.");
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
            tile tile_to_draw = _level.get_location_tile_def(i, j);
            tile_to_draw.set_sprite_position(j * 64, i * 64);
            //            _tiles[tile_map[i][j]]->set_sprite_position(j * 64, i
            //            * 64);
            _engine.window().draw((tile_to_draw.get_sprite()));

            //            _engine.window().draw(_tiles[tile_map[i][j]]->get_sprite());
        }
    }

    for (auto& _tank : _tanks) {
        _tank->update();
        _engine.window().draw(*_tank);
    }
    _engine.window().draw(_editor);
    return nullptr;
}

bool gameplay::_handle_text(sf::Event event) {
    qDebug() << event.key.code;
    // qDebug() << sf::Keyboard::BackSpace;
    // for whatever reason, we get return carriage for the return key rather
    // than a newline
    if (event.text.unicode == '\r') {
        _editor.insert_char('\n');
    } else if (event.text.unicode == '\b') {
        _editor.backspace();
    } else {
        _editor.insert_char(event.text.unicode);
    }
    return false;
}

bool gameplay::_run_tanks() {
    _tanks.emplace_back(std::make_unique<tank>(
            _engine,
            sf::Sprite(_engine.load_texture(
                    "../team-triangle-eduapp/assets/Tanks/PNG/"
                    "DefaultSize/tankBody_blue.png")),
            sf::Sprite(_engine.load_texture(
                    "../team-triangle-eduapp/assets/Tanks/PNG/"
                    "DefaultSize/tankBlue_barrel2_outline.png")),
            sf::Sprite(_engine.load_texture(
                    "../team-triangle-eduapp/assets/Tanks/PNG/"
                    "DefaultSize/bulletBlue1_outline.png"))));
    auto thread = std::thread([this]() {
        namespace py = boost::python;
        // Retrieve the main module.
        qDebug() << _editor.get_text().toAnsiString().c_str();
        try {
            auto main = py::import("__main__");

            // Retrieve the main module's namespace
            auto global = main.attr("__dict__");
            auto result = py::exec(
                    py::str(_editor.get_text().toAnsiString()), global, global);
            std::cout << "test" << std::endl;
        } catch (boost::python::error_already_set const&) {
            // TODO give user the exception somehow (maybe print and redirect
            // stdout to something we print on screen)
        }
    });
    thread.detach();
}

bool gameplay::_handle_keyboard(sf::Event event) {
    if (event.key.code == sf::Keyboard::F5) {
        _run_tanks();
        return true;
    } else if (event.key.code ==
               sf::Keyboard::Key::Down) { // to test scroll "5" down
        _editor.scroll(_editor.SCROLL_DOWN);
        return true;
    } else if (event.key.code ==
               sf::Keyboard::Key::Up) { // to test scroll "6" up
        _editor.scroll(_editor.SCROLL_UP);
        return true;
    }
    return false;
}
