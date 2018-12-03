#ifndef TANK_H
#define TANK_H

#include "engine.h"
#include <SFML/Graphics.hpp>
#include <atomic>
#include <condition_variable>
#include <functional>
#include <stack>
#include <string>

class gameplay;

class tank : public sf::Drawable {
public:
    tank(engine&, sf::Sprite, sf::Sprite);
    virtual ~tank() override;

    class state {
    public:
        friend class tank;
        virtual ~state();

    private:
        virtual void update(tank&) = 0;
    };

    class rotate : public state {
    public:
        rotate(bool is_right);

    private:
        void update(tank&) override;
        bool _is_right;
        int _progress;
    };

    class move : public state {
    public:
        move(bool is_forward);

    private:
        void update(tank&) override;
        bool _is_forward;
        int _progress;
    };

    class rot_turret : public state {
    public:
        rot_turret(float angle);

    private:
        void update(tank&) override;
        bool _end_angle;
    };

    class shoot : public state {
    public:
        shoot();

    private:
        void update(tank&) override;
    };

    void run_state(std::unique_ptr<state>);

    bool update();

    void wait_until_idle();

private:
    engine& _engine;

    sf::Sprite _sprite;
    sf::Sprite _turret;

    std::mutex _to_run_mutex;
    std::unique_ptr<state> _to_run;

    std::condition_variable _fin_cv;

    //void draw(sf::RenderTarget&, sf::RenderStates) const override;
};

#endif // TANK_H
