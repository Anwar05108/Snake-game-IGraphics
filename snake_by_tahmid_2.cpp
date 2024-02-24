#include "iGraphics.h"
#define width 1280
#define height 720
int fruitX, fruitY, mode, condition=1, i, j;
int Dif, game=1, score=0;
int Count;
int headX=640, headY=360;
int positionX[10000], positionY[10000];


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

/*void snake_death()
{
    for (i=1; i<=Count-1; i++)
    {
        if (positionX[0]-positionX[i]<=4 && positionY[0]-positionY[i]<=4)
            exit(0);
    }
}
*/

void position_update()
{
    for (i=Count-2; i>=0; i--)
    {
        positionX[i+1]=positionX[i];
        positionY[i+1]=positionY[i];
        if (i==0)
        {
            positionX[i]=headX;
            positionY[i]=headY;
        }
    }
}

void iDraw()
{
    iClear();
    iSetColor(255,255,255);
    iFilledRectangle(fruitX,fruitY,10,10);
    for (j=0; j<=Count-1; j++)
    {
        if (j==0)
            iSetColor(0, 0, 255);
        else
            iSetColor(255,255,255);
        iFilledRectangle(positionX[j],positionY[j],10,10);
    }
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
        Count+=8;
        position_update();
        iSetColor(255,255,255);
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
    Count=3;
    iSetTimer(20,position);
    iSetTimer(20,position_update);
    iInitialize(width, height, "Ultimate Snake");
    return 0;
}
