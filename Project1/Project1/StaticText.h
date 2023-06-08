#pragma once
#include <SFML/Graphics.hpp>
#include <string>
class StaticText
{
public:
	//StaticText(sf::String, sf::Color, const char[100], sf::Vector2u, sf::Vector2u, unsigned int = 30);
	void setParametr(sf::Font *, sf::Color, const char[100], sf::Vector2u, sf::Vector2u, unsigned int = 30);
	sf::Text getText();
	sf::Text* getTextP();
	void setNewString(sf::String);
private:
	sf::Text text;
	sf::Font font;
	sf::String fontLoc = "Fonts/OpenSans-Light.ttf";
};

