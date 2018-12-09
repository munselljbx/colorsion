#pragma once
#include <SFML/graphics.hpp>
#include <string>
#include <iostream>

class colorO {
public:
	colorO();
	void setColor(int rColorIn, int gColorIn, int bColorIn);
	
	bool isActive;
	int rColor;
	int gColor;
	int bColor;
	sf::CircleShape circle;

};