#define _USE_MATH_DEFINES
#include <cmath>
#include "ghost_red.h"
#include "gameboard.h"
#include "glut.h"
#include <iostream>

GhostRed::GhostRed(int x, int y) : Ghost(x,y)
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

void GhostRed::Draw()
{
	//draw ghost
	glColor3f(1,1,0);
	glPushMatrix();
		glTranslatef(x,y,0.0);
		glRotatef(45,0,0,1);
		glutSolidCube(0.5);
	glPopMatrix();
}