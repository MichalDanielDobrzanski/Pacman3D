#define _USE_MATH_DEFINES
#include <cmath>

#include "pac.h"
#include "gameboard.h"
#include "GLUT.H"

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
	x +=  speed*cos(M_PI/180*angle); // dodawany jakis staly interwal
	y +=  speed*sin(M_PI/180*angle);
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

void Pac::Turn(int v)//, GameBoard* board)
{
	double dim_var; // zmienna przyjmujaca wartosci x dla ruchu w gore/w dol lub wartosci y dla ruchu w lewo/w prawo
	switch (v)
	{
	case 0: // going left
		dim_var = y;
		break;
	case 90: // going top
		dim_var = x;
		break;

	case 180: // goin right
		dim_var = y;
		break;

	case 270: // going bottom
		dim_var = x;
		break;
	default:
		break;
	}

	if (angle != v)
	{
		if ((dim_var - (int)dim_var > 0.5)) //&& //!board->isWall((int)x + 1,(int)y + 1))
		{
			x += 1;
		} 

		//if (!board->isWall((int)x,(int)y + 1))
		{
			if (angle != 270) 
			{
					Pad();
			}
			moving = true;
			angle = 90;
		}
	}
}
