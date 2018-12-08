#include "gameplay.h"
#include "object_def.h"
#include "pyinqt.h"
#include "tile.h"
#include <QTextDocument>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <thread>
#include <vector>
#include <QDebug>

gameplay::gameplay(engine& eng, int level)

    : _editor{15, 800, 650}, _engine{eng}, _level(0), _current_level(level),
      _text_handle(_engine.add_event_listener(
              sf::Event::TextEntered,
              [this](auto e) {
                  _input_con.handleEvents(
                          _text_doc, _text_view, _engine.window(), e);
                  return true;
              })),

      _pressed_handle(_engine.add_event_listener(
              sf::Event::KeyPressed,
              [this](auto e) {
                  if (_handle_keyboard(e)) {
                      return true;
                  } else {
                      _input_con.handleEvents(
                              _text_doc, _text_view, _engine.window(), e);
                      return true;
                  }
              })),

      _released_handle(_engine.add_event_listener(
              sf::Event::KeyReleased,
              [this](auto e) {
                  _input_con.handleEvents(
                          _text_doc, _text_view, _engine.window(), e);
                  return true;
              })),

      _mouse_click(_engine.add_event_listener(
              sf::Event::MouseButtonPressed,
              [this](auto e) {
                  if (handle_mouse(e)) {
                      return true;
                  } else {
                      _input_con.handleEvents(
                              _text_doc, _text_view, _engine.window(), e);
                  }
              })),
      _text_view((_editor_subtarget.create(1920 * 0.333333, 1080),
                  _editor_subtarget),
                 "./../team-triangle-eduapp/assets/fonts/droid_sans_mono.ttf") {
    _load_level(_current_level);
    _text_doc.addTextToPos(_level._level_instructions, 0,0);
    int lines = _text_doc.getLineCount();
    for(int i = 0; i< lines; i++){
        _text_view.moveCursorDown(_text_doc, false);
    }
    _text_view.moveCursorToEnd(_text_doc, false);

}

