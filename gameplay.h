#ifndef GAMEPLAY_H
#define GAMEPLAY_H

#include "game_state.h"
#include "textedit.h"

class gameplay : public game_state {
public:
    gameplay();

    void update(std::unique_ptr<game_state>&) override;

private:
    textedit _editor;
    // TODO some structure to handle the tile (boost::multi_array or something,
    // maybe have a definition mapping ints to tiles and their properties
    // elsewhere - something close to the flyweight pattern)
    // do we want to split this between a 'simulate' and an 'edit' state?
    // gameplay can have sub-states instead - nothing prevents that
    // might be better because the tile map needs to persist and it's probably
    // better than passing it around a bunch
};

#endif // GAMEPLAY_H
