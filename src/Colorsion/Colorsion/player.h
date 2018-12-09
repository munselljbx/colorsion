#pragma once
#include "colorO.h"

class player: public colorO {
public:
	void addColor(int rColorIn, int gColorIn, int bColorIn);
	void setLastColor(int inLastR, int inLastG, int inLastB);

	int lastRColor;
	int lastGColor;
	int lastBColor;
};
