#include "level.h"
#include <boost/foreach.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>
#include <iostream>
namespace pt = boost::property_tree;

Level::Level(int level)
{
    auto root = pt::ptree();
    pt::read_json("../team-triangle-eduapp/levels/levels.json", root);
    for (pt::ptree::value_type& level : root.get_child("levels")) {
        auto level_path = level.second.data();
        levels_master_list.emplace_back(level_path);
    }

}
sf::Texture Level::get_preview()
{

}
sf::Texture Level:: get_full_texture()
{
    }

sf::Sprite Level::get_tile_sprite(){

}
tile Level::get_location_tile_def(int x, int y){

}

void Level::save_level(){

}
void Level::load_new_level(){

    }
}
