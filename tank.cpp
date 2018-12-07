#include "tank.h"
#include <cassert>
#include <cmath>
#include <QDebug>

tank::tank(engine& eng, sf::Sprite sprite, sf::Sprite turret, sf::Sprite bullet)
    : _engine(eng), _sprite(sprite), _turret(turret),
      _bullet(eng, bullet) {
    _sprite.setOrigin(19,19);
    _turret.setOrigin(6, 5);
    _sprite.setPosition(32,32);
    _turret.setPosition(32,32);
    _bullet.set_location(sf::Vector2f(32,32));
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
    if (++_progress <= 64) {
        switch ((int)t._sprite.getRotation()) {
        case (0):
            t._sprite.move(0, direction*1);
            t._turret.move(0, direction*1);
            t._bullet.move(0, direction*1);
            break;
        case (90):
            t._sprite.move(direction*-1, 0);
            t._turret.move(direction*-1, 0);
            t._bullet.move(direction*-1, 0);
            break;
        case (180):
            t._sprite.move(0, direction*-1);
            t._turret.move(0, direction*-1);
            t._bullet.move(0, direction*-1);
            break;
        case (270):
            t._sprite.move(direction*1, 0);
            t._turret.move(direction*1, 0);
            t._bullet.move(direction*1, 0);
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
    _end_angle = (int)_end_angle%360;
    if(_end_angle < 0)
        _end_angle = _end_angle + 360;

}

bool tank::rot_turret::update(tank& t) {
    int actual_end_angle = abs(((int)(_end_angle-t._sprite.getRotation())%360));
    if(actual_end_angle == t._turret.getRotation()){
        return true;
    }

    int offset = actual_end_angle-t._turret.getRotation();
    if ((offset < 179 && offset > 0) || offset <= -180) {
        t._turret.rotate(1);
    } else {
        if (offset >= 180 || (offset > -179 && offset < 0)) {
            t._turret.rotate(-1);
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

tank::shoot::shoot() {}

bool tank::shoot::update(tank& t) {
    t._bullet.set_rotation(t._turret.getRotation());

    t._bullet.set_direction(std::cos((t._turret.getRotation()+90) * M_PI / 180.0), std::sin((t._turret.getRotation()+90)* M_PI / 180.0));
    if(t._bullet.update()){
        t._bullet.set_location(sf::Vector2f(t._sprite.getPosition()));
        return true;
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

sf::Vector2f tank::get_bullet_pos()
{
    return sf::Vector2f(_bullet.get_location());
}

void tank::bullet_hit()
{
    _to_run = std::make_unique<tank::shoot>();
    _bullet.show_explosion();
}

void tank::set_offset(int x, int y) {
    _sprite.move(x, y);
    _turret.move(x, y);
    _bullet.move(x, y);
}

void tank::draw(sf::RenderTarget& target, sf::RenderStates) const {
    target.draw(_bullet);
    target.draw(_sprite);
    target.draw(_turret);
}
