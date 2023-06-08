#pragma once
#include "Menu.h"
#include "DynamicTexture.h"
class Instructions : public Menu
{
public:
	void startI(sf::RenderWindow *);
protected:
	bool create = 0;
	void createPanel(sf::RenderWindow *);
	void draw(sf::RenderWindow*);
	vector <StaticText> textV;
	vector <DynamicTexture> textureV;
private:
	sf::String fontLoc = "Fonts/OpenSans-Light.ttf";
	sf::Font font2;

	sf::Texture textureBoost;
};

