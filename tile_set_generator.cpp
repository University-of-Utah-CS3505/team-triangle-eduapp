#include "tile_set_generator.h"
//File loads in levels.JSON, then creates levels when requested.
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/foreach.hpp>
#include <iostream>
namespace pt = boost::property_tree;
tile_set_generator::tile_set_generator()
{

//levels = boost::extents[]
auto root = pt::ptree();
pt::read_json("../team-triangle-eduapp/levels/levels.json", root);
for(pt::ptree::value_type &v : root.get_child("levels")){
        std::string s = v.second.data();
        levels.emplace_back(s);

    }
}


sf::Texture tile_set_generator::tile_set_generate_level(int level)
{
    std::string path = levels[level];
    std::cout << path << std::endl;
    auto root = pt::ptree();
    pt::read_json("../team-triangle-eduapp/levels"+path, root);
    long bounds = (long) root.get_child("tiles").size();
    std::cout << bounds << std::endl;
    boost::multi_array<int,2> boost_array_level(boost::extents[bounds][bounds]);
    for(auto& item : root.get_child("tiles")){
        std::cout <<  item.second.get_value<std::string>() << std::endl;

    }

}
