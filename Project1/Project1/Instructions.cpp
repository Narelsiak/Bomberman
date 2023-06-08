#include "Instructions.h"
#include <iostream>
void Instructions::startI(sf::RenderWindow *window)
{
	if (create != 1) {
		createBack();
		createPanel(window);
		create = 1;
	}
	draw(window);
}

void Instructions::draw(sf::RenderWindow *window)
{
	for (int i = 0; i < tablica.size(); i++) {
		window->draw(tablica[i].getSprite());
	}
	for(int i = 0; i < textV.size(); i++) {
		window->draw(textV[i].getText());
	}
	for (int i = 0; i < textureV.size(); i++) {
		window->draw(textureV[i].getSprite());
	}
}

void Instructions::createPanel(sf::RenderWindow * window)
{
	font2.loadFromFile(fontLoc);
	if (!textureBoost.loadFromFile("Map/boost.png")) {
	}
	textV.push_back(StaticText());
	textV[0].setParametr(&font2, sf::Color::White, "Do poruszania w grze uzywamy klawiatury. \nPolozenie bomby za pomoca spacji.", sf::Vector2u(500, 10), sf::Vector2u(window->getPosition().x, window->getPosition().y), 20);
	textV.push_back(StaticText());
	textV[1].setParametr(&font2, sf::Color::White, "Celem gry jest pokonanie przeciwnikow, przejscie do nastepnego lvla, bla,bla", sf::Vector2u(500,60), sf::Vector2u(window->getPosition().x, window->getPosition().y), 20);
	textV.push_back(StaticText());
	textV[2].setParametr(&font2, sf::Color::White, "W grze mozna zbierac boosty, ich lista: ", sf::Vector2u(500, 90), sf::Vector2u(window->getPosition().x, window->getPosition().y), 20);

	textureV.push_back(DynamicTexture());
	textureV[0].setNew(&textureBoost, 500, 120);
	textureV[0].editRectangle(0, 0, 32, 32);
	textV.push_back(StaticText());
	textV[3].setParametr(&font2, sf::Color::White, " - dodatkowa bomba  ", sf::Vector2u(540, 126), sf::Vector2u(window->getPosition().x, window->getPosition().y), 20);

	textureV.push_back(DynamicTexture());
	textureV[1].setNew(&textureBoost, 500, 160);
	textureV[1].editRectangle(32, 0, 32, 32);
	textV.push_back(StaticText());
	textV[4].setParametr(&font2, sf::Color::White, " - szybsze chodzenie ", sf::Vector2u(540, 166), sf::Vector2u(window->getPosition().x, window->getPosition().y), 20);

	textureV.push_back(DynamicTexture());
	textureV[2].setNew(&textureBoost, 500, 200);
	textureV[2].editRectangle(64, 0, 32, 32);
	textV.push_back(StaticText());
	textV[5].setParametr(&font2, sf::Color::White, " - bomby nas nie zabijaja ", sf::Vector2u(540, 206), sf::Vector2u(window->getPosition().x, window->getPosition().y), 20);

	textureV.push_back(DynamicTexture());
	textureV[3].setNew(&textureBoost, 500, 240);
	textureV[3].editRectangle(96, 0, 32, 32);
	textV.push_back(StaticText());
	textV[6].setParametr(&font2, sf::Color::White, " - przechodzenie przez scianki ", sf::Vector2u(540, 246), sf::Vector2u(window->getPosition().x, window->getPosition().y), 20);

	textV.push_back(StaticText());
	textV[7].setParametr(&font2, sf::Color::White, "W zaleznosci od wybranego poziomu trudnosci \nzmieniaja sie parametry gry oraz inteligencja\nprzeciwnikow", sf::Vector2u(500, 280), sf::Vector2u(window->getPosition().x, window->getPosition().y), 20);

	textV.push_back(StaticText());
	textV[7].setParametr(&font2, sf::Color::White, "Gre mozna zatrzymac wykorzystujac klawisz 'P'", sf::Vector2u(500, 350), sf::Vector2u(window->getPosition().x, window->getPosition().y), 20);
}
