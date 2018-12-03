#include "tank.h"
#include <cassert>

tank::tank(engine& eng, sf::Sprite sprite, sf::Sprite turret)
    : _engine(eng), _sprite(sprite), _turret(turret) {
    _sprite.setOrigin(19,19);
    _turret.setOrigin(6, 5);
    _sprite.setPosition(32,32);
    _turret.setPosition(32,32);
}

tank::~tank() = default;

tank::state::~state() = default;

tank::rotate::rotate(bool is_right) : _is_right(is_right), _progress(0) {}

bool tank::rotate::update(tank& t) {
    if (++_progress <= 45) {
        t._sprite.rotate(_is_right ? 2 : -2);
        t._turret.rotate(_is_right ? 2 : -2);
    } else {
        return true;
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
    return false;
};

tank::move::move(bool is_forward) : _is_forward(is_forward), _progress(0) {}

bool tank::move::update(tank& t) {
    int direction = 1;
    if(!_is_forward)
        direction = -1;
    if (++_progress < 64) {
        switch ((int)t._sprite.getRotation()) {
        case (0):
            t._sprite.move(0, direction*1);
            t._turret.move(0, direction*1);
            break;
        case (90):
            t._sprite.move(direction*-1, 0);
            t._turret.move(direction*-1, 0);
            break;
        case (180):
            t._sprite.move(0, direction*-1);
            t._turret.move(0, direction*-1);
            break;
        case (270):
            t._sprite.move(direction*1, 0);
            t._turret.move(direction*1, 0);
            break;
        default:
            break;
        }
    } else {
        return true;
    }
    return false;
}

tank::rot_turret::rot_turret(float angle) : _end_angle(angle) {
    _end_angle = (int)_end_angle;
}

bool tank::rot_turret::update(tank& t) {
    int actual_end_angle = abs(((int)(_end_angle-t._sprite.getRotation())%360));
    if (actual_end_angle > t._turret.getRotation()) {
        t._turret.rotate(1);
    } else {
        if (actual_end_angle < t._turret.getRotation()) {
            t._turret.rotate(-1);
        } else {
            return true;
        }
    }

    int current_rotation = t._turret.getRotation();
    if (current_rotation >= 360) {
        t._turret.setRotation(current_rotation % 360);
    } else {
        if (current_rotation < 0)
            t._turret.setRotation(current_rotation + 360);
    }
    return false;
}

void tank::run_state(std::unique_ptr<state> state) {
    assert(state != nullptr);
    auto lock = std::lock_guard(_mutex);
    _to_run = std::move(state);
}

void tank::update() {
    auto lock = std::unique_lock(_mutex);
    if (_to_run && _to_run->update(*this)) {
        _to_run = nullptr;
        lock.unlock();
        _fin_cv.notify_all();
    }
}

void tank::wait_until_idle() {
    auto lock = std::unique_lock(_mutex);
    _fin_cv.wait(lock, [this] { return _to_run == nullptr; });
}

void tank::draw(sf::RenderTarget& target, sf::RenderStates) const {
    target.draw(_sprite);
    target.draw(_turret);
}
