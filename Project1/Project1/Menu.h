#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "StaticTexture.h"
#include "StaticText.h"
#include "Map.h"
using namespace std;

class Menu
{
public:
    void start();
    void continueGame(sf::RenderWindow*);
protected:
    void createPanel();
    vector <StaticTexture> tablica;
    vector <sf::Text> textVector;
    vector <StaticText> diffList;
    sf::RenderWindow* wnd;
    void createBack();
    void createDifList();
private:
    Map *map;
    void mainLoop(sf::RenderWindow*);
    void events(sf::RenderWindow*);
    void drawBack();
    void drawPanel();
    void drawDifList();
    void downOption();
    void upOption();
    void rightOption();
    void changeSelectedOption(int);
    void ClickEvent(int);
    void keyboardPressEvent(sf::Event, sf::RenderWindow *);
    int checkMousePosition(int, int);
    void startGame(sf::RenderWindow*);
    void setDifText(int);
    int selectedDif = 0;//0-latwy,1-sredni, 2-trudny
    int onChangeDif = 0;
    int selectedItem = 0;
    bool stop = 0;
    bool createGame = 0;
    bool options = 0;
    bool instructions = 0;
    sf::Font font;
    sf::String fontLoc = "Fonts/OpenSans-Light.ttf";
    sf::Font font2;
};

