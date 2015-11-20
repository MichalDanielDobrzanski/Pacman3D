#define _USE_MATH_DEFINES
#include <cmath>

#include "ghost.h"
#include "gameboard.h"
#include "GLUT.H"
#include <iostream>

Ghost::Ghost(int tx, int ty)
{
	angle = 180; // initially all ghosts move to the left
	moving = true;
	speed = 0.02;


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


// basic movement algorithm which applies to every ghost
void Ghost::BasicMove()
{
	// ghost regular movement
	if (moving)
	{
		x +=  speed*cos(M_PI/180*angle); // dodawany jakis staly interwal
		y +=  speed*sin(M_PI/180*angle);
	}
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

double Ghost::TargetPythagoras(double x, double y)
{
	return sqrt(abs(x * x - targetX * targetX) + abs(y * y - targetY * targetY));
}

bool Ghost::isAtIntersection()
{
	if (abs(x - (int)x) < 0.05 && abs(y - (int)y < 0.05))
	{
	int counter = 3;
	if (WallCheck(angle))
		counter--;
	if (WallCheck(GetLeftAngle(angle)))
		counter--;
	if (WallCheck(GetRightAngle(angle)))
		counter--;

	if (counter > 1)
	{
		std::cout << "Intersection." << angle << std::endl;
		return true;
	}
	else
		return false;
	}
	else
		return false;
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
		std::cout << "Blinky: My target: " << targetX << ", " << targetY << std::endl;
	}
}