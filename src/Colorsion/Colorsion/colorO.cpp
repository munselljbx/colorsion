#include "colorO.h"

colorO::colorO()
{
	isActive = false;
	rColor = 255;
	gColor = 255;
	bColor = 255;
	circle.setRadius(20);
	circle.setOrigin(20, 20);
	circle.setPosition(400, 400);
	circle.setFillColor(sf::Color(255, 255, 255));
}

void colorO::setColor(int rColorIn, int gColorIn, int bColorIn)
{
	rColor = rColorIn;
	gColor = gColorIn;
	bColor = bColorIn;

	circle.setFillColor(sf::Color(rColor, gColor, bColor));
}