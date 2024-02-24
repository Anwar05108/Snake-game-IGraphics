#include "iGraphics.h"
#define width 1280
#define height 720
int fruitX, fruitY, mode, condition=1, i, j, k=0;
int H_conditon=4, B_condition=2,T_condition=4;
int Dif, game=0, score=0;
int Count;
int headX=465, headY=325;
int gamestate=-1;
int positionX[10000], positionY[10000];
char button[10][15]= {"hs\\play.bmp","hs\\score.bmp","hs\\ins.bmp"};

struct buttonCordinate
{
    int x;
    int y;
} bCordinate[3];

void FruitSpawn()
{
    fruitX = rand() % 930;
    fruitY = rand() % 650;
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

void snake_death()
{
    for (i=Count-1; i>2; i--)
    {

        if (sqrt(pow(positionX[0]-positionX[i],2)+pow(positionY[0]-positionY[i],2))<=5)
            gamestate=1;
    }
}

void position_update()
{
    for (i=Count-2; i>=0; i--)
    {
        positionX[i+1]=positionX[i]+20;
        positionY[i+1]=positionY[i];
        if (i==0)
        {
            positionX[i]=headX;
            positionY[i]=headY;
        }
    }
}

void Draw_Head(int X, int Y)
{
    /*switch(condition)
    {
    case 1:
        H_conditon=1;
    case 2:
        H_conditon=2;
    case 3:
        H_conditon=3;
    case 4:
        H_conditon=4;
    }*/
    switch(H_conditon)
    {
    case 1:
        iShowBMP2(X, Y,"Head2.bmp",1);
    case 2:
        iShowBMP2(X, Y,"Head4.bmp",1);
    case 3:
        iShowBMP2(X, Y,"Head1.bmp",1);
    case 4:
        iShowBMP2(X, Y,"Head3.bmp",1);
    }
}

void Draw_Body(int X, int Y)
{
    switch(B_condition)
    {
    case 1:
        iShowBMP2(X, Y,"Body2.bmp", 255);
    case 2:
        iShowBMP2(X, Y, "Body4.bmp", 255);
    case 3:
        iShowBMP2(X, Y,"Body1.bmp", 255);
    case 4:
        iShowBMP2(X, Y,"Body4.bmp", 255);
    }

}

void Draw_Tail(int X,int Y)
{
    switch(T_condition)
    {
    case 1:
        iShowBMP2(X, Y,"Tail2.bmp", 255);
    case 2:
        iShowBMP2(X, Y,"Tail4.bmp", 255);
    case 3:
        iShowBMP2(X, Y,"Tail1.bmp", 255);
    case 4:
        iShowBMP2(X, Y,"Tail3.bmp", 255);
    }

}

void iDraw()
{

    iClear();
    //homemenu
    if(gamestate==-1)
    {
        iShowBMP(0,0,"Background.bmp");
        for(int i=0; i<3; i++)
        {
            iShowBMP2(bCordinate[i].x,bCordinate[i].y,button[i],255);
        }
    }
    else if(gamestate==0)
    {
        iShowBMP(0,0,"BG1.bmp");
        iShowBMP2(fruitX,fruitY,"Food.bmp", 255);
        position_update();

        /*if (game==0)
        {
            iShowBMP2(headX,headY,"Head4.bmp", 255);
            iShowBMP2(headX+20,headY,"Body4.bmp", 255);
            iShowBMP2(headX+40,headY,"Tail4.bmp", 255);
            game==1;
        }
        else
*/
        {
            for (j=0; j<=Count-1; j++)
            {
                /*
                    if (j==0)
                        iFilledRectangle(positionX[j],positionY[j],25,25);
                    else
                        iShowBMP2(positionX[j],positionY[j],"Body4.bmp", 255);

                */
                if (j==0)
                    Draw_Head(positionX[j],positionY[j]);
                else if (j<Count-1)
                    Draw_Body(positionX[j],positionY[j]);
                else
                    Draw_Tail(positionX[j],positionY[j]);
            }
        }
        iSetColor(255,127,39);
        iFilledRectangle(10,50,950,20);
        iFilledRectangle(10,50,20,650);
        iFilledRectangle(950,50,20,650);
        iFilledRectangle(10,700,960,20);
        snake_death();
        if (positionX[0]<10 || positionY[0]<50 || positionY[0]>650 || positionX[0]>970)
            gamestate=1;
        if (sqrt(pow(positionX[0]-fruitX,2)+pow(positionY[0]-fruitY,2))<=10)
        {
            FruitSpawn();
            score+=10;
            Count++;
            position_update();
        }
    }
    else if (gamestate==1)
    {
        iClear();
        iSetColor(255,255,255);
        iText(600,360,"GAME OVER",GLUT_BITMAP_TIMES_ROMAN_24);
        iText(600,300,"YOUR SCORE is ",GLUT_BITMAP_TIMES_ROMAN_24);
        //printf("%d",score);
    }
}

void iMouseMove(int mx, int my)
{
    //place your codes here
}

void iMouse(int button, int state, int mx, int my)
{
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        //place your codes here

        if(mx >=bCordinate[0].x && mx <= bCordinate[0].x+260 && my >=bCordinate[0].y &&my<=bCordinate[0].y+90);
        gamestate=0;
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
    if (key == GLUT_KEY_END || key==GLUT_KEY_HOME)
        exit(0);
    if(mode!=2 && key == GLUT_KEY_RIGHT)
    {
        mode=1;
        condition=1;
        H_conditon=1;
        T_condition=1;
        B_condition=1;
    }
    else if(mode!=1 && key == GLUT_KEY_LEFT)
    {
        mode=2;
        condition=2;
        H_conditon=2;
        T_condition=2;
        B_condition=2;
    }
    else if(mode!=4 && key == GLUT_KEY_UP)
    {
        mode=3;
        condition=3;
        H_conditon=3;
        T_condition=3;
        B_condition=3;
    }
    else if(mode !=3 && key == GLUT_KEY_DOWN)
    {
        mode=4;
        condition=4;
        H_conditon=4;
        T_condition=4;
        B_condition=4;
    }
    //place your codes for other keys here
}

int main()
{
    Dif=5;
    int ychange=150;
    for(int i=2; i>=0; i--)
    {
        bCordinate[i].x=150;
        bCordinate[i].y=ychange;
        ychange+=150;
    }
    FruitSpawn();
    Count=3;
    iSetTimer(0,position);
    iSetTimer(0,position_update);
    iInitialize(width, height, "Ultimate Snake");
    return 0;
}

