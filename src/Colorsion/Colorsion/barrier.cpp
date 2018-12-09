#include "barrier.h"

barrier::barrier()
{
	isActive = false;
	rColor = 255;
	gColor = 255;
	bColor = 255;

	circle.setRadius(586);
	circle.setOrigin(586, 586);
	circle.setPosition(400, 400);
	circle.setFillColor(sf::Color(255, 255, 255));

	interiorCircle.setRadius(566);
	interiorCircle.setOrigin(566, 566);
	interiorCircle.setFillColor(sf::Color());
}