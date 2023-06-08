#include "StaticText.h"
#include <iostream>
void StaticText::setParametr(sf::Font * fontStr, sf::Color color, const char str[100], sf::Vector2u pos, sf::Vector2u wind, unsigned int charSize)
{
    text.setFont(*fontStr);
    text.setCharacterSize(charSize);
    text.setFillColor(color);
    text.setString(str);
    text.setPosition(pos.x, pos.y);
}
sf::Text StaticText::getText()
{
    return text;
}

sf::Text* StaticText::getTextP()
{
    return &text;
}

void StaticText::setNewString(sf::String string)
{
    text.setString(string);
}