std::unique_ptr<game_state> gameplay::update() {
    _engine.window().clear();

    // Draw tiles
    for (int i = 0; i < _level.get_location_matrix().shape()[0]; i++) {
        for (int j = 0; j < _level.get_location_matrix().shape()[1]; j++) {
            tile tile_to_draw = _level.get_location_tile_def(i, j);
            tile_to_draw.set_sprite_position(j * 64+(.1655*_engine.window().getSize().x), i * 64+(.1665*_engine.window().getSize().y));
            _engine.window().draw((tile_to_draw.get_sprite()));
        }
    }

    // Draw objects
    for (auto& c_tank : _tanks) {
        c_tank->update();
        for (int i = 0; i < _objects.size(); i++) {
            _engine.window().draw(_objects[i]->get_sprite());

            //Tank hitting objects
            if(_objects[i]->get_type() == "destroyable" ||
                    _objects[i]->get_type() == "solid") {
                if (_objects[i]->get_position().x - _objects[i]->get_size().x <
                    c_tank->get_position().x) {
                    if (_objects[i]->get_position().x + _objects[i]->get_size().x >
                        c_tank->get_position().x) {
                        if (_objects[i]->get_position().y -
                                    _objects[i]->get_size().y <
                            c_tank->get_position().y) {
                            if (_objects[i]->get_position().y +
                                        _objects[i]->get_size().y >
                                c_tank->get_position().y) {
                                    c_tank->run_state(
                                        std::make_unique<tank::explode>());
                                    //_load_level(_current_level);
                            }
                        }
                    }
                }
            }

            // Hit detection for objects and bullet
            if(c_tank->is_shooting()){
                if(_objects[i]->get_type() == "destroyable" ||
                        _objects[i]->get_type() == "solid") {
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
                                    if(_objects[i]->get_type() == "destroyable"){
                                        _objects.erase(_objects.begin() + i);
                                        i = 0;
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
        _engine.window().draw(*c_tank);
    }
    _editor_subtarget.clear(sf::Color(21, 29, 45));
    _editor_subtarget.setView(_text_view.getCameraView());

    _text_view.draw(_editor_subtarget, _text_doc);
    auto editor = sf::Sprite();
    editor.setPosition(0.66666 * _engine.window().getSize().x, 0);
    _editor_subtarget.display();
    editor.setTexture(_editor_subtarget.getTexture());
    _engine.window().draw(editor);

    //draw level name
    auto level_name = sf::Text();
    auto font = sf::Font();
    font.loadFromFile("../team-triangle-eduapp/assets/fonts/droid_sans_mono.ttf");
    level_name.setString(_level._level_name);
    level_name.setPosition(0.1665 * _engine.window().getSize().x, 10);
    level_name.setCharacterSize(30);
    level_name.setFont(font);
    level_name.setFillColor(sf::Color::White);
    _engine.window().draw(level_name);
    return nullptr;
}

bool gameplay::_handle_text(sf::Event event) {
    // qDebug() << sf::Keyboard::BackSpace;
    // for whatever reason, we get return carriage for the return key rather
    // than a newline
    if (event.text.unicode == '\r') {
        _editor.insert_char('\n');
        // _editor.new_line();
    } else if (event.text.unicode == '\b') {
        _editor.backspace();
    } else {
        _editor.insert_char(event.text.unicode);
    }
    return false;
}

bool gameplay::handle_mouse(sf::Event event) {
    _editor.move_cursor(event.mouseButton.x, event.mouseButton.y - 10);

    return true;
}

bool gameplay::_run_tanks() {
    _load_level(_current_level);
    auto user_source = std::string();
    for (auto i = 0; i < _text_doc.getLineCount(); i++) {
        user_source.append(_text_doc.getLine(i).toAnsiString() + "\n");
    }
    auto thread = std::thread([this, user_source]() {
        namespace py = boost::python;
        // Retrieve the main module.
        try {
            auto main = py::import("__main__");

            // Retrieve the main module's namespace
            auto global = main.attr("__dict__");
            global["d_print"] = py::make_function(
                    std::function([](py::object x) {
                        std::cout << py::extract<std::string>(x)() << std::endl;
                    }),
                    py::default_call_policies(),
                    boost::mpl::vector<void, py::object>());

            global["forward"] = py::make_function(
                    std::function([this]() {
                        for (auto& c_tank : _tanks) {
                            c_tank->run_state(
                                    std::make_unique<tank::move>(true));
                        }
                        for (auto& c_tank : _tanks) {
                            c_tank->wait_until_idle();
                        }
                    }),
                    py::default_call_policies(),
                    boost::mpl::vector<void>());

            global["backward"] = py::make_function(
                    std::function([this]() {
                        for (auto& c_tank : _tanks) {
                            c_tank->run_state(
                                    std::make_unique<tank::move>(false));
                        }
                        for (auto& c_tank : _tanks) {
                            c_tank->wait_until_idle();
                        }
                    }),
                    py::default_call_policies(),
                    boost::mpl::vector<void>());

            global["turn_left"] = py::make_function(
                    std::function([this]() {
                        for (auto& c_tank : _tanks) {
                            c_tank->run_state(
                                    std::make_unique<tank::rotate>(false));
                        }
                        for (auto& c_tank : _tanks) {
                            c_tank->wait_until_idle();
                        }
                    }),
                    py::default_call_policies(),
                    boost::mpl::vector<void>());

            global["turn_right"] = py::make_function(
                    std::function([this]() {
                        for (auto& c_tank : _tanks) {
                            c_tank->run_state(
                                    std::make_unique<tank::rotate>(true));
                        }
                        for (auto& c_tank : _tanks) {
                            c_tank->wait_until_idle();
                        }
                    }),
                    py::default_call_policies(),
                    boost::mpl::vector<void>());

            global["shoot"] = py::make_function(
                    std::function([this]() {
                        for (auto& c_tank : _tanks) {
                            c_tank->run_state(std::make_unique<tank::shoot>());
                        }
                        for (auto& c_tank : _tanks) {
                            c_tank->wait_until_idle();
                        }
                    }),
                    py::default_call_policies(),
                    boost::mpl::vector<void>());

            global["rotate_turret"] = py::make_function(
                    std::function([this](py::object py_angle) {
                        auto angle = py::extract<float>(py_angle);
                        for (auto& c_tank : _tanks) {
                            c_tank->run_state(
                                    std::make_unique<tank::rot_turret>(angle));
                        }
                        for (auto& c_tank : _tanks) {
                            c_tank->wait_until_idle();
                        }
                    }),
                    py::default_call_policies(),
                    boost::mpl::vector<void, py::object>());

            auto result = py::exec(py::str(user_source), global, global);
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

bool gameplay::_load_level(int level) {
    _level.load_new_level(level);
    _current_level = level;
    _objects.clear();
    _tanks.clear();

    for(auto &obj : _level.get_objects()){
        obj->set_offset(.1655*_engine.window().getSize().x, .1655*_engine.window().getSize().y);
        _objects.emplace_back(obj);
    }

    // Load Tank
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
    for(auto &tank : _tanks){
        tank->set_offset(.1655*_engine.window().getSize().x, .1655*_engine.window().getSize().y);

        tank->set_bullet_bounds(.1655*_engine.window().getSize().x,
                                .1655*_engine.window().getSize().y,
                                .1655*_engine.window().getSize().x + (_level.get_location_matrix().shape()[0] * 64),
                                .1655*_engine.window().getSize().y + (_level.get_location_matrix().shape()[1] * 64));
    }
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
