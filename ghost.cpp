#define _USE_MATH_DEFINES
#include <cmath>

#include "ghost.h"
#include "gameboard.h"
#include "GLUT.H"
#include <iostream>
#include <vector>
#include <exception>

Ghost::Ghost(int tx, int ty) : Creature(tx,ty)
{
	angle = 180; // initially all ghosts move to the left
	speed = 0.03;

	if (index == 1)
	{
		// red ghost
		scatterTileX = GameBoard::DIM_X - 2;
		scatterTileY = GameBoard::DIM_Y + 4;
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

int Ghost::TargetPythagoras(int agle)
{
	int tx = 0;
	int ty = 0;

	if (agle == 0)
	{
		tx = tileX + 1;
		ty = tileY;
	}
	if (agle == 180)
	{
		tx = tileX - 1;
		ty = tileY;
	}
	if (agle == 90)
	{
		tx = tileX;
		ty = tileY + 1;
	}
	if (agle == 270)
	{
		tx = tileX;
		ty = tileY - 1;

	}
	return abs(tx * tx - targetTileX * targetTileX) + abs(ty * ty - targetTileY * targetTileY);
}

// Here we will make a decision where should ghost go.
void Ghost::onTileCenter()
{
	moving = false;
	PadToCenter();

	//std::cout << "Ghost at center of tile coords: " << x << ", " << y << std::endl;
	//std::cout << "Ghost at center of tile: " << tileX << ", " << tileY << std::endl;

	// Dealing with intersections:
			//		  Front  Left   Right
	std::vector<int> dist(3,10000);

	if (!WallCheck(angle))
	{
		dist[0] = TargetPythagoras(angle);
		//std::cout << "Ghost front dist: " << dist[0] << std::endl;
	}
	if (!WallCheck(GetLeftAngle(angle)))
	{
		dist[1] = TargetPythagoras(GetLeftAngle(angle));
		//std::cout << "Ghost left dist: " << dist[1] << std::endl;
	}
	if (!WallCheck(GetRightAngle(angle)))
	{
		dist[2] = TargetPythagoras(GetRightAngle(angle));
		//std::cout << "Ghost right dist: " << dist[2] << std::endl;
	}

	//std::cout << "Ghost Fdist: " << dist[0] << ", Ldist: " << dist[1] << ", Rdist" << dist[2] << std::endl;

	int smallest = dist[0];
	int idx = 0;
	for (int i = 1; i < dist.size(); i++) 
	{
		if (dist[i] < smallest)
		{
			smallest = dist[i];
			idx = i;
		}
	}

	try { if (smallest == 10000) throw 99; } 
	catch (int e) { std::cout << "Exception " << e << ": THERE CANT BE ANY DEAD CORRIDORS IN THE MAP "  << '\n'; }

	if (idx == 1)
		angle = GetLeftAngle(angle);
	else
	if (idx == 2)
		angle = GetRightAngle(angle);

	moving = true;	
}

