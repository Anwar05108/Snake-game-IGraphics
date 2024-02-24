/*
	author: S. M. Shahriar Nirjon
	last modified: August 8, 2008
*/
# include "iGraphics.h"
# include "gl.h"
#include<stdlib.h>
#include<time.h>

int i;

int g_sunX, g_sunY, g_sunR;
int g_planetOrbitR[9], g_planetR[9], g_planetSweepAngle[9];
int g_satelliteOrbitR[3], g_satelliteR[3], g_satelliteSweepAngle[3];

int color_a[9],color_b[9],color_c[9];

void drawStar(int x, int y, int r) {
    iSetColor(255, 255, 0);
    iFilledCircle(x, y, r);
}

void drawOrbit(int x, int y, int r) {
    iSetColor(255, 255, 255);
    //iCircle(x, y, r);
    iEllipse(x,y,3*r,r);
}

void drawPlanet(int starX, int starY, int orbitR, int planetR, int sweepAngle, int a, int b, int c) {
    double pi = 2*acos(0);
    double sweepRadian = sweepAngle * pi / 180;
    int planetX = starX + orbitR * 3* cos(sweepRadian);
    int planetY = starY + orbitR * sin(sweepRadian);

    iSetColor(a, b, c);
    iFilledCircle(planetX, planetY, planetR);
}

void drawSatellite(
    int starX,
    int starY,
    int planetOrbitR,
    int planetSweepAngle,
    int satelliteOrbitR,
    int satelliteR,
    int satelliteSweepAngle) {
    double pi = 2*acos(0);
    double planetSweepRadian = planetSweepAngle * pi / 180;
    double satelliteSweepRadian = satelliteSweepAngle * pi / 180 + planetSweepRadian;

    int planetX = starX + planetOrbitR * 3* cos(planetSweepRadian);
    int planetY = starY + planetOrbitR * sin(planetSweepRadian);

    int satelliteX = planetX + satelliteOrbitR * cos(satelliteSweepRadian);
    int satelliteY = planetY + satelliteOrbitR * sin(satelliteSweepRadian);

    iSetColor(200, 200, 200);
    iFilledCircle(satelliteX, satelliteY, satelliteR);
}

/*
	function iDraw() is called again and again by the system.
*/
void iDraw()
{
	//place your drawing codes here

	iClear();
	srand (time(NULL));

	drawStar(g_sunX, g_sunY, g_sunR);
	for (i=0;i<9;i++) drawOrbit(g_sunX, g_sunY, g_planetOrbitR[i]);
	for (i=0;i<9;i++) drawPlanet(g_sunX, g_sunY, g_planetOrbitR[i], g_planetR[i], g_planetSweepAngle[i],color_a[i],color_b[i],color_c[i]);
	drawSatellite(
        g_sunX,
        g_sunY,
        g_planetOrbitR[0],
        g_planetSweepAngle[0],
        g_satelliteOrbitR[0],
        g_satelliteR[0],
        g_satelliteSweepAngle[0]
        );
    for(i=1;i<3;i++) drawSatellite(
        g_sunX,
        g_sunY,
        g_planetOrbitR[3],
        g_planetSweepAngle[3],
        g_satelliteOrbitR[i],
        g_satelliteR[i],
        g_satelliteSweepAngle[i]
        );

	iSetColor(255, 255, 255);
	iText(10, 10, "Press p for pause, r for resume, END for exit.");
}

/*
	function iMouseMove() is called when the user presses and drags the mouse.
	(mx, my) is the position where the mouse pointer is.
*/
void iMouseMove(int mx, int my)
{
	//place your codes here
}

/*
	function iMouse() is called when the user presses/releases the mouse.
	(mx, my) is the position where the mouse pointer is.
*/
void iMouse(int button, int state, int mx, int my)
{
	if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		//place your codes here
	}
	if(button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
	{
		//place your codes here
	}
}

/*
	function iKeyboard() is called whenever the user hits a key in keyboard.
	key- holds the ASCII value of the key pressed.
*/
void iKeyboard(unsigned char key)
{
	if(key == 'p')
	{
		//do something with 'q'
		iPauseTimer(0);
	}
	if(key == 'r')
	{
		iResumeTimer(0);
	}
	//place your codes for other keys here
}

/*
	function iSpecialKeyboard() is called whenver user hits special keys like-
	function keys, home, end, pg up, pg down, arraows etc. you have to use
	appropriate constants to detect them. A list is:
	GLUT_KEY_F1, GLUT_KEY_F2, GLUT_KEY_F3, GLUT_KEY_F4, GLUT_KEY_F5, GLUT_KEY_F6,
	GLUT_KEY_F7, GLUT_KEY_F8, GLUT_KEY_F9, GLUT_KEY_F10, GLUT_KEY_F11, GLUT_KEY_F12,
	GLUT_KEY_LEFT, GLUT_KEY_UP, GLUT_KEY_RIGHT, GLUT_KEY_DOWN, GLUT_KEY_PAGE UP,
	GLUT_KEY_PAGE DOWN, GLUT_KEY_HOME, GLUT_KEY_END, GLUT_KEY_INSERT
*/
void iSpecialKeyboard(unsigned char key)
{

	if(key == GLUT_KEY_END)
	{
		exit(0);
	}
	//place your codes for other keys here
}

void movePlanets(){
    const int g_dPlanetSweepAngle = 1;
    int g_dSatelliteSweepAngle[] = {10,15,7};
    for (i=0;i<9;i++) g_planetSweepAngle[i] = (g_planetSweepAngle[i] + (10-i)*g_dPlanetSweepAngle)%360;
    for(i=0;i<3;i++) g_satelliteSweepAngle[i] = (g_satelliteSweepAngle[i] + g_dSatelliteSweepAngle[i])%360;
}

int main()
{
    const int CX_MAX = 1380;
    const int CY_MAX = 720;

    // Initialize Sun's position and size.
    g_sunX = CX_MAX/2;
    g_sunY = CY_MAX/2;
    g_sunR = 25;
    for(i=0;i<9;i++)
    {
        color_a[i]=rand()%256;
        color_b[i]=rand()%256;
        color_c[i]=rand()%256;
    }

    // Initialize earth's orbit and radius
    for (i=0;i<9;i++) {
    g_planetOrbitR[i] = 30+25*i;
    g_planetR[i] = 7+rand()%7;
    //g_planetSweepAngle[i] = 45;
}
    g_planetSweepAngle[0]=0;
    g_planetSweepAngle[1]=45;
    g_planetSweepAngle[2]=275;
    g_planetSweepAngle[3]=190;
    g_planetSweepAngle[4]=68;
    g_planetSweepAngle[5]=230;
    g_planetSweepAngle[6]=23;
    g_planetSweepAngle[7]=180;
    g_planetSweepAngle[8]=90;
    // Initialize moon's orbit and radius
    g_satelliteOrbitR[0] = 30;
    g_satelliteR[0] = 5;
    g_satelliteOrbitR[1] = 15;
    g_satelliteR[1] = 3;
    g_satelliteOrbitR[2] = 25;
    g_satelliteR[2] = 5;

    //g_planetSweepAngle = 45;

	//place your own initialization codes here.
	iSetTimer(40, movePlanets);
	iInitialize(CX_MAX, CY_MAX, "Solar system!");

	return 0;
}

