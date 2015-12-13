#define _USE_MATH_DEFINES
#include <cmath>

#include <windows.h>
#include <GL/gl.h>
#include "glut.h"
#include "creature.h"
#include "pac.h"
#include "ghost_red.h"
#include "gameboard.h"
#include "scrnsave.h"
#include <iostream>
#include <string>

static const int ghosts_count = 4;

// board game:
GameBoard *board;

// mr. pacman
Pac *pacman;
bool pacFollowed = false;

// ghosts
Ghost *ghosts[ghosts_count];

// basic game information
std::string infoText[] = 
{
	"Coins left: ",
	"Lives: "
};

// zooming - max Z distance and min Z distance
float maxZ = 15;
float minZ = 8;

// Camera up/down maximums:
float camUpDownMax = 0.8;

// Camera left/right maximums:
float camLRMax = 0.8;

// Camera rotation angles:
double theta = 0;
double phi = 0;

// Initial camera looking target
GLdouble centerX = GameBoard::CENTER_X;
GLdouble centerY = GameBoard::CENTER_Y;
GLdouble centerZ = GameBoard::CENTER_Z;
GLdouble centerDistance = 15;

// Camera (i.e. observer) coordinates
GLdouble eyeX = 0;
GLdouble eyeY = 0;
GLdouble eyeZ = 0;

void init()
{   
	// ustaw intensywnosc swaitla i kolor
	// https://www.youtube.com/watch?v=g_0yV7jZvGg
	// https://www.youtube.com/watch?v=gFZqzVQrw84 // swietny opis rodzajow swiatel
	// https://www.youtube.com/watch?v=oVwH8KV1xnY // najlepsze

	// intialization of 3D rendering
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);
	glEnable(GL_NORMALIZE); // Automatically normalize normals (vectors of surfaces )
	glShadeModel(GL_SMOOTH); // smooth shading

	// Add ambient light
    GLfloat ambientColor[] = { 0.2, 0.2,  0.2, 1.0 };
	glLightModelfv( GL_LIGHT_MODEL_AMBIENT, ambientColor); // ambient lights everywhere with the same amount 
   
	GLfloat mat_ambient[]    = { 1.0, 1.0,  1.0, 1.0 };
    GLfloat mat_specular[]   = { 1.0, 1.0,  1.0, 1.0 };

	glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient );
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular );
    glMaterialf( GL_FRONT, GL_SHININESS, 50.0 );
	// parametry cieniowania (flat daje taki sam kolor)

    glDepthFunc( GL_LESS );
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

	// lighting stuff:

	// Add positioned light
	GLfloat lightColor0[] = { 0.5f, 0.5f, 0.5f, 1.0f};
	GLfloat lightPos0[] = { pacman->x, pacman->y, 2.0f, 1.0f };
	glLightfv(GL_LIGHT0, GL_DIFFUSE,  lightColor0);
    glLightfv(GL_LIGHT0, GL_POSITION, lightPos0);

	// Add directed light:
	GLfloat lightColor1[] = { 0.5f, 0.2f, 0.2f, 1.0f };
	GLfloat lightPos1[] = {GameBoard::CENTER_X, GameBoard::CENTER_Y, 5.0f, 0.0f };
	glLightfv(GL_LIGHT1, GL_DIFFUSE,  lightColor1);
    glLightfv(GL_LIGHT1, GL_POSITION, lightPos1);

	// camera movement stuff:
	// http://gamedev.stackexchange.com/questions/43588/how-to-rotate-camera-centered-around-the-cameras-position
	// M_PI /2 - przesuniecie fazowe w celu dobrego wyswietlenia poczatkowego planszy
	// implementacja operacji: ROLL (theta) (zla!) oraz PITCH (phi) ('w', 's' jest ok)
	if (pacFollowed) 
	{ // look at pacman 
		centerX = pacman->x;
		centerY = pacman->y;
		centerZ = pacman->z;
	}
	else 
	{ // look at the middle of the gameboard
		centerX = GameBoard::CENTER_X;
		centerY = GameBoard::CENTER_Y;
		centerZ = GameBoard::CENTER_Z;
	}

	eyeX = centerX + 5 * sin(theta);
	eyeY = centerY + centerDistance * sin(phi) + 5 * sin(theta);
	eyeZ = centerZ + centerDistance * cos(phi);
	gluLookAt( eyeX, eyeY, eyeZ, centerX, centerY, centerZ, sin(theta), cos(theta), 0 );


	// move the pacman
	pacman->Move();	

	// wall check stops movement
	pacman->WallCheck();

	// coins eating
	if (pacman->Consume())
		board->coinsCount--;

	// ghosts movement algorithms:
	if (((GhostRed*)ghosts[0])->chase)
	{
		// Blinky targets packman current tile coordinates while in chase mode
		(ghosts[0])->targetTileX = pacman->tileX;
		(ghosts[0])->targetTileY = pacman->tileY;
	}
	//for (int i = 0; i < ghosts_count; i++)
	{
		ghosts[0]->Move();
		//ghosts[i]->WallStop();
	}

	// actual pacman, ghosts and board drawing
	glPushMatrix();
		pacman->Draw();
		board->Draw();
		ghosts[0]->Draw(phi,1,0,0); // Blinky
		ghosts[1]->Draw(phi,1,0.753f,0.796f); // Pinky
		ghosts[2]->Draw(phi,0,1,1); // Inky
		ghosts[3]->Draw(phi,1,0.647f,0); // Clyde
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
	static float step = 0.1;
	static float stepZoom = 1;

	// Camera / zooming
	switch (key)
	{
	case 'a':
		// left
		if (theta < -camLRMax)
			return;
		theta -= step;
		break;
       
	case 'w':
		// up
		if (phi > camUpDownMax)
			return;
		phi += step;
		break;
       
	case 'd':     
		// right
		if (theta > camLRMax)
			return;
		theta += step;
		break;
       
	case 's':
		// down
		if (phi < -camUpDownMax)
			return;
		phi -= step;
		break;

	case 'r':
		// zoom in
		if (centerDistance < minZ)
			return;
		centerDistance -= stepZoom;
		//positionz += stepZoom;
		break;

	case 'f':
		// zoom out
		if (centerDistance > maxZ)
			return;
		centerDistance += stepZoom;
		//positionz -= stepZoom;
		break;

	case 'c':
		//follow camera mode
		pacFollowed = pacFollowed ? false : true;
		pacFollowed ? centerDistance = maxZ - 4 : centerDistance = maxZ;
		if(!pacFollowed)
		{
			// reset angles when returning from following mode
			phi = 0;
			theta = 0;
		}
		break;
	}
}

