#ifndef BULLET_H
#define BULLET_H

#include <SFML/Graphics.hpp>
#include "engine.h"


class bullet : public sf::Drawable {
public:
     bullet(engine&, sf::Sprite);
     virtual ~bullet() override;
     bool update();
     void set_location(sf::Vector2f);
     void move(int, int);
     void set_direction(float, float);
     void set_rotation(float);
     void set_bounds(int, int, int, int);
     sf::Vector2f get_location();
     bool show_explosion();
private:
     sf::Sprite _sprite;
     sf::Vector2f _direction;
     sf::Vector2i _upper_bounds;
     sf::Vector2i _lower_bounds;
     std::vector<sf::Sprite*> _explosion;
     bool _show_explosion;
     int _progress;
     void draw(sf::RenderTarget&, sf::RenderStates) const override;
};

#endif // BULLET_H
