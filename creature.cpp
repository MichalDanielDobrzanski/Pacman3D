#define _USE_MATH_DEFINES
#include <cmath>
#include "creature.h"
#include <iostream>


static const double CENTER_DIM = 0.05;

Creature::Creature(int x_b, int y_b)
{
	x = x_b;
	y = y_b;
	tileX = x_b;
	tileY = y_b;

	atCenter = true;
}

void Creature::calcTileX()
{
	if (angle == 0)
		if (x - (int)x > 0.5)
			tileX = (int)ceil(x);
	if (angle == 180)
		if (x - (int)x < 0.5)
			tileX = (int)floor(x);
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

bool Creature::isCenterTile()
{
	if (angle == 0)
	{
		if (x - (int)x > 1 - CENTER_DIM)
			return true;
	}
	if (angle == 180)
	{
		if (x - (int)x < CENTER_DIM)
			return true;
	}
	if (angle == 90)
	{
		if (y - (int)y > 1 - CENTER_DIM)
			return true;
	}
	if (angle == 270)
	{
		if (y - (int)y < CENTER_DIM)
			return true;
	}
	return false;
}

void Creature::Move()
{

	if (moving) 
	{
		x +=  speed*cos(M_PI/180*angle); // dodawany jakis staly interwal
		y +=  speed*sin(M_PI/180*angle);

		if (!atCenter && isCenterTile())
		{
			atCenter = true;
			onTileCenter();
		}
	}

	int oldTileX = tileX;
	int oldTileY = tileY;

	calcTileX();
	calcTileY();

	if (tileX != oldTileX || tileY != oldTileY)
	{
		atCenter = false;
		onTileChange();
	}
}

void Creature::Pad()
{
	x = (int)x;
	y = (int)y;
}

void Creature::PadToCenter()
{

	if (angle == 180 || angle == 270)
	{
		x = tileX;
		y = tileY;
	}

	if (angle == 0 || angle == 90)
	{
		x = tileX;
		y = tileY;
	}
}