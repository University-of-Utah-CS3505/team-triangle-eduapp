#ifndef TANK_H
#define TANK_H

#include "engine.h"
#include "bullet.h"
#include <SFML/Graphics.hpp>
#include <atomic>
#include <condition_variable>
#include <functional>
#include <stack>
#include <string>

class gameplay;

class tank : public sf::Drawable {
public:
    tank(engine&, sf::Sprite, sf::Sprite, sf::Sprite);
    virtual ~tank() override;

    class state {
    public:
        friend class tank;
        virtual ~state();

    private:
        virtual bool update(tank&) = 0;
        friend class tank;
    };

    class rotate : public state {
    public:
        rotate(bool is_right);

    private:
        bool update(tank&) override;
        bool _is_right;
        int _progress;
    };

    class move : public state {
    public:
        move(bool is_forward);

    private:
        bool update(tank&) override;
        bool _is_forward;
        int _progress;
    };

    class rot_turret : public state {
    public:
        rot_turret(float angle);

    private:
        bool update(tank&) override;
        float _end_angle;
    };

    class shoot : public state {
    public:
        shoot();

    private:
        bool update(tank&) override;
    };

    class explode : public state {
    public:
        explode();

    private:
        bool update(tank&) override;
        int _progress;
    };

    void run_state(std::unique_ptr<state>);
    void update();
    void wait_until_idle();
    sf::Vector2f get_bullet_pos();
    sf::Vector2f get_position();
    void bullet_hit();
    void set_offset(int, int);\
    void set_bullet_bounds(int,int,int,int);
    bool is_shooting();
    bool explode();

private:
    engine& _engine;
    sf::Sprite _sprite;
    sf::Sprite _turret;
    std::vector<sf::Sprite*> _explosion;
    bool _explode;
    int _progress;

    bullet _bullet;
    bool _shooting;


    std::mutex _mutex;
    std::unique_lock<std::mutex> _lock;
    std::unique_ptr<state> _to_run;

    std::condition_variable _fin_cv;

    void draw(sf::RenderTarget&, sf::RenderStates) const override;
};

#endif // TANK_H
