#define _USE_MATH_DEFINES
#include <cmath>

#include "ghost.h"
#include "gameboard.h"
#include "GLUT.H"
#include <iostream>

Ghost::Ghost(int tx, int ty) : Creature(tx,ty)
{
	angle = 180; // initially all ghosts move to the left
	speed = 0.05;

	if (index == 1)
	{
		// red ghost
		scatterX = GameBoard::DIM_X - 2;
		scatterY = GameBoard::DIM_Y + 4;
	}
}

void Ghost::Draw() 
{
	//draw ghost
	glColor3f(1,1,0);
	glPushMatrix();
		glTranslatef(x,y,0.0);
		glutSolidCube(0.7);
	glPopMatrix();
}

// Not ufeful as for now
void Ghost::onTileChange()
{
	//std::cout << "Ghost tile: " << tileX << ", " << tileY << std::endl;	
}

bool Ghost::WallCheck(int agle)
{
	if (agle == 0)
		return GameBoard::isWall(tileX + 1,tileY);
	if (agle == 180)
		return GameBoard::isWall(tileX - 1,tileY);
	if (agle == 90)
		return GameBoard::isWall(tileX,tileY + 1);
	if (agle == 270)
		return GameBoard::isWall(tileX,tileY - 1);
}

// ghost left hand direction
double GetLeftAngle(double angdir)
{
	if ((int)angdir + 90 == 360)
		return 0;
	else
		return angdir + 90;
}

// ghost right hand direction
double GetRightAngle(double angdir)
{
	if ((int)angdir - 90 == -90)
		return 270;
	else
		return angdir - 90;
}

double Ghost::TargetPythagoras(int x, int y)
{
	return sqrt(abs(x * x - targetTileX * targetTileX) + abs(y * y - targetTileY * targetTileY));
}


// Here we will make a decision where should ghost go.
void Ghost::onTileCenter()
{
	std::cout << "Ghost at center of tile: " << tileX << ", " << tileY << std::endl;

	// Dealing with the turns:
	if (WallCheck(angle))
	{
		//std::cout << "Wall in front " << std::endl;
		if (WallCheck(GetLeftAngle(angle))) // there is a wall on my left
		{
			std::cout << "Blinky: Lets go right. " << std::endl;	
			angle = GetRightAngle(angle); // yep, right.
		}
		else
		{
			std::cout << "Blinky: Lets go left. " << std::endl;
			angle = GetLeftAngle(angle);
		}
		// This is neccessary
		x = (int)x;
		y = (int)y;
	}
		
	// Dealing with intersections:
}

