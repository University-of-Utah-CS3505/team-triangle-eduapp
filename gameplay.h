#ifndef GAMEPLAY_H
#define GAMEPLAY_H

#include "engine.h"
#include "game_state.h"
#include "textedit.h"
#include "tile.h"
#include <SFML/Graphics.hpp>

class gameplay : public game_state {
public:
    gameplay(engine& window);

    int move_tank(char dir, int current_move);
    std::unique_ptr<game_state> update() override;

private:
    textedit _editor;
    engine& _engine;
    sf::Texture _texture;
    std::vector<tile*> _tiles;
    sf::Sprite _tank;
    int _current_move;
    // TODO some structure to handle the tile (boost::multi_array or something,
    // maybe have a definition mapping ints to tiles and their properties
    // elsewhere - something close to the flyweight pattern)
    // do we want to split this between a 'simulate' and an 'edit' state?
    // gameplay can have sub-states instead - nothing prevents that
    // might be better because the tile map needs to persist and it's probably
    // better than passing it around a bunch
};

#endif // GAMEPLAY_H
