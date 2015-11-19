#define _USE_MATH_DEFINES
#include <cmath>

#include "pac.h"
#include "gameboard.h"
#include "GLUT.H"
#include <iostream>

Pac::Pac(int x_b, int y_b)
{
	x = x_b;
	y = y_b;
	z = 0;
	speed = 0.07;
	moving = true;
	angle = 0;
	lives = 3;
}

Pac::~Pac()
{
}

void Pac::Move(void)
{
	if (moving) 
	{
		x +=  speed*cos(M_PI/180*angle); // dodawany jakis staly interwal
		y +=  speed*sin(M_PI/180*angle);
	}
}

void Pac::Draw() 
{
	//draw current pacman
	glColor3f(1,1,0); // yellow
	glPushMatrix();
		glTranslatef(x,y,0.0);
		glutSolidSphere(0.5,20,20);
	glPopMatrix();

}

void Pac::Pad()
{
	// padding
	x = (int)x;
	y = (int)y;
}


// true if COIN was eaten
bool ConsumeMap(int x, int y)
{
	int idx = GameBoard::DIM_Y - y - 1;
	if (GameBoard::initial_map[idx][x] == 0)
	{
		// consume a coin (-1 value indicates eaten)
		GameBoard::initial_map[idx][x] = -1;
		return true;
	} else
	if (GameBoard::initial_map[idx][x] == 3)
	{
		// consume energizer
		GameBoard::initial_map[idx][x] = -1;
	}
	return false;
}

// true if COIN (not energizer) was eaten
bool Pac::Consume()
{
	if (x - (int)x < 0.4 &&  angle == 180) // going left
	{
		if (ConsumeMap((int)x,(int)y))
			return true;
	} else 
	if (x - (int)x >= 0.6 && angle == 0) // goin right
	{
		if(ConsumeMap((int)x + 1,(int)y))
			return true;
	} else 
	if (y - (int)y < 0.4 && angle == 270) // goin bottom
	{
		if(ConsumeMap((int)x,(int)y))
			return true;
	} else 
	if (y - (int)y >= 0.6 && angle == 90) // goin top
	{
		if (ConsumeMap((int)x,(int)y + 1))
			return true;
	}
	return false;
}


// check whether PackMan can go to the next tile he is facing.
bool Pac::WallCheck()
{
	if (((angle == 0   && GameBoard::isWall((int)(x + 1),(int)y))        || // moving right
		( angle == 180 && GameBoard::isWall((int)(x - 1),(int)y))        || // moving left
		( angle == 90  && GameBoard::isWall((int) x     ,(int)(y + 1)))  || // moving top
		( angle == 270 && GameBoard::isWall((int) x     ,(int)(y - 1)))) && // moving bottom
		abs(x - (int)x) < 0.1 && abs(y - (int)y < 0.1))	
	{
		moving = false;
		// padding
		x = (int)x;
		y = (int)y;
		return false;
	}
	return true;
}

// helper function
void Pac::PadAndMove(int a)
{
	if (angle != (a + 180) % 360)
	{
		Pad();
	}
	moving = true;
	angle = a;
}

// TODO: write an algorithm
void Pac::Turn(int nangle) // new angle
{
	//std::cout << "angle " << angle << " New angle " << nangle << std::endl;
	if (angle != nangle) // do not consider the same direction
	{
		if (nangle == 180) // wanting to go left
		{
			if ((y - (int)y >= 0.6) && !GameBoard::isWall((int)x - 1,(int)y - 1))
			{ // going from top
				y += (1 - (y - (int)y));
			} 

			if (!GameBoard::isWall((int)x - 1,(int)y))
				PadAndMove(nangle);

		} else
		if (nangle == 0) // wanting to go right
		{
			if ((y - (int)y >= 0.6) && !GameBoard::isWall((int)x + 1,(int)y - 1))
			{ // going from top
				y += (1 - (y - (int)y));
			} 

			if (!GameBoard::isWall((int)x + 1,(int)y))
				PadAndMove(nangle);

		} else
		if (nangle == 90) // wanting to go top
		{
			if ((x - (int)x >= 0.6) && !GameBoard::isWall((int)x + 1,(int)y + 1))
			{ // going from left
				x += (1 - (x - (int)x));
			} 

			if (!GameBoard::isWall((int)x,(int)y + 1))
				PadAndMove(nangle);

		} else
		if (nangle == 270) // wanting to go bottom
		{ // going from left
			if ((x - (int)x >= 0.6) && !GameBoard::isWall((int)x + 1,(int)y - 1))
			{
				x += (1 - (x - (int)x));
			}
			if (!GameBoard::isWall((int)x,(int)y - 1))
				PadAndMove(nangle);
		}
	}
}