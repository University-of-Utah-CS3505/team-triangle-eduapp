#ifndef TILE_SET_GENERATOR_H
#define TILE_SET_GENERATOR_H
#include <boost/multi_array.hpp>
#include <SFML/Graphics.hpp>
class tile_set_generator
{
public:
    tile_set_generator();
    sf::Texture tile_set_generate_level(int Level);
private:
    //boost::multi_array<int, 1> levels;
    std::vector<std::string> levels;
};

#endif // TILE_SET_GENERATOR_H
