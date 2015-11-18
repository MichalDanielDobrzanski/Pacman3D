#define _USE_MATH_DEFINES
#include <cmath>

#include <windows.h>
#include <GL/gl.h>
#include "glut.h"
#include "pac.h"
#include "gameboard.h"
#include <iostream>
#include <string>

// board game:
GameBoard *board;

// mr. pacman
Pac *pacman;
bool pacFollowed = false;

// mouse
GLdouble dx = 0;
GLdouble dy = 0;
GLdouble dz = 0;

int oldX = 0;
int oldY = 0;

double theta = 0;
double phi = 0;

float sensitivity = -0.5f;

// camera
float angleXZ = -90;
float angleYZ = 90;

// init coordinates
GLdouble eyeX = 0;
GLdouble eyeY = 0;
GLdouble eyeZ = 0;

// information
std::string infoText[] = 
{
	"Coins left: ",
	"Lives: "
};

// wspolrzedne dla kamery (obserwatora calej sceny)
GLdouble centerX = GameBoard::CENTER_X;
GLdouble centerY = GameBoard::CENTER_Y;
GLdouble centerZ = GameBoard::CENTER_Z;
GLdouble centerDistance = 15;

GLdouble positionx = eyeX;
GLdouble positiony = eyeY;
GLdouble positionz = eyeZ;


void init()
{

    GLfloat mat_ambient[]    = { 1.0, 1.0,  1.0, 1.0 };
    GLfloat mat_specular[]   = { 1.0, 1.0,  1.0, 1.0 };
	GLfloat light_position[] = { GameBoard::DIM_X / 2 , GameBoard::DIM_Y / 2, 4.0, 1.0 };
    GLfloat lm_ambient[]     = { 0.2, 0.2,  0.2, 1.0 };

    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient );
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular );
    glMaterialf( GL_FRONT, GL_SHININESS, 50.0 );

    glLightfv( GL_LIGHT0, GL_POSITION, light_position );
    glLightModelfv( GL_LIGHT_MODEL_AMBIENT, lm_ambient );

	// parametry cieniowania (flat daje taki sam kolor)
    glShadeModel( GL_SMOOTH );

    glEnable( GL_LIGHTING );
    glEnable( GL_LIGHT0 );

    glDepthFunc( GL_LESS );
    glEnable( GL_DEPTH_TEST );

	glEnable(GL_NORMALIZE);

	//gluPerspective( 90, 1, 0.1, 10.0 );
	//glOrtho(0, GameBoard::DIM_X, 0, GameBoard::DIM_Y, 0.1, 10 );

}

void DrawInfo() 
{
	// buffer for storing coinsCount
	static const int buf_length = 4;
	static char count_buffer[buf_length];
	std::sprintf(count_buffer,"%d",pacman->lives);
	std::sprintf(count_buffer + 1,"%d",board->coinsCount); // very unsafe! Be careful!
	

	// updating coins count
	// http://stackoverflow.com/questions/18847109/displaying-fixed-location-2d-text-in-a-3d-opengl-world-using-glut
	glDisable(GL_TEXTURE_2D);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0,500,0,500);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
		glLoadIdentity();
		glColor3d(1.0, 1.0, 1.0);
		//std::cout << static_cast <char>(board->coinsCount) << std::endl;
		// text display functionality			
		for (int i = 0; i < sizeof(infoText) / sizeof(infoText[0]); i++)
		{
			glRasterPos2i(10, 500 - 20 - i * 18); // initial position of a raster.
			for (std::string::iterator j = infoText[i].begin(); j != infoText[i].end(); ++j)
			{
				glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,*j);
			}
			if (i == 0)
			{ // display coinsCount
				for (int j = 1; j < buf_length; j++)
				{
					glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, count_buffer[j]);
				}
			}
			if (i == 1)
			{ // display lives
				glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, count_buffer[0]);
			}
		}
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
	//added this
	glEnable(GL_TEXTURE_2D);
}

