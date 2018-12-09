#include "player.h"

void player::addColor(int rColorIn, int gColorIn, int bColorIn)
{
	//rColor = lastRColor;
	//gColor = lastGColor;
	//bColor = lastBColor;

	//std::cout << "before add: " << rColor << std::endl;

	rColor = (rColorIn + rColor) / 2;
	gColor = (gColorIn + gColor) / 2;
	bColor = (bColorIn + bColor) / 2;

	circle.setFillColor(sf::Color(rColor, gColor, bColor));
	//std::cout << "added to: " << rColor << std::endl;
}

void player::setLastColor(int inLastR, int inLastG, int inLastB)
{
	lastRColor = inLastR;
	lastGColor = inLastG;
	lastBColor = inLastB;
}
