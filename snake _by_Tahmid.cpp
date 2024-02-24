

/*Skip to content
Using Gmail with screen readers

Conversations
0.05 GB (0%) of 15 GB used
Manage
Terms · Privacy · Program Policies
Last account activity: 10 days ago
Details*/

#include "iGraphics.h"
#define width 1280
#define height 720
int fruitX, fruitY, mode, condition=1, i, j, k;
int Dif, game=0, score=0;
int Count=3;
int headX=640, headY=360, tempX, tempY;
int tail_positionX[10000], tail_positionY[10000];
int tail_length=0;

void FruitSpawn()
{
    fruitX = rand() % width;
    fruitY = rand() % height;
}

void position()
{
    switch(mode)
    {
    case 1:
            headX+=Dif;
        break;
    case 2:
            headX-=Dif;
        break;
    case 3:
            headY+=Dif;
        break;
    case 4:
            headY-=Dif;
        break;
    }
}

/*void death()
{
    for (i=0; i<tail_length; i++)
    {
        tail_positionX=tail_position[i][0];
        tail_positionY=tail_position[i][1];
        if (snakeX-tail_positionX<1 || snakeY-tail_positionY<1)
            exit(0);
    }
}
*/

void position_update()
{
    if(mode==1)
    {
        if (condition==3)
            headY+=5;
        else if (condition==4)
            headY-=5;
    }
    else if(mode==2)
    {
        if (condition==3)
            headY+=5;
        else if (condition==4)
            headY-=5;
    }
    else if(mode==3)
    {
        if (condition==1)
            headX+=5;
        else if (condition==2)
            headX-=5;
    }
    else if(mode==3)
    {
        if (condition==1)
            headX+=5;
        else if (condition==2)
            headX-=5;
    }
}

void iDraw()
{
    iClear();
    iSetColor(255,255,255);
    iFilledRectangle(fruitX,fruitY,10,10);
    tempX=headX;
    tempY=headY;
    for (j=0; j<=Count-1; j++)
    {
        if (j==0)
            iSetColor(0, 0, 255);
        else
            iSetColor(255,255,255);
         if (condition==1)
            iFilledRectangle(headX+10*j,headY,10,10);
        if (condition==2)
            iFilledRectangle(headX-10*j,headY,10,10);
        if (condition==3)
            iFilledRectangle(headX,headY+10*j,10,10);
        if (condition==4)
            iFilledRectangle(headX,headY-10*j,10,10);
    }
    position_update();
    iSetColor(0,0,255);
    iRectangle(0,0,1280,720);
    iRectangle(1,1,1279,719);
    iRectangle(2,2,1278,718);
    iRectangle(3,3,1277,717);
    iRectangle(4,4,1276,716);
    if (headX<0 || headY<0 || headY>height || headX>width)
        exit(0);
    if (abs(headX-fruitX)<=8 && abs(headY-fruitY)<=8)
    {
        FruitSpawn();
        score+=10;
        Count++;
        iSetColor(255,255,255);
        iClear();
        iFilledRectangle(fruitX,fruitY,10, 10);
    }
}

void iMouseMove(int mx, int my)
{
    printf("x = %d, y= %d\n",mx,my);
    //place your codes here
}

void iMouse(int button, int state, int mx, int my)
{
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        //place your codes here

    }
    if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
    {
        //place your codes here

    }
}

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
}

void iSpecialKeyboard(unsigned char key)
{
    if (key == GLUT_KEY_END)
        exit(0);
    if(mode!=2 && key == GLUT_KEY_RIGHT)
    {
        mode=1;
        condition=1;
    }
    else if(mode!=1 && key == GLUT_KEY_LEFT)
    {
        mode=2;
        condition=2;
    }
    else if(mode!=4 && key == GLUT_KEY_UP)
    {
        mode=3;
        condition=3;
    }
    else if(mode !=3 && key == GLUT_KEY_DOWN)
    {
        mode=4;
        condition=4;
    }
    //place your codes for other keys here
}

int main()
{
    Dif=8;

    FruitSpawn();
    iSetTimer(40,position);
    iInitialize(width, height, "Ultimate Snake");
    return 0;
}
//Ultimate Snake.cpp
//Displaying Ultimate Snake.cpp.
