#define _USE_MATH_DEFINES
#include <cmath>
#include "creature.h"
#include <iostream>

// Difference between current position and the tile center.
static const double CENTER_DIM = 0.05;

Creature::Creature(int x_b, int y_b, float z_b)
{
	x = x_b;
	y = y_b;
	z = z_b;
	tileX = x_b;
	tileY = y_b;

	atCenter = true;
}

void Creature::calcCurrentTile()
{
	if ((angle == 0) && (x - (int)x > 0.5))
		tileX = (int)ceil(x);
	if ((angle == 180) && (x - (int)x < 0.5))
		tileX = (int)floor(x);
	if ((angle == 90) && (y - (int)y > 0.5))
		tileY = (int)ceil(y);
	if ((angle == 270) && (y - (int)y < 0.5))
		tileY = (int)floor(y);
}

bool Creature::isCenterTile()
{
	return (
		((angle == 0)   && (x - (int)x > 1 - CENTER_DIM)) ||
	    ((angle == 180) && (x - (int)x < CENTER_DIM))     ||
	    ((angle == 90)  && (y - (int)y > 1 - CENTER_DIM)) ||
	    ((angle == 270) && (y - (int)y < CENTER_DIM)))    ? true : false;
}

// Basic movement algorithm.
void Creature::Move()
{
	if (moving) 
	{
		x += speed*cos(M_PI/180*angle); // dodawany jakis staly interwal
		y += speed*sin(M_PI/180*angle);

		if (!atCenter && isCenterTile())
		{
			atCenter = true;
			onTileCenter();
		}
	}

	int oldTileX = tileX;
	int oldTileY = tileY;

	calcCurrentTile();

	if (tileX != oldTileX || tileY != oldTileY) // kiedy wszedlem na nowa plytke
	{
		atCenter = false;  // wtedy moge szukac centrum nowej plytki
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
	x = tileX;
	y = tileY;
}