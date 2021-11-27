#include "Level.h"
#include "constants.h"
#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include <iostream>
#include <SFML/Graphics.hpp>


Level::Level(int id_):
    id(id_)
{
    isCompleted = false;

    std::ifstream file;
    std::string line;
    std::string val;

    // load tiles
    file.open("levels/" + std::to_string(id) + "/map.csv");
    while (std::getline(file, line)) {
        std::vector<int> v;                 
        std::stringstream s(line);         
        while (getline(s, val, ','))      
            v.push_back(std::stoi(val));  
        map.push_back(v);                
    }
    file.close();

    // load sprites for tiles
    texture.loadFromFile("sprites/tiles.png");
    sprite.setTexture(texture);

    int textureX = 0;
    int textureY = 0;

    for (int row = 0; row < TILES_Y; row++) {
        for (int col = 0; col < TILES_X; col++) {
            if (map.at(row).at(col) > 0) {
                textureX = (map.at(row).at(col) % TILESET_TILES) * TILE_SIZE;
                textureY = (map.at(row).at(col) / TILESET_TILES) * TILE_SIZE;

                sprite.setTextureRect(sf::IntRect(textureX, textureY, TILE_SIZE, TILE_SIZE));
                sprite.setPosition(col * TILE_SIZE, row * TILE_SIZE);
                sprite_map.push_back(sprite);
            }
        }
    }

    // load ground rectangles
    file.open("levels/" + std::to_string(id) + "/ground.csv");
    while (std::getline(file, line))
    {
        int x = 0;
        int y = 0;
        int w = 0;
        int h = 0;

        std::stringstream iss(line);

        for (int i = 1; i < 5; ++i)
        {
            std::getline(iss, val, ',');

            std::stringstream convertor(val);
            switch (i) {
            case 1:
                convertor >> x;
                break;
            case 2:
                convertor >> y;
                break;
            case 3:
                convertor >> w;
            case 4:
                convertor >> h;
            }
        }

        groundRects.push_back(sf::FloatRect(x, y, w, h));
    }
    file.close();

    // load spike rectangles
    file.open("levels/" + std::to_string(id) + "/spikes.csv");
    while (std::getline(file, line))
    {
        int x = 0;
        int y = 0;
        int w = 0;
        int h = 0;

        std::stringstream iss(line);

        for (int i = 1; i < 5; ++i)
        {
            std::getline(iss, val, ',');

            std::stringstream convertor(val);
            switch (i) {
            case 1:
                convertor >> x;
                break;
            case 2:
                convertor >> y;
                break;
            case 3:
                convertor >> w;
            case 4:
                convertor >> h;
            }
        }

        spikeRects.push_back(sf::FloatRect(x, y, w, h));
    }

    file.close();
}

void Level::draw(sf::RenderWindow& window) {
    std::vector<sf::Sprite>::iterator it;
    for (it = sprite_map.begin(); it != sprite_map.end(); ++it) {
        window.draw(*it);
    }
}