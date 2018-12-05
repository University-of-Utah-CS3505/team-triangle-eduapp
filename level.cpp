#include "level.h"
#include <boost/foreach.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>
#include <iostream>
namespace pt = boost::property_tree;

level::level(int level_index) {

    auto root = pt::ptree();
    pt::read_json("../team-triangle-eduapp/levels/levels.json", root);
    for (pt::ptree::value_type& level : root.get_child("levels")) {
        auto level_path = level.second.data();
        levels_master_list.emplace_back(level_path);
    }
    load_new_level(level_index);
}
sf::Texture level::get_preview() {
    // TODO
    sf::Texture texture;
    return texture;
}
sf::Texture level::get_full_texture() {
    // TODO
    sf::Texture texture;
    return texture;
}

sf::Sprite level::get_tile_sprite() {
    sf::Sprite texture;
    return texture;
}
tile level::get_location_tile_def(int x, int y) {
    int tile_loc = location_matrix[x][y];
    return tile(tile_loc,
                type_defs[tile_loc].first,
                type_defs[tile_loc].second);
}

void level::save_level() {
    // TODO, find out if nessesary
}
void level::load_new_level(int level) {
    location_matrix.resize(boost::extents[0][0]); // Clear matrix, valid
                                                  // according to documentation.
    type_defs.clear();

    auto texture = sf::Texture{};
    auto root = pt::ptree();
    auto level_path = levels_master_list[level];
    pt::read_json("../team-triangle-eduapp/levels" + level_path, root);

    // Get tile defs in order to build tiles when getting values
    for (pt::ptree::value_type& def : root.get_child("tiledefs")) {
        std::string img = def.second.get<std::string>("img");
        std::string type = def.second.get<std::string>("type");
        type_defs.push_back(std::make_pair(img, type));
    }

    // Get tile values
    auto x = 0;
    auto size = root.get_child("tiles").size();
    location_matrix.resize(boost::extents[size][size]);
    for (pt::ptree::value_type& row : root.get_child("tiles")) {
        auto y = 0;
        for (pt::ptree::value_type& tile : row.second) {
            std::cout << "coor: " << x << " " << y
                      << " -- val: " << tile.second.get_value<std::string>()
                      << " -- typedef: "
                      << type_defs[tile.second.get_value<int>()].second << " "
                      << type_defs[tile.second.get_value<int>()].first
                      << std::endl;
            location_matrix[x][y] = tile.second.get_value<int>();
            y++;
        }
        x++;
    }
}

boost::multi_array<int,2> level::get_location_matrix(){return location_matrix;};
