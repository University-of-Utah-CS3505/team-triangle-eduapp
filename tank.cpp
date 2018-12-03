#include "tank.h"
#include <assert.h>

tank::tank(engine& eng, sf::Sprite sprite, sf::Sprite turret)
    : _engine(eng), _sprite(sprite), _turret(turret) {}

tank::~tank() = default;

tank::state::~state() = default;

tank::rotate::rotate(bool is_right) : _is_right(is_right), _progress(0) {}

bool tank::rotate::update(tank& t) {
    if (++_progress < 9) {
        t._sprite.rotate(_is_right ? 10 : -10);
        t._turret.rotate(_is_right ? 10 : -10);
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
    if (++_progress < 32) {
        switch ((int)t._sprite.getRotation()) {
        case (0 || 360):
            t._sprite.move(0, 2);
            t._turret.move(0, 2);
            break;
        case (90):
            t._sprite.move(-2, 0);
            t._turret.move(-2, 0);
            break;
        case (180):
            t._sprite.move(0, -2);
            t._turret.move(0, -2);
            break;
        case (270):
            t._sprite.move(2, 0);
            t._turret.move(2, 0);
            break;
        default:
            break;
        }
    } else {
        return true;
    }
    return false;
}

tank::rot_turret::rot_turret(float angle) : _end_angle(angle) {}

bool tank::rot_turret::update(tank& t) {
    if (_end_angle < t._turret.getRotation()) {
        t._turret.rotate(-1);
    } else {
        if (_end_angle > t._turret.getRotation()) {
            t._turret.rotate(1);
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
    auto lock = std::lock_guard(_mutex);
    assert(_to_run != nullptr);
    _to_run = std::move(state);
}

void tank::update() {
    auto lock = std::unique_lock(_mutex);
    lock.lock();
    if (_to_run && _to_run->update(*this)) {
        _to_run = nullptr;
        lock.unlock();
        _fin_cv.notify_one();
    }
}

void tank::wait_until_idle() {
    auto lock = std::unique_lock(_mutex);
    _fin_cv.wait(lock);
}

void tank::draw(sf::RenderTarget& target, sf::RenderStates) const {
    target.draw(_sprite);
    target.draw(_turret);
}
