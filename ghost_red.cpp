#define _USE_MATH_DEFINES
#include <cmath>
#include "ghost_red.h"
#include "gameboard.h"
#include "glut.h"
#include <iostream>

GhostRed::GhostRed(int x, int y, float z) : Ghost(1,1,0,x,y,z)
{
	index = 1;
	chase = true;
	scatter = false;
	frightened = false;

	// default scatter point for the red ghost
	scatterTileX = GameBoard::DIM_X - 2;
	scatterTileY = GameBoard::DIM_Y + 4;
}

GhostRed::~GhostRed() { }