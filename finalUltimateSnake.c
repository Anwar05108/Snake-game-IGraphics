#include "iGraphics.h"
#include<stdlib.h>
#define width 1280
#define height 720
int fruitX, fruitY, mode, condition=1, i, j, b,count_score=1;
int Dif, game=0, score=0;
int Count;
int headX=465, headY=325;
int gamestate=-1;
int positionX[1280*720], positionY[1280*720], Condition[720*1280];
char button[10][15]= {"hs\\play.bmp","hs\\score.bmp","hs\\ins.bmp","hs\\exit.bmp"};
char score_str[100];


struct buttonCordinate
{
    int x;
    int y;
} bCordinate[4];

void FruitSpawn()
{
    fruitX=rand()%850+60;
    fruitY=rand()%550+80;
//    fruitX = temp_randX>=0&&temp_randX<200? ((temp_randX+120) % 920):temp_randX%920;
//    fruitY = temp_randY>=0&&temp_randY<200? ((temp_randY+120) % 625):temp_randY%625;

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

        if (sqrt(pow(positionX[0]-positionX[i],2)+pow(positionY[0]-positionY[i],2))<=10)
            gamestate=3;
    }
}
//void position_update()
//{
//    for (i=Count-2; i>=0; i--)
//    {
//        positionX[i+1]=positionX[i];
//        positionY[i+1]=positionY[i];
//        if (i==0)
//        {
//            positionX[i]=headX;
//            positionY[i]=headY;
//        }
//    }
//}



void position_update()
{
    for (i=Count-1; i>=0; i--)
    {
        Condition[i+1]=Condition[i];
        if (mode==2)
        {
            positionX[i+1]=positionX[i]+10;
            positionY[i+1]=positionY[i];
        }
        else if (mode==1)
        {
            positionX[i+1]=positionX[i]-10;
            positionY[i+1]=positionY[i];
        }
        else if (mode==3)
        {
            positionX[i+1]=positionX[i];
            positionY[i+1]=positionY[i]-10;
        }
        else
        {
            positionX[i+1]=positionX[i];
            positionY[i+1]=positionY[i]+10;
        }
        if (i==0)
        {
//        {    fruitX = temp_randX>0&&temp_randX<50? ((temp_randX+40) % 920):temp_randX%920;

            positionX[i]=headX;
            positionY[i]=headY;
            Condition[i]=condition;
        }
    }
}


//int Draw_Head(int X, int Y, int condition)
//{
//    switch(condition)
//    {
//    case 1:
//        iShowBMP2(X, Y,"Head2.bmp", 255);
//    case 2:
//        iShowBMP2(X, Y,"Head4.bmp", 255);
//    case 3:
//        iShowBMP2(X, Y,"Head1.bmp", 255);
//    case 4:
//        iShowBMP2(X, Y,"Head3.bmp", 255);
//    }
//}
//
//int Draw_Body(int X, int Y, int condition)
//{
//    switch(condition)
//    {
//    case 1:
//        iShowBMP2(X, Y,"Body2.bmp", 255);
//    case 2:
//        iShowBMP2(X, Y, "Body4.bmp", 255);
//    case 3:
//        iShowBMP2(X, Y,"Body1.bmp", 255);
//    case 4:
//        iShowBMP2(X, Y,"Body4.bmp", 255);
//    }
//
//}
//
//int Draw_Tail(int X,int Y, int condition)
//{
//    switch(condition)
//    {
//    case 1:
//        iShowBMP2(X, Y,"Tail2.bmp", 255);
//    case 2:
//        iShowBMP2(X, Y,"Tail4.bmp", 255);
//    case 3:
//        iShowBMP2(X, Y,"Tail1.bmp", 255);
//    case 4:
//        iShowBMP2(X, Y,"Tail3.bmp", 255);
//    }
//}


