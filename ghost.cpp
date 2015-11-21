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
	inter = false;

	x = tx;
	y = ty;

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



bool Ghost::WallCheck(int agle)
{
	if (agle == 0)
		return GameBoard::isWall((int)x + 1,(int)y);
	if (agle == 180)
		return GameBoard::isWall((int)x - 1,(int)y);
	if (agle == 90)
		return GameBoard::isWall((int)x,(int)y + 1);
	if (agle == 270)
		return GameBoard::isWall((int)x,(int)y - 1);
}

// Gets the next Tile coordinates based on angle
std::pair<int,int> Ghost::NextTile(int agle)
{
	if (agle == 0)
		return std::make_pair<int,int>((int)x + 1,(int)y);
	if (agle == 180)
		return std::make_pair<int,int>((int)x - 1,(int)y);
	if (agle == 90)
		return std::make_pair<int,int>((int)x,(int)y + 1);
	if (agle == 270)
		return std::make_pair<int,int>((int)x,(int)y - 1);
}


bool Ghost::WallStop()
{
	//std::cout << "Performing...." << std::endl;
	if (WallCheck(angle) && abs(x - (int)x) < 0.1 && abs(y - (int)y < 0.1))		
	{
		moving = false;
		// padding
		x = (int)x;
		y = (int)y;
		return false;
	}
	return true;
}

double Ghost::Rotate(double chng)
{
	if (angle + chng < 360)
		return (int)(angle + chng);
	else
		return (int)fmod(angle + chng, 360);
}

// ghost left hand direction
double Ghost::GetLeftAngle(double angdir)
{
	if ((int)angdir + 90 == 360)
		return 0;
	else
		return angdir + 90;
}

// ghost right hand direction
double Ghost::GetRightAngle(double angdir)
{
	if ((int)angdir - 90 == -90)
		return 270;
	else
		return angdir - 90;
}


void Ghost::Move()
{
	Creature::Move();
}

// Make a turn at the turn.
bool Ghost::AtTurn()
{
	if (abs(x - (int)x) < 0.05 && abs(y - (int)y < 0.05))
	{
		if (WallCheck(angle)) // there is a wall in front of me
		{
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
			x = (int)x;
			y = (int)y;
			return true;
		}
	}
	return false;
}

double Ghost::TargetPythagoras(int x, int y)
{
	return sqrt(abs(x * x - targetTileX * targetTileX) + abs(y * y - targetTileY * targetTileY));
}

bool Ghost::isAtIntersection()
{
	int idx = GameBoard::DIM_Y - y - 1;
	if (!inter && GameBoard::initial_map[idx][(int)x] == 5)
	{
		if (abs(x - (int)x) < 0.06 && abs(y - (int)y < 0.06))
		{
		std::cout << "Intersection. " << std::endl;
		inter = true;
		}
	}
	else
		inter = false;
	return true;
}


void Ghost::IntersectionDecision()
{
	if (abs(x - (int)x) < 0.05 && abs(y - (int)y < 0.05))
	{
		double dist = 1000;
		double newAngle = -1;

		moving = false;

		if (!WallCheck(angle))
		{
			double opt = TargetPythagoras(NextTile(angle).first,NextTile(angle).second);
			if (opt < dist)
				dist = opt;
		}

		if (!WallCheck(GetLeftAngle(angle)))
		{
			double opt = TargetPythagoras(NextTile(GetLeftAngle(angle)).first,NextTile(GetLeftAngle(angle)).second);
			if (opt < dist)
			{
				dist = opt;
				angle = GetLeftAngle(angle);
			}
		}

		if (!WallCheck(GetRightAngle(angle)))
		{
			double opt = TargetPythagoras(NextTile(GetRightAngle(angle)).first,NextTile(GetRightAngle(angle)).second);
			if (opt < dist)
			{
				dist = opt;
				angle = GetRightAngle(angle);
			}
		}

		std::cout << "Blinky: Intesection. x: " << x << std::endl;
		//std::cout << "Blinky: My target: " << targetX << ", " << targetY << std::endl;
	}
}