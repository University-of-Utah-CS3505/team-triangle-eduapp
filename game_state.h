#ifndef GAME_STATE_H
#define GAME_STATE_H

#include <memory>

class game_state {
public:
    virtual ~game_state() = default;

    virtual void update(std::unique_ptr<game_state>&) = 0;
};

#endif // GAME_STATE_H