// renderowanie grafiki
void display()
{
	//std::cout << "render" << std::endl;
	float orthoOffset = 2.0f;

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	// TODO
	//glOrtho(-orthoOffset, GameBoard::DIM_X + orthoOffset, -orthoOffset, GameBoard::DIM_Y + orthoOffset, 0.1, 10 );
	//gluOrtho2D(-orthoOffset, GameBoard::DIM_X + orthoOffset, -orthoOffset, GameBoard::DIM_Y + orthoOffset );
	//glFrustum(-10.25, 10.25, -10.25, 10.25, 1, 1.3);
	gluPerspective( 90, 1, 5, 30.0 ); // 4. parametr - ile widzimy

	glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();

	glClearColor( 0.0f, 0.0f, 0.0f, 1.0f );
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT ); // czysc bufory

	// camera movement:
	// http://gamedev.stackexchange.com/questions/43588/how-to-rotate-camera-centered-around-the-cameras-position
	// M_PI /2 - przesuniecie fazowe w celu dobrego wyswietlenia poczatkowego planszy
	// implementacja operacji: ROLL (theta) (zla!) oraz PITCH (phi) ('w', 's' jest ok)

	if (pacFollowed) 
	{
		gluLookAt(pacman->x, pacman->y, pacman->z + centerDistance, pacman->x, pacman->y, pacman->z, 0, 1, 0);
	}
	else 
	{
		eyeX = centerX;// * sin(theta);
		eyeY = centerY + centerDistance * sin(phi);// * sin(theta);
		eyeZ = centerZ + centerDistance * cos(phi);//  * cos(theta);
		gluLookAt( eyeX, eyeY, eyeZ, centerX, centerY, centerZ, cos(theta + M_PI/2), sin(theta + M_PI/2), 0 );
	}

	// move the pacman
	if (pacman->moving)
		pacman->Move();	

	// wall check. Badz blisko szyny, aby go wykonac.
	//std::cout << "pac: " << pacman->x << ", " << pacman->y << std::endl;
	if (((pacman->angle == 0 && board->isWall((int)(pacman->x + 1),(int)pacman->y)) ||
		(pacman->angle == 180 && board->isWall((int)(pacman->x - 1),(int)pacman->y)) ||
		(pacman->angle == 90 && board->isWall((int)pacman->x,(int)(pacman->y + 1))) ||
		(pacman->angle == 270 && board->isWall((int)pacman->x,(int)(pacman->y - 1))))
		&& abs(pacman->x - (int)pacman->x) < 0.1
		&& abs(pacman->y - (int)pacman->y < 0.1)) 
	{
		pacman->moving = false;
		// padding
		pacman->x = (int)pacman->x;
		pacman->y = (int)pacman->y;
	}

	// coins eating
	if (pacman->x - (int)pacman->x < 0.4 &&  pacman->angle == 180) // going left
	{
		board->consume((int)pacman->x,(int)pacman->y);
	} else 
	if (pacman->x - (int)pacman->x > 0.6 && pacman->angle == 0) // goin right
	{
		board->consume((int)pacman->x + 1,(int)pacman->y);
	} else 
	if (pacman->y - (int)pacman->y < 0.4 && pacman->angle == 270) // goin bottom
	{
		board->consume((int)pacman->x,(int)pacman->y);
	} else 
	if (pacman->y - (int)pacman->y > 0.6 && pacman->angle == 90) // goin top
	{
		board->consume((int)pacman->x,(int)pacman->y + 1);
	}


	// actual pacman and board drawing
	glPushMatrix();
		pacman->Draw();
		board->Draw();
	glPopMatrix();

	// screen information
	DrawInfo();


    glFlush(); // wyczysc wszystkie bufory. Standard zaleca wywolywanie tej komendy.
	glutSwapBuffers();
}


