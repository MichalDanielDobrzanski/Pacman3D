#define _USE_MATH_DEFINES
#include <cmath>
#include "creature.h"
#include <iostream>


Creature::Creature(int x_b, int y_b)
{
	x = x_b;
	y = y_b;
	tileX = x_b;
	tileY = y_b;
}

void Creature::calcTileX()
{
	if (angle == 0)
		if (x - (int)x > 0.5)
		{
			tileX = (int)ceil(x);
		}
	if (angle == 180)
		if (x - (int)x < 0.5)
		{
			tileX = (int)floor(x);
		}
}

void Creature::calcTileY()
{
	if (angle == 90)
		if (y - (int)y > 0.5)
			tileY = (int)ceil(y);
	if (angle == 270)
		if (y - (int)y < 0.5)
			tileY = (int)floor(y);
}


void Creature::Move()
{
	if (moving) 
	{
		x +=  speed*cos(M_PI/180*angle); // dodawany jakis staly interwal
		y +=  speed*sin(M_PI/180*angle);
	}

	int oldTileX = tileX;
	int oldTileY = tileY;

	calcTileX();
	calcTileY();

	if (tileX != oldTileX || tileY != oldTileY)
		onTileChange();
}

void Creature::Pad()
{
	x = (int)x;
	y = (int)y;
}
