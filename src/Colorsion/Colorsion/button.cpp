#include "button.h"

button::button()
{

}

button::button(int inX, int inY, int inWidth, int inHeight, std::string inString, int inCharacterSize)
{
	rect.setSize(sf::Vector2f(inWidth, inHeight));
	rect.setOrigin(inWidth / 2.0f, inHeight / 2.0f);
	rect.setPosition(inX, inY);
	rect.setFillColor(sf::Color(255, 255, 255));
	
	candal.loadFromFile("font/Candal.ttf");
	text.setFont(candal);
	text.setString(inString);
	text.setCharacterSize(inCharacterSize);
	text.setFillColor(sf::Color());
	
	sf::FloatRect textRect = text.getLocalBounds();
	text.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
	text.setPosition(sf::Vector2f(inX, inY));
}