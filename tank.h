#ifndef TANK_H
#define TANK_H

#include "engine.h"
#include <SFML/Graphics.hpp>
#include <atomic>
#include <condition_variable>
#include <functional>
#include <stack>
#include <string>

class tank : public sf::Drawable {
public:
    tank(engine& eng);
    virtual ~tank() override;

    class state {
    public:
        virtual ~state();

    private:
        virtual void update(tank&);
    };

    class rotate : public state {
    public:
        rotate(bool is_right);

    private:
        void update(tank&) override;
    };

    class move : public state {
    public:
        move(bool is_forward);

    private:
        void update(tank&) override;
    };

    class rot_turret : public state {
    public:
        rot_turret(float angle);

    private:
        void update(tank&) override;
    };

    class shoot : public state {
    public:
        shoot();

    private:
        void update(tank&) override;
    };

    void run_state(std::unique_ptr<state>);

    void wait_until_idle();

private:
    engine& _engine;

    sf::Sprite _sprite;
    sf::Texture _texture;

    std::mutex _to_run_mutex;
    std::unique_ptr<state> _to_run;

    std::condition_variable _fin_cv;

    int _x, _y;

    void draw(sf::RenderTarget&, sf::RenderStates) const override;
};

#endif // TANK_H