void reshape(GLsizei w, GLsizei h)
{
    if( h > 0 && w > 0 ) {
    glViewport( 0, 0, w, h );
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();

	        
	GLdouble aspect = 1;
	if( h > 0 )
         aspect = w /( GLdouble ) h;
   
    // rzutowanie perspektywiczne
    //gluPerspective( 90, aspect, 0.1, 50.0 );

    //  if( w <= h ) {
    //     //glOrtho( -2.25, 2.25, -2.25*h/w, 2.25*h/w, -10.0, 10.0 ); // parametry obcinania // 2D RENDER!
	//glFrustum(-20.25, 20.25, -20.25, 20.25, 11, 50);
    //  }
    //  else {
    //     //glOrtho( -2.25*w/h, 2.25*w/h, -2.25, 2.25, -10.0, 10.0 );
		  //glFrustum(-2.25*w / h, 2.25*w / h, -2.25, 2.25, 1, 10);
    //  }
    //  glTranslatef(0, 0, -2.5);
    }
}

void keyboard(unsigned char key, int x, int y)
{
	float step = 0.1;

	switch (key)
	{
	case 'a':
		if (!pacFollowed)
			theta -= step;
		positionx -= step;
		break;
       
    // kursor w górê
	case 'w':
		if (!pacFollowed)
			phi += step;
		positiony += step;
		break;
       
    // kursor w prawo
	case 'd':        
		if (!pacFollowed)
			theta += step;
		positionx += step;
		break;
       
    // kursor w dó³
	case 's':
		if (!pacFollowed)
			phi -= step;
		positiony -= step;
		break;

	case 'r':
		if (pacFollowed)
			centerDistance -= step;
		positionz += step;
		break;

	case 'f':
		if (pacFollowed)
			centerDistance += step;
		positionz -= step;
		break;

	case 'c':
		//follow camera mode
		pacFollowed = pacFollowed ? false : true;
		break;
	}
}

void mouse(int button, int state, int x, int y)
{
	if (button == GLUT_RIGHT_BUTTON) {
		exit(0); 
	}
}

