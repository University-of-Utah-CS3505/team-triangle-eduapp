#include "gameplay.h"
#include "tile.h"
#include <vector>
gameplay::gameplay(sf::RenderWindow& window) : _editor{0, 0, 0}, _window{window}{
    _texture.loadFromFile("../team-triangle-eduapp/assets/Tanks/Spritesheet/allSprites_default.png");
}

void gameplay::update(std::unique_ptr<game_state>&) {

    sf::Sprite tank(_texture,sf::IntRect(432,48,42,46));

    int tile_width = 5;
    int tile_height = 5;
    int tile_map [5][5] = {{1,0,0,0,0},
                          {1,0,0,0,0},
                          {6,2,2,3,0},
                          {0,0,0,1,0},
                          {0,0,0,1,0}};

    std::vector<tile> tiles;
    tile grass(0, "../team-triangle-eduapp/assets/Tanks/PNG/DefaultSize/tileGrass1.png", "grass");
    tile vert_road(1, "../team-triangle-eduapp/assets/Tanks/PNG/DefaultSize/tileGrass_roadNorth.png", "road");
    tile hori_road(2, "../team-triangle-eduapp/assets/Tanks/PNG/DefaultSize/tileGrass_roadEast.png", "road");
    tile LL_road(3, "../team-triangle-eduapp/assets/Tanks/PNG/DefaultSize/tileGrass_roadCornerLL.png", "road");
    tile LR_road(4, "../team-triangle-eduapp/assets/Tanks/PNG/DefaultSize/tileGrass_roadCornerLR.png", "road");
    tile UL_road(5, "../team-triangle-eduapp/assets/Tanks/PNG/DefaultSize/tileGrass_roadCornerUL.png", "road");
    tile UR_road(6, "../team-triangle-eduapp/assets/Tanks/PNG/DefaultSize/tileGrass_roadCornerUR.png", "road");
    tiles.push_back(grass);
    tiles.push_back(vert_road);
    tiles.push_back(hori_road);
    tiles.push_back(LL_road);
    tiles.push_back(LR_road);
    tiles.push_back(UL_road);
    tiles.push_back(UR_road);


    _window.clear();
    for(int i = 0; i < tile_height; i++){
        for(int j = 0; j < tile_width; j++){
            tiles[tile_map[i][j]].set_sprite_position(j*64, i*64);
            _window.draw(tiles[tile_map[i][j]].get_sprite());
        }
    }

    tank.setPosition(sf::Mouse::getPosition(_window).x, sf::Mouse::getPosition(_window).y);
    _window.draw(tank);
    _window.display();
}
