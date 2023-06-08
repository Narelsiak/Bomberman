#pragma once
#include "Menu.h"
#include "Instructions.h"
//text z menu oraz grafiki do nowej klasy->

void Menu::start()
{
    wnd = new sf::RenderWindow();
    wnd->create(sf::VideoMode(31*32,23*32), "Bomberman");
    //wnd->setFramerateLimit(100);
    createPanel();
    createBack();
    createDifList();
    options = 0, instructions = 0, stop = 0;
    mainLoop(wnd);
}
void Menu::continueGame(sf::RenderWindow * window){
    createPanel();
    createBack();
    createDifList();
    options = 0, instructions = 0, stop = 0;
    mainLoop(wnd);
}
void Menu::mainLoop(sf::RenderWindow * window){
    Instructions instruction;
    while (wnd->isOpen()) {
        events(wnd);
        wnd->clear(sf::Color(120, 120, 125));
        if (options == 0 && instructions == 0 && createGame == 0) {
            drawBack();
            drawPanel();
            drawDifList();
        }
        if (options == 1) {
            //todo opcje, dzwiek, ikonka postaci
        }
        if (instructions == 1) {
            instruction.startI(wnd);
            //todo instrukcja, tj sterowanie, podstawowe informacje
        }
        wnd->display();
        if (stop == 1) {
            GameDifParam* param = new GameDifParam();
            param->setParametr(selectedDif);
            Map map;
            cout << "ADRESPRZED: " << this << endl;
            map.game(window, param);
            delete param;        
            cout <<"ADRESPO: "<< this << endl;

            stop = 0;
        }
    }
}
void Menu::startGame(sf::RenderWindow * window) {
    stop = 1;
}
void Menu::setDifText(int opt)
{
    string dif = "Poziom trudnosci: \n";
    dif += selectedDif == 0 ? "Latwy" : selectedDif == 1 ? "Sredni" : "Trudny";
    diffList[0].getTextP()->setString(dif.c_str());
}
void Menu::drawBack(){
    for (int i = 0; i < tablica.size(); i++) {
        wnd->draw(tablica[i].getSprite());
    }
}
void Menu::events(sf::RenderWindow * window)
{
    sf::Event event;
    while (window->pollEvent(event)) {
        //klawiatura
        if (event.type == event.KeyPressed) {
            cout <<"code"<< event.key.code << endl;
            keyboardPressEvent(event, window);
        }
        if (event.type == event.MouseMoved) {
            changeSelectedOption(checkMousePosition(event.mouseMove.x, event.mouseMove.y));
        }
        if (event.type == event.MouseButtonPressed && event.key.code == sf::Mouse::Left) {
            ClickEvent(checkMousePosition(sf::Mouse::getPosition(*wnd).x, sf::Mouse::getPosition(*wnd).y));
        }
    }
}
void Menu::createPanel()
{
    if (!font.loadFromFile("Fonts/OpenSans-Light.ttf")) {
        //dodac try.
    }
    sf::Vector2u size = wnd->getSize();
    /*text[4].setFont(font);
    text[4].setCharacterSize(24);
    text[4].setFillColor(sf::Color::Black);
    text[4].setString("Do poruszania sie po menu uzyj klawiatury lub myszki");
    text[4].setPosition(size.x / 2 - text[4].getGlobalBounds().width / 2, size.y - text[4].getGlobalBounds().height * 1.5);
    */
    textVector.push_back(sf::Text());
    textVector[0].setFont(font);
    textVector[0].setFillColor(sf::Color::Red);
    textVector[0].setString("Start");
    textVector[0].setPosition(size.x/2 - textVector[0].getGlobalBounds().width/2, size.y/5 - textVector[0].getGlobalBounds().height / 2);

    textVector.push_back(sf::Text());
    textVector[1].setFont(font);
    textVector[1].setFillColor(sf::Color::White);
    textVector[1].setString("Opcje");
    textVector[1].setPosition(size.x / 2 - textVector[1].getGlobalBounds().width / 2, size.y / 5 * 2 - textVector[1].getGlobalBounds().height / 2);

    textVector.push_back(sf::Text());
    textVector[2].setFont(font);
    textVector[2].setFillColor(sf::Color::White);
    textVector[2].setString("Sterowanie");
    textVector[2].setPosition(size.x / 2 - textVector[2].getGlobalBounds().width / 2, size.y / 5 * 3 - textVector[2].getGlobalBounds().height / 2);

    textVector.push_back(sf::Text());
    textVector[3].setFont(font);
    textVector[3].setFillColor(sf::Color::White);
    textVector[3].setString("Wyjscie");
    textVector[3].setPosition(size.x / 2 - textVector[3].getGlobalBounds().width / 2, size.y / 5 * 4 - textVector[3].getGlobalBounds().height / 2);

    textVector.push_back(sf::Text());
    textVector[4].setFont(font);
    textVector[4].setCharacterSize(24);
    textVector[4].setFillColor(sf::Color::Black);
    textVector[4].setString("Do poruszania sie po menu uzyj klawiatury lub myszki");
    textVector[4].setPosition(size.x / 2 - textVector[4].getGlobalBounds().width / 2, size.y - textVector[4].getGlobalBounds().height * 1.5);
    selectedItem = 0;
}
void Menu::createBack()
{
    tablica.push_back(StaticTexture());
    tablica.push_back(StaticTexture());
    tablica[0].setnew("Menu/background2.png", 700.f, 450.f);
    tablica[1].setnew("Menu/background1.png", 5.f, 130.f);
}
void Menu::createDifList()
{
    font2.loadFromFile(fontLoc);
    sf::Vector2u size = wnd->getSize();
    diffList.push_back(StaticText());
    string dif = "Poziom trudnosci: \n";
    dif += selectedDif == 0 ? "Latwy" : selectedDif == 1 ? "Sredni" : "Trudny";
    diffList[0].setParametr(&font2, sf::Color::White, dif.c_str(), sf::Vector2u(textVector[0].getPosition().x + textVector[0].getGlobalBounds().width + 50.f, textVector[0].getPosition().y), size);
    
    diffList.push_back(StaticText());
    diffList[1].setParametr(&font2, sf::Color::Red, "Latwy", sf::Vector2u(textVector[0].getPosition().x + textVector[0].getGlobalBounds().width + 50.f, textVector[0].getPosition().y - 30), size);
    
    diffList.push_back(StaticText());
    diffList[2].setParametr(&font2, sf::Color::White, "Sredni", sf::Vector2u(textVector[0].getPosition().x + textVector[0].getGlobalBounds().width + 50.f, textVector[0].getPosition().y), size);

    diffList.push_back(StaticText());
    diffList[3].setParametr(&font2, sf::Color::White, "Trudny", sf::Vector2u(textVector[0].getPosition().x + textVector[0].getGlobalBounds().width + 50.f, textVector[0].getPosition().y + 30), size);
    
    }
