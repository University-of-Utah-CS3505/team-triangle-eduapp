#include "tile_set_generator.h"
#include <boost/foreach.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>
#include <iostream>

namespace pt = boost::property_tree;

tile_set_generator::tile_set_generator() {
    // _levels = boost::extents[]
    auto root = pt::ptree();
    pt::read_json("../team-triangle-eduapp/levels/levels.json", root);
    for (pt::ptree::value_type& level : root.get_child("levels")) {
        auto level_path = level.second.data();
        _levels.emplace_back(level_path);
    }
}

// **Seems like texture is not the right return here, maybe pass in a
// tank and tiles map and set, void return**

sf::Texture tile_set_generator::tile_set_generate_level(int level) {
    auto texture = sf::Texture {};
    auto root = pt::ptree();
    std::vector< std::pair<std::string, std::string> > type_defs;
    auto level_path = _levels[level];
    pt::read_json("../team-triangle-eduapp/levels" + level_path, root);

    // Get tile defs in order to build tiles when getting values
    for (pt::ptree::value_type& def : root.get_child("tiledefs")) {
        std::string img = def.second.get<std::string>("img");
        std::string type = def.second.get<std::string>("type");
        type_defs.push_back(std::make_pair(img, type));
    }

    // Get tile values
    auto x = 0;
    for (pt::ptree::value_type& row : root.get_child("tiles")) {
        auto y = 0;
        for (pt::ptree::value_type& tile : row.second) {
            std::cout << "coor: " << x << " " << y << " -- val: "
                      << tile.second.get_value<int>() << " -- typedef: "
                      << type_defs[tile.second.get_value<int>()].second << " "
                      << type_defs[tile.second.get_value<int>()].first
                      << std::endl;
            y++;
        }
        x++;
    }

    // Place objects

    return texture;



//    long bounds = (long)root.get_child("tiles").size();
//    std::cout << bounds << std::endl;
//    boost::multi_array<int, 2> boost_array_level(
//            boost::extents[bounds][bounds]);
//    for (auto& item : root.get_child("tiles")) {
//        std::cout << item.second.get_value<std::string>() << std::endl;
//    }
}