void iDraw()
{
//    char score_str[100];
    iClear();
    //homemenu
    if(gamestate==-1)
    {
        iShowBMP(0,0,"Background.bmp");
        for(int i=0; i<4; i++)
        {
            iShowBMP2(bCordinate[i].x,bCordinate[i].y,button[i],255);
        }
    }
//    else if(gamestate==0)
//    {
//       iShowBMP(0,0,"BG1.bmp");
//       iShowBMP2(470,340,)
//    }
    else if(gamestate==0)
    {
        iShowBMP(0,0,"BG1.bmp");
        if(count_score%5==0)
            iShowBMP2(fruitX,fruitY,"bonus5.bmp",0);
        else
            iShowBMP2(fruitX,fruitY,"Food.bmp", 255);
        //char score_str[100];
//        sprintf(score_str,"%d",score);
        itoa(score,score_str,10);
        iSetColor(0,0,0);
        iText(1002,650,"score:",GLUT_BITMAP_TIMES_ROMAN_24);
        iText(1072,650,score_str,GLUT_BITMAP_TIMES_ROMAN_24);
        /*
        if (game==0)
        {
            iShowBMP2(headX,headY,"Head4.bmp", 255);
            iShowBMP2(headX+20,headY,"Body4.bmp", 255);
            iShowBMP2(headX+40,headY,"Tail4.bmp", 255);
            game==1;
        }
        else
            */
        {
            for (j=Count-1; j>=0; j--)
            {
                if (j==0)
                {
                    if (Condition[j]==1)
                        iShowBMP2(positionX[j], positionY[j],"Head2.bmp", 255);
                    else if (Condition[j]==2)
                        iShowBMP2(positionX[j], positionY[j],"Head4.bmp", 255);
                    else if (Condition[j]==3)
                        iShowBMP2(positionX[j], positionY[j],"Head1.bmp", 255);
                    else
                        iShowBMP2(positionX[j], positionY[j],"Head3.bmp", 255);
                }
                else if (j<Count-1)
                {
                    if (Condition[j]==1)
                        iShowBMP2(positionX[j], positionY[j],"Body2.bmp", 255);
                    else if (Condition[j]==2)
                        iShowBMP2(positionX[j], positionY[j], "Body4.bmp", 255);
                    else if (Condition[j]==3)
                        iShowBMP2(positionX[j], positionY[j],"Body1.bmp", 255);
                    else
                        iShowBMP2(positionX[j], positionY[j],"Body3.bmp", 255);
                }
                else
                {
                    if (Condition[j]==1)
                        iShowBMP2(positionX[j], positionY[j],"Tail2.bmp", 255);
                    else if (Condition[j]==2)
                        iShowBMP2(positionX[j], positionY[j],"Tail4.bmp", 255);
                    else if (Condition[j]==3)
                        iShowBMP2(positionX[j], positionY[j],"Tail1.bmp", 255);
                    else
                        iShowBMP2(positionX[j], positionY[j],"Tail3.bmp", 255);
                }
            }
        }
        iSetColor(255,127,39);
        iFilledRectangle(10,50,950,20);
        iFilledRectangle(10,50,20,650);
        iFilledRectangle(950,50,20,650);
        iFilledRectangle(10,700,960,20);
        snake_death();
        if (positionX[0]<10 || positionY[0]<50 || positionY[0]>680 || positionX[0]>950)
            gamestate=3;
        if (sqrt(pow(positionX[0]-fruitX,2)+pow(positionY[0]-fruitY,2))<=10)
        {

            FruitSpawn();

            if(count_score%5==0)
                score+=20;
            else
                score+=10;
            count_score++;
            Count++;
            position_update();
        }
    }
    else if(gamestate==1)
    {
        iShowBMP(0,0,"highscore2.bmp");
    }
    else if(gamestate==2)
    {
        iShowBMP(0,0,"images (3).bmp");
        iShowBMP2(5,620,"backbutton4.bmp",255);
    }
    else if (gamestate==3)
    {
        iClear();
//        FILE *fs;
        iShowBMP(0,0,"snakegameover.bmp");
        iSetColor(255,255,255);
//        iText(600,360,"GAME OVER",GLUT_BITMAP_TIMES_ROMAN_24);
        iText(547,300,"YOUR SCORE is",GLUT_BITMAP_TIMES_ROMAN_24);
        iText(725,300,score_str,GLUT_BITMAP_TIMES_ROMAN_24);
//        fs=fopen("highscore.txt","a");
//        int h_score=atoi(score_str);
//        fprintf(fs,"%d",h_score);
//        fclose(fs);

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


        if(mx >=bCordinate[0].x && mx <= bCordinate[0].x+260 && my >=bCordinate[0].y &&my<=bCordinate[0].y+90)
        {

            gamestate=0;
        }
        else if(mx >=bCordinate[1].x && mx <= bCordinate[1].x+260 && my >=bCordinate[1].y &&my<=bCordinate[1].y+90)
        {
            gamestate=1;
        }
        else if(mx >=bCordinate[2].x && mx <= bCordinate[2].x+260 && my >=bCordinate[2].y &&my<=bCordinate[2].y+90)
        {
            gamestate=2;
        }
        else if(mx >=bCordinate[3].x && mx <= bCordinate[3].x+260 && my >=bCordinate[3].y &&my<=bCordinate[3].y+90)
        {
            exit(0);
        }
        else if(mx>=30 && mx<= 215 && my >= 75 && my <= 130)
        {
            gamestate=-1;
        }
        else if(mx>=5 && mx<= 205 && my>= 620 && my<= 620+99)
        {
            gamestate=-1;
        }
        printf("%d %d\n",mx,my);

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
    {iShowBMP(10,500,"backbutton4.bmp");
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
    Dif=10;
    int ychange=100;
    for(int i=3; i>=0; i--)
    {
        bCordinate[i].x=50;
        bCordinate[i].y=ychange;
        ychange+=150;
    }
    FruitSpawn();
    Count=3;
    iSetTimer(50
              ,position);
//    iSetTimer(50,FruitSpawn);
    iSetTimer(100,position_update);
    iSetTimer(10,snake_death);
    FILE *fs;
    fs=fopen("highscore.txt","a");
    int h_score=atoi(score_str);
    fprintf(fs,"%d\n",h_score);
    fclose(fs);

    // PlaySound("snd2.wav", NULL ,  SND_LOOP | SND_ASYNC);
    iInitialize(width, height, "Ultimate Snake");
    return 0;
}


