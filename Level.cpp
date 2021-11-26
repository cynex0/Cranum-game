#include "Level.h"
#include "constants.h"
#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include <iostream>
#include <SFML/Graphics.hpp>


Level::Level(int id) {
    std::ifstream file("levels/" + std::to_string(id) + ".csv");

    for (int row = 0; row < TILES_Y; ++row)
    {
        std::string line;
        std::getline(file, line);
        if (!file.good())
            break;

        std::stringstream iss(line);

        for (int col = 0; col < TILES_X; ++col)
        {
            std::string val;
            std::getline(iss, val, ',');
            if (!iss.good())
                break;

            std::stringstream convertor(val);
            convertor >> map[col][row];
        }
    }
    for (int row = 0; row < TILES_Y; row++){
        for (int col = 0; col < TILES_X; col++){
        }
    }
    getSprites();
}

void Level::getSprites() {
    texture.loadFromFile("sprites/tiles.png");
    sprite.setTexture(texture);

    int textureX = 0;
    int textureY = 0;

    for (int row = 0; row < TILES_X; row++) {
        for (int col = 0; col < TILES_Y; col++) {
            if (map[row][col] > 0) {
                textureX = (map[row][col] % TILESET_TILES) * TILE_SIZE;
                textureY = (map[row][col] / TILESET_TILES) * TILE_SIZE;

                sprite.setTextureRect(sf::IntRect(textureX, textureY, TILE_SIZE, TILE_SIZE));
                sprite.setPosition(row * TILE_SIZE, col * TILE_SIZE);
                sprite_map.push_back(sprite);
            }
        }
    }
}

void Level::draw(sf::RenderWindow& window) {
    std::list<sf::Sprite>::iterator it;
    for (it = sprite_map.begin(); it != sprite_map.end(); ++it) {
        window.draw(*it);
    }
}