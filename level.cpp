#include "level.h"
#include "boost/python.hpp"
#include "Python.h"
#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>

namespace pt = boost::property_tree;

level::level(std::string file) : _level_path(file)
{

}
