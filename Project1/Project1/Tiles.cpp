#include "Tiles.h"
#include <iostream>
void Tiles::load(const std::string& tiles, sf::Vector2u tilSize, int* tilesArr, int width, int height)
{
	if (!tileset.loadFromFile(tiles)) {
		//blad czytania.
	}
    vertices.setPrimitiveType(sf::Quads);
    vertices.resize(width * height * 4);
    w = width;
    h = height;
    tillsizeX = tilSize.x;
    tillsizeY = tilSize.y;
    
    for (int i = 0; i < width; i++)
        for (int j = 0; j < height; j++)
        {
            level[i + j * width] = tilesArr[i + j * width];
            int tileNumber = tilesArr[i + j * width];

            int tu = tileNumber % (tileset.getSize().x / tilSize.x);
            int tv = tileNumber / (tileset.getSize().x / tilSize.x);

            sf::Vertex* quad = &vertices[(i + j * width) * 4];
            
            quad[0].position = sf::Vector2f(i * tilSize.x, j * tilSize.y + 64.f);
            quad[1].position = sf::Vector2f((i + 1) * tilSize.x, j * tilSize.y + 64.f);
            quad[2].position = sf::Vector2f((i + 1) * tilSize.x, (j + 1) * tilSize.y + 64.f);
            quad[3].position = sf::Vector2f(i * tilSize.x, (j + 1) * tilSize.y + 64.f);   

            quad[0].texCoords = sf::Vector2f(tu * tilSize.x, tv * tilSize.y);
            quad[1].texCoords = sf::Vector2f((tu + 1) * tilSize.x, tv * tilSize.y);
            quad[2].texCoords = sf::Vector2f((tu + 1) * tilSize.x, (tv + 1) * tilSize.y);
            quad[3].texCoords = sf::Vector2f(tu * tilSize.x, (tv + 1) * tilSize.y); 
        }
}

int* Tiles::getLevel()
{
    return level;
}

void Tiles::actu()//okej jest
{
    for (int i = 0; i < w; i++)
        for (int j = 0; j < h; j++)
        {
            int tileNumber = level[i + j * w];
            int tu = tileNumber % (tileset.getSize().x / tillsizeX);
            int tv = tileNumber / (tileset.getSize().x / tillsizeX);

            sf::Vertex* quad = &vertices[(i + j * (int)w) * 4];

            if (quad[0].texCoords.x == tu * tillsizeX && quad[0].texCoords.y == tv * tillsizeY){
                //std::cout << "ZMIENIAM:  x: " << tileNumber % 31 << " y: " << tileNumber / 31 << std::endl;
                continue;
            }
           // std::cout << "ZMIENIAM:  x: " << i << " y: " << j << std::endl;
                quad[0].texCoords = sf::Vector2f(tu * tillsizeX, tv * tillsizeY);
                quad[1].texCoords = sf::Vector2f((tu + 1) * tillsizeX, tv * tillsizeY);
                quad[2].texCoords = sf::Vector2f((tu + 1) * tillsizeX, (tv + 1) * tillsizeY);
                quad[3].texCoords = sf::Vector2f(tu * tillsizeX, (tv + 1) * tillsizeY);               
            if (tileNumber == 5) {
                quad[0].color = sf::Color::Red;
                quad[1].color = sf::Color::Red;
                quad[2].color = sf::Color::Red;
                quad[3].color = sf::Color::Red;
            }
        }
}

void Tiles::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();

    states.texture = &tileset;

    target.draw(vertices, states);
}
