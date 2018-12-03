//DEPRECATED, REPLACED WITH LEVEL.CPP
//DEPRECATED, REPLACED WITH LEVEL.CPP
//DEPRECATED, REPLACED WITH LEVEL.CPP
//DEPRECATED, REPLACED WITH LEVEL.CPP
//DEPRECATED, REPLACED WITH LEVEL.CPP
#ifndef TILE_SET_GENERATOR_H
#define TILE_SET_GENERATOR_H

#include <SFML/Graphics.hpp>
#include <boost/multi_array.hpp>

class tile_set_generator {
public:
    tile_set_generator();
    boost::multi_array<int,2> tile_set_generate_level(int Level);

    sf::Texture generate_texture(boost::multi_array<int,2> boost_array);
private:

    std::vector<std::string> _levels;
};

#endif // TILE_SET_GENERATOR_H