void special( int key, int x, int y )
{		
	// (int)pacman->y - pacman->y > -0.1 - warunek na animacje. Akceptuj tylko male odchylki od szyn.
	// Potrzebne, aby packman trzymal sie szyn, a nie z nich wychodzil sobie.
	// Skret w lewo mozliwy tylko, gdy jestesmy blisko jakies szyny y = [1,DIM_Y -1]
	switch( key )
    {
	case GLUT_KEY_LEFT:
		if (pacman->angle != 180)
		{ // kiedy idziemy z gory:
			if ((pacman->y - (int)pacman->y > 0.6) && !board->isWall((int)pacman->x - 1,(int)pacman->y - 1))
			{
				pacman->y += 0.4;
			} 

			if (!board->isWall((int)pacman->x - 1,(int)pacman->y))
			{
				if (pacman->angle != 0) 
				{
					pacman->Pad();
				}
				pacman->moving = true;
				pacman->angle = 180;
			}
		}


        break;

    case GLUT_KEY_RIGHT:   
		if (pacman->angle != 0)
		{
			if ((pacman->y - (int)pacman->y > 0.6) && !board->isWall((int)pacman->x + 1,(int)pacman->y - 1))
			{
				pacman->y += 0.4;
			} 

			if (!board->isWall((int)pacman->x + 1,(int)pacman->y))
			{
				if (pacman->angle != 180) 
				{
					pacman->Pad();
				}
				pacman->moving = true;
				pacman->angle = 0;
			}
		}

		//if (!board->isWall((int)pacman->x + 1,(int)pacman->y) && pacman->y - (int)pacman->y < 0.3  && pacman->angle != 0)
		//{
		//	if (pacman->angle != 180) {
		//		pacman->Pad();
		//	}
		//	pacman->moving = true;
		//	pacman->angle = 0;
		//}
        break;

    case GLUT_KEY_UP:
		//std::cout << "pac: " << pacman->x << ", " << pacman->y << " abs "<< pacman->x - (int)pacman->x << std::endl;
		std::cout << "diffX: " << pacman->x - (int)pacman->x << std::endl;
		if (pacman->angle != 90)
		{
			if ((pacman->x - (int)pacman->x > 0.6) && !board->isWall((int)pacman->x + 1,(int)pacman->y + 1))
			{
				pacman->x += 0.4;
			} 

			if (!board->isWall((int)pacman->x,(int)pacman->y + 1))
			{
				if (pacman->angle != 270) 
				{
					pacman->Pad();
				}
				pacman->moving = true;
				pacman->angle = 90;
			}
		}
        break;
       
    case GLUT_KEY_DOWN:
		if (pacman->angle != 270)
		{
			if ((pacman->x - (int)pacman->x > 0.6) && !board->isWall((int)pacman->x + 1,(int)pacman->y - 1))
			{
				pacman->x += 0.4;
			} 

			if (!board->isWall((int)pacman->x,(int)pacman->y - 1))
			{
				if (pacman->angle != 90) 
				{
					pacman->Pad();
				}
				pacman->moving = true;
				pacman->angle = 270;
			}
		}

		//if (!board->isWall((int)pacman->x,(int)pacman->y - 1) && pacman->x - (int)pacman->x < 0.5  && pacman->angle != 270)
		//{
		//	if (pacman->angle != 90) {
		//		pacman->Pad();
		//	}
		//	pacman->moving = true;
		//	pacman->angle = 270;
		//}
        break;
    }

	positionx = eyeX;
	positiony = eyeY;
	positionz = eyeZ;

	// odrysowanie okna
    reshape( glutGet( GLUT_WINDOW_WIDTH ), glutGet( GLUT_WINDOW_HEIGHT ) );
}

void mouseMotion( int x, int y )
{
	float dX = oldX - x;
	float dY = oldY - y;

	angleXZ += sensitivity*dX;
	angleYZ += sensitivity*dY;

	if(angleXZ < 0) angleXZ += 360;
	else if(angleXZ >= 360) angleXZ -= 360;

	if(angleYZ < 0) angleYZ = 0;
	else if(angleYZ >= 180) angleYZ = 180;
		
	centerX = cos(angleXZ * M_PI / 180);
	centerY = cos(angleYZ * M_PI / 180);
	centerX = sin(angleXZ * M_PI / 180);
	
	oldX = x;
	oldY = y;
}

void firstMotion( int x, int y )
{
    oldX = x;
	oldY = y;

	glutPassiveMotionFunc(mouseMotion);
}

void timer(int v) 
{

}


int main(int argc, char** argv)
{
	glutInit( &argc, argv );
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH); // pojedyncze buforowanie oraz bufor glebokosci ustawiamy
	glutInitWindowPosition( 0, 0 );
	glutInitWindowSize( 500, 500 );
	glutCreateWindow( "PackMan" ); // zainicjowany kontekst openGL'owy

	//glutGameModeString( "800x600:16@60" );
	//glutEnterGameMode();

	glutSetCursor(GLUT_CURSOR_NONE);

	glutDisplayFunc( display );
	glutReshapeFunc( reshape ); // trzeba zmienic parametry rzutowania
	glutIdleFunc(display); // scena jest caly czas przeliczana w tle

	glutTimerFunc(15, timer, 1);

	glutSpecialFunc(special);
	glutKeyboardFunc(keyboard);
	//glutMouseFunc(mouse);
	//glutPassiveMotionFunc(firstMotion);

	// inicjalizacja obiektow openGL
	pacman = new Pac(15,2);
	board = new GameBoard();

	init();

	glutMainLoop(); // w momencie wywolania nasz program zaczyna dzialac. Reaguje od tego momentu na zdarzenia.

	return 0;
}

