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

#define RETURN_KEY 13
#define BACKSPACE_KEY 8
// Arrow keys are not heard by handle_keyboard
#define ARROW_L_KEY 1
#define ARROW_R_KEY 2
#define ARROW_D_KEY 3
#define ARROW_U_KEY 4

class gameplay : public game_state {
public:
    gameplay(engine& window, int level);
    std::unique_ptr<game_state> update() override;

private:
    bool handle_mouse(sf::Event);
    bool _handle_text(sf::Event);
    bool _handle_keyboard(sf::Event);
    bool _run_tanks();
    bool _load_level(int);
    textedit _editor;
    engine& _engine;
    std::vector<tile*> _tiles;
    std::vector<std::unique_ptr<tank>> _tanks;
    level _level;
    int _current_level;
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
    // TODO some structure to handle the tile (boost::multi_array or something,
    // maybe have a definition mapping ints to tiles and their properties
    // elsewhere - something close to the flyweight pattern)
    // do we want to split this between a 'simulate' and an 'edit' state?
    // gameplay can have sub-states instead - nothing prevents that
    // might be better because the tile map needs to persist and it's probably
    // better than passing it around a bunch
};

#endif // GAMEPLAY_H
