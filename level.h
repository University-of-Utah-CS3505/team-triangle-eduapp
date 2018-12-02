#ifndef LEVEL_H
#define LEVEL_H

#include <string>
#include "tile.h"

class level
{
public:
  level(std::string);
  level  next_level(std::string);


private:
    std::string _level_path;
    std::vector<tile*> _tiles;
};

#endif // LEVEL_H
