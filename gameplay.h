#ifndef GAMEPLAY_H
#define GAMEPLAY_H

#include "engine.h"
#include "game_state.h"
#include "level.h"
#include "tank.h"
#include "textedit.h"
#include "texteditor/InputController.h"
#include "texteditor/TextDocument.h"
#include "texteditor/TextView.h"
#include "tile.h"
#include <SFML/Graphics.hpp>
#include <atomic>
#include <boost/circular_buffer.hpp>
#include <queue>
#include <thread>

class gameplay : public game_state {
public:
    gameplay(engine& window, int level);
    std::unique_ptr<game_state> update() override;

private:
    bool _handle_mouse(sf::Event);
    bool _handle_text(sf::Event);
    bool _handle_keyboard(sf::Event);
    bool _run_tanks();
    bool _load_level(int);
    void _draw_current_lines(sf::RenderTarget& target);
    textedit _editor;
    engine& _engine;
    std::vector<tile*> _tiles;
    level _level;
    int _current_level;
    bool _level_won;
    event_handle _text_handle;
    std::vector<object_def*> _objects;
    event_handle _pressed_handle;
    event_handle _mouse_click;
    event_handle _click_handle;

    sf::RenderTexture _editor_subtarget;
    TextView _text_view;
    TextDocument _text_doc;
    InputController _input_con;
    std::unique_ptr<game_state> _to_state;
    event_handle _released_handle;


    std::unique_ptr<tank> _tank;
    std::unique_ptr<std::thread> _tank_controller;
    std::atomic<int> _executing_line;
    std::atomic<bool> _kill_sig;

    std::mutex _pyout_mutex;
    std::stringstream _pyout;
    sf::RectangleShape _error_console;
    sf::Font _error_font;
    sf::Text _error_text;
    // TODO some structure to handle the tile (boost::multi_array or something,
    // maybe have a definition mapping ints to tiles and their properties
    // elsewhere - something close to the flyweight pattern)
    // do we want to split this between a 'simulate' and an 'edit' state?
    // gameplay can have sub-states instead - nothing prevents that
    // might be better because the tile map needs to persist and it's probably
    // better than passing it around a bunch

    std::streambuf* _stdoutbuf;
    std::stringstream _stdout;

    boost::circular_buffer<std::string> _stdout_lines;
};

#endif // GAMEPLAY_H
