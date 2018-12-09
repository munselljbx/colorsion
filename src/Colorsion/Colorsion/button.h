#pragma once
#include <SFML/graphics.hpp>
#include <string>

class button
{
public:
	button();
	button(int inX, int inY, int inWidth, int inHeight, std::string inString, int inCharacterSize);

	bool allowButton;
	bool isClicked;
	sf::RectangleShape rect;
	sf::Text text;
	sf::Font candal;
};
