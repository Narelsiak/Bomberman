#pragma once
#include <SFML/Graphics.hpp>
class Tiles : public sf::Drawable, public sf::Transformable
{
public:
	void load(const std::string& tiles, sf::Vector2u tilSize, int* tilesArr, int width, int height);
	int* getLevel();
	void actu();
private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	sf::VertexArray vertices;
	sf::Texture tileset;
	int w = 0;
	int h = 0;
	int tillsizeX = 0;
	int tillsizeY = 0;
	int level[651];
};

