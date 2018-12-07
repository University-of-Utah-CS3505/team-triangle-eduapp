#ifndef LEVEL_H
#define LEVEL_H

#include "tile.h"
#include "object_def.h"
#include <SFML/Graphics.hpp>
#include <boost/multi_array.hpp>
class level {
public:
    level(int level_index); // determines the level we want to load, loads tiledef,
    sf::Texture get_preview(); // for use in level select
    sf::Texture get_full_texture(); // for use in gameplay, backround of the tiles.
    sf::Sprite get_tile_sprite(); // either this or get full texture? prolly not bother...
    tile get_location_tile_def(int x, int y);
    void save_level(); // do we need this? We are just saving the text editor commands?
    void load_new_level(int level); // UNLOADS CURRENT LEVEL, reloads from master list
    boost::multi_array<int,2> get_location_matrix();
    std::vector<object_def*> get_objects();
    std::string _level_name;

private:
    int tankstart[2]; // x then y
    boost::multi_array<int, 2> location_matrix;
    sf::Texture preview;
    std::vector<tile*> _tiles;
    std::vector<object_def*> _objects;
    std::vector<std::string> levels_master_list;
    std::vector<std::pair<std::string, std::string>> type_defs;
};

#endif // LEVEL_H