// Mouse handling
void mouse(int button, int state, int x, int y)
{
	if (button == GLUT_RIGHT_BUTTON) {
		exit(0);
	}
}

// Special keys handling (arrows)
void special( int key, int x, int y )
{
	switch( key )
    {
	case GLUT_KEY_LEFT:
		pacman->Turn(180);
        break;

    case GLUT_KEY_RIGHT:   
		pacman->Turn(0);
        break;

    case GLUT_KEY_UP:
		pacman->Turn(90);
        break;
       
    case GLUT_KEY_DOWN:
		pacman->Turn(270);
        break;
    }

	// odrysowanie okna
    reshape( glutGet( GLUT_WINDOW_WIDTH ), glutGet( GLUT_WINDOW_HEIGHT ) );
}

void timer(int v) 
{
	// maybe some visual effects?
}

int main(int argc, char** argv)
{
	glutInit( &argc, argv );
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH); // pojedyncze buforowanie oraz bufor glebokosci ustawiamy
	glutInitWindowPosition( 0, 0 );
	glutInitWindowSize( 1000, 1000 );
	glutCreateWindow( "PackMan" ); // zainicjowany kontekst openGL'owy

	//glutGameModeString( "800x600:16@60" );
	//glutEnterGameMode();

	glutSetCursor(GLUT_CURSOR_NONE);

	glutDisplayFunc( display );
	glutReshapeFunc( reshape ); // trzeba zmienic parametry rzutowania
	glutIdleFunc(display); // scena jest caly czas przeliczana w tle

	glutTimerFunc(40, timer, 1);

	glutSpecialFunc(special);
	glutKeyboardFunc(keyboard);

	// OpenGL objects initialization:
	pacman = new Pac(15,2);
	board = new GameBoard();
	for (int i = 0; i < ghosts_count; i++)
	{
		if (i == 0)
			ghosts[i] = new GhostRed(15, 10, 2);
		else
			ghosts[i] = new Ghost(13 + i , 8, 2);
	}

	init();

	glutMainLoop(); // w momencie wywolania nasz program zaczyna dzialac. Reaguje od tego momentu na zdarzenia.

	return 0;
}