void Menu::downOption()
{
    if (onChangeDif == 0) {
        if (selectedItem + 1 < textVector.size() - 1) {
            textVector[selectedItem].setFillColor(sf::Color::White);
            selectedItem++;
            textVector[selectedItem].setFillColor(sf::Color::Red);
        }
        else {
            textVector[selectedItem].setFillColor(sf::Color::White);
            selectedItem = 0;
            textVector[selectedItem].setFillColor(sf::Color::Red);
        }
    }
    else {
        if (selectedDif + 1 < diffList.size() - 1) {        
            diffList[selectedDif + 1].getTextP()->setFillColor(sf::Color::White);
            selectedDif++;
            diffList[selectedDif + 1].getTextP()->setFillColor(sf::Color::Red);
        }
        else {
            diffList[selectedDif + 1].getTextP()->setFillColor(sf::Color::White);
            selectedDif = 0;
            diffList[selectedDif + 1].getTextP()->setFillColor(sf::Color::Red);
        }
    }
}
void Menu::upOption()
{
    if (onChangeDif == 0) {
        if (selectedItem - 1 >= 0) {
            textVector[selectedItem].setFillColor(sf::Color::White);
            selectedItem--;
            textVector[selectedItem].setFillColor(sf::Color::Red);
        }
        else {
            textVector[selectedItem].setFillColor(sf::Color::White);
            selectedItem = textVector.size() - 1 - 1;
            textVector[selectedItem].setFillColor(sf::Color::Red);
        }
    }
    else {
        if (selectedDif - 1 >= 0) {
            diffList[selectedDif + 1].getTextP()->setFillColor(sf::Color::White);
            selectedDif--;
            diffList[selectedDif + 1].getTextP()->setFillColor(sf::Color::Red);
        }
        else {
            diffList[selectedDif + 1].getTextP()->setFillColor(sf::Color::White);
            selectedDif = diffList.size() - 1 - 1;
            diffList[selectedDif + 1].getTextP()->setFillColor(sf::Color::Red);
        }
    }
}
void Menu::rightOption()
{
    onChangeDif = 1;
    textVector[selectedItem].setFillColor(sf::Color::White);

}
void Menu::drawPanel()
{
    for (int i = 0; i < textVector.size();i++) {
        wnd->draw(textVector[i]);
    }
}
void Menu::drawDifList()
{
    if (onChangeDif == 0) {
        wnd->draw(diffList[0].getText());
    }
    else {
        for (int i = 1; i < diffList.size(); i++) {
            wnd->draw(diffList[i].getText());
        }
    }
}
void Menu::changeSelectedOption(int option)
{
    if (option != -1 && onChangeDif == 1) {
        textVector[selectedItem].setFillColor(sf::Color::White);
        diffList[selectedDif+1].getTextP()->setFillColor(sf::Color::White);
        //cout << "OPTION" << option << endl;
        selectedDif = option;
        diffList[selectedDif+1].getTextP()->setFillColor(sf::Color::Red);
    }
    if (option == -1 && onChangeDif == 1) {
        textVector[selectedItem].setFillColor(sf::Color::White);
    }
    if (option!=-1 && onChangeDif == 0) {
        textVector[selectedItem].setFillColor(sf::Color::White);
        selectedItem = option;
        textVector[selectedItem].setFillColor(sf::Color::Red);
    }
}
void Menu::ClickEvent(int option)
{
    if (onChangeDif == 0) {
        if (option != -1) {
            switch (option) {
            case 0:
                startGame(wnd);
                return;
                break;
            case 1:
                options = 1;
                break;
            case 2:
                instructions = 1;
                break;
            case 3:
                wnd->close();
                break;
            }
        }
    }
    else {
        onChangeDif = 0;
        selectedDif = option;
        setDifText(option);
        //cout << "selectedDif: " << selectedDif << endl;   
        textVector[selectedItem].setFillColor(sf::Color::Red);
    }
}
void Menu::keyboardPressEvent(sf::Event event, sf::RenderWindow * window)
{
    if (event.key.code == sf::Keyboard::Down) {
        downOption();
    }
    if (event.key.code == sf::Keyboard::Up) {
        upOption();
    }
    if (selectedItem == 0 && event.key.code == sf::Keyboard::Right && onChangeDif == 0) {
        rightOption();
        //przejscie na ustawianie trudnosci.
    }
    if (onChangeDif == 0 && event.key.code == sf::Keyboard::Enter) {
        ClickEvent(selectedItem);
    }
    if(onChangeDif == 1 && event.key.code == sf::Keyboard::Enter) {
        onChangeDif = 0;
        cout <<"DIFFICULITY: "<< selectedDif << endl;
        setDifText(selectedDif);
        //wybranie innego poziomu trudnosci
        textVector[selectedItem].setFillColor(sf::Color::Red);
    }
    if ((instructions == 1 || options == 1) && event.key.code == sf::Keyboard::Escape) {
        instructions = 0, options = 0;
    }
}
int Menu::checkMousePosition(int positionX, int positionY)
{
    //cout << positionX << " " << positionY << endl;
    for (int i = 0; i < textVector.size() -1;i++){
        if (positionX >= textVector[i].getGlobalBounds().left && positionX <= (textVector[i].getGlobalBounds().left + textVector[i].getGlobalBounds().width)){
       
            if (positionY >= textVector[i].getGlobalBounds().top && positionY <= (textVector[i].getGlobalBounds().top + textVector[i].getGlobalBounds().height)) {
                if(onChangeDif == 1) onChangeDif = 0;
                return i;
            }
        }
    }
    if (positionX > diffList[0].getTextP()->getGlobalBounds().left && positionX <= (diffList[0].getTextP()->getGlobalBounds().left + diffList[0].getTextP()->getGlobalBounds().left) 
     && positionY >= diffList[0].getTextP()->getGlobalBounds().top && positionY <= (diffList[0].getTextP()->getGlobalBounds().top+ diffList[0].getTextP()->getGlobalBounds().height)){
        onChangeDif = 1;
    }
    if (onChangeDif == 1) {
        for (int i = 1; i < diffList.size(); i++) {
            //cout <<"I: "<<i<< " "<< diffList[i].getTextP()->getGlobalBounds().height << endl;
            if (positionX > diffList[i].getTextP()->getGlobalBounds().left && positionX <= (diffList[i].getTextP()->getGlobalBounds().left + diffList[i].getTextP()->getGlobalBounds().width)
                && positionY >= diffList[i].getTextP()->getGlobalBounds().top && positionY <= (diffList[i].getTextP()->getGlobalBounds().top + diffList[i].getTextP()->getCharacterSize())) {
                return i-1;
            }
        }
        //cout << "DD" << endl;
    }
    onChangeDif = 0;
    textVector[selectedItem].setFillColor(sf::Color::Red);
    return -1;
}