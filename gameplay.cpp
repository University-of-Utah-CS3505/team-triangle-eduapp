#include "gameplay.h"
#include "tile.h"
#include <vector>
gameplay::gameplay(sf::RenderWindow& window) : _editor{12, 3, 3}, _window{window},
                                               _tank(_texture,sf::IntRect(432,48,42,46)){
    _texture.loadFromFile("../team-triangle-eduapp/assets/Tanks/Spritesheet/allSprites_default.png");

    _tiles.emplace_back(new tile(0, "../team-triangle-eduapp/assets/Tanks/PNG/DefaultSize/tileGrass1.png", "grass"));
    _tiles.emplace_back(new tile(1, "../team-triangle-eduapp/assets/Tanks/PNG/DefaultSize/tileGrass_roadNorth.png", "road"));
    _tiles.emplace_back(new tile(2, "../team-triangle-eduapp/assets/Tanks/PNG/DefaultSize/tileGrass_roadEast.png", "road"));
    _tiles.emplace_back(new tile(3, "../team-triangle-eduapp/assets/Tanks/PNG/DefaultSize/tileGrass_roadCornerLL.png", "road"));
    _tiles.emplace_back(new tile(4, "../team-triangle-eduapp/assets/Tanks/PNG/DefaultSize/tileGrass_roadCornerLR.png", "road"));
    _tiles.emplace_back(new tile(5, "../team-triangle-eduapp/assets/Tanks/PNG/DefaultSize/tileGrass_roadCornerUL.png", "road"));
    _tiles.emplace_back(new tile(6, "../team-triangle-eduapp/assets/Tanks/PNG/DefaultSize/tileGrass_roadCornerUR.png", "road"));

}

void gameplay::update(std::unique_ptr<game_state>&) {


    int tile_height = 5;
    int tile_width = 5;
    int tile_map[5][5] = {{1,0,0,0,0},
                          {1,0,0,0,0},
                          {6,2,2,3,0},
                          {0,0,0,1,0},
                          {0,0,0,1,0}};

    _window.clear();
    for(int i = 0; i < tile_height; i++){
        for(int j = 0; j < tile_width; j++){
            _tiles[tile_map[i][j]]->set_sprite_position(j*64, i*64);
            _window.draw(_tiles[tile_map[i][j]]->get_sprite());
        }
    }

    //tank.setPosition(sf::Mouse::getPosition(_window).x, sf::Mouse::getPosition(_window).y);
    _tank.setPosition((_tank.getPosition().x), (_tank.getPosition().y)+5);
    _window.draw(_tank);
    _window.display();
}
