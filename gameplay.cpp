#include "gameplay.h"
#include "object_def.h"
#include "pyinqt.h"
#include "tile.h"
#include <iostream>
#include <thread>
#include <vector>
#include <QTextDocument>

gameplay::gameplay(engine& eng)

    : _editor{15, 400, 650}, _engine{eng},
        _level(0), _keyboard_handle(
                       _engine.add_event_listener(sf::Event::TextEntered,
                              [this](auto e){return _handle_keyboard(e);})),
          _mouse_handle(_engine.add_event_listener(sf::Event::MouseButtonPressed,
                                                   [this](auto e){return handle_mouse(e);})),
          _text_handle(_engine.add_event_listener(
                  sf::Event::TextEntered,
                  [this](auto e) { return _handle_text(e); })){
    _load_level(1);
}

std::unique_ptr<game_state> gameplay::update() {
    _engine.window().clear();

    // Draw tiles
    for (int i = 0; i < _level.get_location_matrix().shape()[0]; i++) {
        for (int j = 0; j < _level.get_location_matrix().shape()[1]; j++) {
            tile tile_to_draw = _level.get_location_tile_def(i, j);
            tile_to_draw.set_sprite_position(j * 64, i * 64);
            _engine.window().draw((tile_to_draw.get_sprite()));
        }
    }

    // Draw objects
    for (auto& c_tank : _tanks) {
        c_tank->update();
        _engine.window().draw(*c_tank);
        for (int i = 0; i < _objects.size(); i++) {
            _engine.window().draw(_objects[i]->get_sprite());
            // Hit detection
            if (_objects[i]->get_position().x - _objects[i]->get_size().x <
                c_tank->get_bullet_pos().x) {
                if (_objects[i]->get_position().x + _objects[i]->get_size().x >
                    c_tank->get_bullet_pos().x) {
                    if (_objects[i]->get_position().y -
                                _objects[i]->get_size().y <
                        c_tank->get_bullet_pos().y) {
                        if (_objects[i]->get_position().y +
                                    _objects[i]->get_size().y >
                            c_tank->get_bullet_pos().y) {
                            c_tank->bullet_hit();
                            _objects.erase(_objects.begin() + i);
                            i = 0;
                        }
                    }
                }
            }
        }
    }

    _engine.window().draw(_editor);

    return nullptr;
}

bool gameplay::_handle_text(sf::Event event) {
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

bool gameplay::handle_mouse(sf::Event event){
    _editor.move_cursor(event.mouseButton.x, event.mouseButton.y);

    return true;
}
bool gameplay::_run_tanks() {

    auto thread = std::thread([this]() {
        namespace py = boost::python;
        // Retrieve the main module.
        qDebug() << _editor.get_text().toAnsiString().c_str();
        try {

            auto main = py::import("__main__");

            // Retrieve the main module's namespace
            auto global = main.attr("__dict__");
            auto debug_print = py::make_function(
                    std::function([](py::object x) {
                        std::cout << py::extract<std::string>(x)() << std::endl;
                    }),
                    py::default_call_policies(),
                    boost::mpl::vector<void, py::object>());
            global["d_print"] = debug_print;

            auto result = py::exec(
                    py::str(_editor.get_text().toAnsiString()), global, global);
            std::cout << "test" << std::endl;
        } catch (py::error_already_set const&) {
            // https://stackoverflow.com/a/1418703
            // TODO give user the exception somehow (maybe print and redirect
            // stdout to something we print on screen)
            auto ptype = static_cast<PyObject*>(nullptr),
                 pvalue = static_cast<PyObject*>(nullptr),
                 ptraceback = static_cast<PyObject*>(nullptr);
            PyErr_Fetch(&ptype, &pvalue, &ptraceback);
            // pvalue contains error message
            // ptraceback contains stack snapshot and many other information
            std::cout //<< py::extract<std::string>(ptype)() << "\n"
                    << py::extract<std::string>(pvalue)() << std::endl;
            // << py::extract<std::string>(ptraceback)() << std::endl;
        }
    });
    thread.detach();
}

bool gameplay::_load_level(int level)
{
    _level.load_new_level(level);
    //Load Tiles
    //Load Objects
    _objects.emplace_back(new object_def("../team-triangle-eduapp/assets/Tanks/"
                                         "PNG/DefaultSize/crateWood.png",
                                         "Temp",
                                         sf::Vector2i(100, 100),
                                         sf::Vector2i(28, 28)));
    _objects.emplace_back(new object_def("../team-triangle-eduapp/assets/Tanks/"
                                         "PNG/DefaultSize/crateWood.png",
                                         "Temp",
                                         sf::Vector2i(200, 100),
                                         sf::Vector2i(28, 28)));

    //Load Tank
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
    return true;
}

bool gameplay::_handle_keyboard(sf::Event event) {
    if (event.key.code == sf::Keyboard::F5) {
        _run_tanks();
        return true;
    } else if (event.key.code == sf::Keyboard::PageDown) {
        _editor.scroll_down();
        return true;
    } else if (event.key.code == sf::Keyboard::PageUp) {
        _editor.scroll_up();
        return true;
    } else if (event.key.code == sf::Keyboard::Home) {
        _editor.scroll_left();
        return true;
    } else if (event.key.code == sf::Keyboard::End) {
        _editor.scroll_right();
        return true;
    } else {
        return false;
    }

}
