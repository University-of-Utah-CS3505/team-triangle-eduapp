#include "level.h"
#include <boost/foreach.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>
#include <iostream>
#include <fstream>
#include <sstream>
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
    _objects.clear();

    _level_inst_path = levels_master_list[level] + "level.txt";
    _level_instructions = get_level_instructions(_level_inst_path);

    auto texture = sf::Texture{};
    auto root = pt::ptree();
    auto level_path = levels_master_list[level];
    pt::read_json("../team-triangle-eduapp/levels" + level_path + "level.json", root);


    for(pt::ptree::value_type& def : root.get_child("objects")) {
        std::string type = def.second.get<std::string>("type");

        std::vector<std::string> pos;
        for (pt::ptree::value_type &p : def.second.get_child("pos")) {
          pos.push_back(p.second.data());
        }

        std::vector<std::string> size;
        for (pt::ptree::value_type &p : def.second.get_child("size")) {
          size.push_back(p.second.data());
        }

        std::string img = def.second.get<std::string>("img");

        _objects.emplace_back(new object_def(img,
                                             type,
                                             sf::Vector2i(std::stoi(pos[0]),std::stoi(pos[1])),
                                             sf::Vector2i(std::stoi(size[0]),std::stoi(size[1]))));

    }

    // Get tile defs in order to build tiles when getting values
    for (pt::ptree::value_type& def : root.get_child("tiledefs")) {
        std::string img = def.second.get<std::string>("img");
        std::string type = def.second.get<std::string>("type");
        type_defs.push_back(std::make_pair(img, type));
    }

    // Get name
    _level_name = root.get<std::string>("name");

    // Get size of map
    auto size_x = 0, size_y = 0;
    auto x = 0;
    for (pt::ptree::value_type& row : root.get_child("tiles")) {
        auto y = 0;
        for (pt::ptree::value_type& tile : row.second) {
            tile.second.get_value<int>();
            y++;
        }
        size_y = y;
        x++;
    }
    size_x = x;
    location_matrix.resize(boost::extents[size_x][size_y]);

    // Get tile values
    x = 0;
    for (pt::ptree::value_type& row : root.get_child("tiles")) {
        auto y = 0;
        for (pt::ptree::value_type& tile : row.second) {
            location_matrix[x][y] = tile.second.get_value<int>();
            y++;
        }
        x++;
    }
}

boost::multi_array<int,2> level::get_location_matrix(){return location_matrix;};

std::string level::get_level_instructions(std::string path){
    std::stringstream result;
    std::ifstream file("../team-triangle-eduapp/levels/"+path);
    result << file.rdbuf();
    return result.str();
}

std::vector<object_def *> level::get_objects()
{
    return _objects;
};

