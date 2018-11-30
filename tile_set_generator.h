#ifndef TILE_SET_GENERATOR_H
#define TILE_SET_GENERATOR_H

#include <SFML/Graphics.hpp>
#include <boost/multi_array.hpp>

class tile_set_generator {
public:
    tile_set_generator();
    sf::Texture tile_set_generate_level(int Level);

private:
    // boost::multi_array<int, 1> _levels;
    std::vector<std::string> _levels;
};

#endif // TILE_SET_GENERATOR_H
