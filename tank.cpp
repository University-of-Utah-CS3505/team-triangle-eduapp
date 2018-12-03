#include "tank.h"

tank::tank(engine& eng, sf::Sprite sprite, sf::Sprite turret) : _engine(eng), _sprite(sprite), _turret(turret){}


tank::~tank() = default;

tank::state::~state() = default;

tank::rotate::rotate(bool is_right) : _is_right(is_right), _progress(0) {}

void tank::rotate::update(tank& t) {
    if (++_progress < 9) {
        t._sprite.rotate(_is_right ? 10 : -10);
        t._turret.rotate(_is_right ? 10 : -10);
    } else {
        t.run_state(nullptr);
    }

    int current_rotation = t._turret.getRotation();
    if (current_rotation >= 360) {
        t._turret.setRotation(current_rotation % 360);
    } else {
        if (current_rotation < 0)
            t._turret.setRotation(current_rotation + 360);
    }

    current_rotation = t._sprite.getRotation();
    if (current_rotation >= 360) {
        t._sprite.setRotation(current_rotation % 360);
    } else {
        if (t._sprite.getRotation() < 0)
            t._sprite.setRotation(current_rotation + 360);
    }
};

tank::move::move(bool is_forward) : _is_forward(is_forward), _progress(0) {
}

void tank::move::update(tank& t) {
    if (++_progress < 32) {
        switch((int)t._sprite.getRotation()){
        case (0 || 360):
            t._sprite.move(0,1);
            t._turret.move(0,1);
            break;
        case (90):
            t._sprite.move(-1,0);
            t._turret.move(-1,0);
            break;
        case (180):
            t._sprite.move(0,-1);
            t._turret.move(0,-1);
            break;
        case (270):
            t._sprite.move(1,0);
            t._turret.move(1,0);
            break;
        default:
            break;
        }
    } else {
        t.run_state(nullptr);
    }
}

tank::rot_turret::rot_turret(float angle) : _end_angle(angle) {}

void tank::rot_turret::update(tank& t) {
    if (_end_angle < t._turret.getRotation()){
        t._turret.rotate(-1);
    } else {
        if (_end_angle > t._turret.getRotation()){
            t._turret.rotate(1);
        } else {
            t.run_state(nullptr);
        }
    }

    int current_rotation = t._turret.getRotation();
    if (current_rotation >= 360) {
        t._turret.setRotation(current_rotation % 360);
    } else {
        if (current_rotation < 0)
            t._turret.setRotation(current_rotation + 360);
    }
}

void tank::run_state(std::unique_ptr<state> to_run) {}

bool tank::update() {
        if(_to_run){
            _to_run->update(*this);
            return false;
        }
        return true;
}
