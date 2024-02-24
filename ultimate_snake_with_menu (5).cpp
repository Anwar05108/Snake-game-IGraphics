#include "iGraphics.h"
#include<conio.h>
#include<stdlib.h>
#define width 1280
#define height 720
#define hm -1
#define nm 5
#define g 0
#define gn 4
#define hs 1
#define ins 2
#define over 3
#define enter_name 6
#define gn1 7
#define d_21 ((headX>=300 && headX<=(300+5)) && (headY>=400 && headY<=(400+400)))
#define d_1 ((positionX[0]>=100 && positionX[0]<=(100+6)) && (positionY[0]>=500 && positionY[0]<=(500+50)))
#define d_2 ((positionX[0]>=100 && positionX[0]<=(100+6)) && (positionY[0]>=200 && positionY[0]<=(200+50)))
#define d_3 ((positionX[0]>=300 && positionX[0]<=(300+6)) && (positionY[0]>=300 && positionY[0]<=(300+200)))
#define d_4 ((positionX[0]>=500 && positionX[0]<=(500+6)) && (positionY[0]>=500 && positionY[0]<=(500+50)))
#define d_5 ((positionX[0]>=500 && positionX[0]<=(500+6)) && (positionY[0]>=200 && positionY[0]<=(200+50)))
#define d_6 ((positionX[0]>=700 && positionX[0]<=(700+6)) && (positionY[0]>=300 && positionY[0]<=(300+200)))
#define d_7 ((positionX[0]>=900 && positionX[0]<=(900+6)) && (positionY[0]>=200 && positionY[0]<=(200+50)))
#define d_8 ((positionX[0]>=900 && positionX[0]<=(900+6)) && (positionY[0]>=500 && positionY[0]<=(500+50)))
int fruitX, fruitY, mode, condition=1, i, j, b,count_score=1;
int Dif, game=0, score=0,p=0;
int Count,call=1,bonusstate=1,bonusX,bonusY,timecall=1;
int headX=465, headY=325;
int gamestate=-1,add_score_count=0;
int positionX[1280*720], positionY[1280*720], Condition[720*1280];
char button[10][15]= {"hs\\play.bmp","hs\\score.bmp","hs\\ins.bmp","hs\\exit.bmp"};
char score_str[100];
int delay_count=0,len=0,name_mode=0;
char h_name[10],str2[10];
typedef struct
{
    char name[15],score_value[15];

} h_score;
h_score score_var[30];
int cmp(const void *a,const void *b)
{
    h_score *A=(h_score*)a;
    h_score *B=(h_score*)b;
    if(A->score_value>B->score_value)
        return 1;
    else
        return 0;



}

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
void bonusSpawn()
{
    bonusX=rand()%850+60;
    bonusY=rand()%550+80;
}

void position()
{
    if(p)
        return;
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
//    for (i=Count-1; i>=0; i--)
//    {
//        Condition[i+1]=Condition[i];
//        if (mode==2)
//        {
//            positionX[i+1]=positionX[i]+10;
//            positionY[i+1]=positionY[i];
//        }
//        else if (mode==1)
//        {
//            positionX[i+1]=positionX[i]-10;
//            positionY[i+1]=positionY[i];
//        }
//        else if (mode==3)
//        {
//            positionX[i+1]=positionX[i];
//            positionY[i+1]=positionY[i]-10;
//        }
//        else
//        {
//            positionX[i+1]=positionX[i];
//            positionY[i+1]=positionY[i]+10;
//        }
//        if (i==0)
//        {
////        {    fruitX = temp_randX>0&&temp_randX<50? ((temp_randX+40) % 920):temp_randX%920;
//
//            positionX[i]=headX;
//            positionY[i]=headY;
//            Condition[i]=condition;
//        }
//    }
//}
void position_update()
{
    if(p)
        return;
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
    if(gamestate==-1)
    {
        iShowBMP(0,0,"Background.bmp");
        for(int i=0; i<4; i++)
        {
            iShowBMP2(bCordinate[i].x,bCordinate[i].y,button[i],255);
        }
    }
    else if(gamestate==enter_name)
    {
        iSetColor(255,255,255);
        iText(500,500,"enter your name");
        iText(500,400,h_name);
    }
    else if(gamestate==0)
    {
        iShowBMP(0,0,"BG1.bmp");
        if(count_score%5==0)
        {
            if(call % 300 ==0 )
            {
                bonusstate=0;
            }
            if(bonusstate)
            {
                iShowBMP2(bonusX,bonusY,"bonus4.bmp",0);
            }
            call++;
            // printf("%d\n",call);
        }
        iShowBMP2(fruitX,fruitY,"Food.bmp", 255);
        itoa(score,score_str,10);
        iSetColor(0,0,0);
        iText(1002,650,"score:",GLUT_BITMAP_TIMES_ROMAN_24);
        iText(1072,650,score_str,GLUT_BITMAP_TIMES_ROMAN_24);
        //iFilledRectangle(fruitX,fruitY,10,10);
        for (j=0; j<=Count-1; j++)
        {
            if (j==0)
                iSetColor(0, 0, 255);
            else
                iSetColor(0,255,0);
            iFilledRectangle(positionX[j],positionY[j],10,10);
        }
        iSetColor(255,127,39);
        iFilledRectangle(10,50,950,20);
        iFilledRectangle(10,50,20,650);
        iFilledRectangle(950,50,20,650);
        iFilledRectangle(10,700,960,20);

        snake_death();
        if (positionX[0]<30 || positionY[0]<70 || positionY[0]>680 || positionX[0]>950)
            gamestate=3;
        if (positionX[0] >= fruitX && positionX[0] <= (fruitX+25) && positionY[0] >= fruitY && positionY[0] <= (fruitY+25) )
        {
            FruitSpawn();
            score+=10;
            count_score++;
            Count+=2;
            position_update();
            call=1;
            bonusstate=1;
            delay_count=0;
        }
        if (positionX[0] >= bonusX && positionX[0] <= (bonusX+57) && positionY[0] >= bonusY && positionY[0] <= (bonusY+60) )
        {

            delay_count++;
            bonusSpawn();
            count_score++;
            score+=20;
            Count+=4;
            call=1;




//            delay_count++;
//
//            if(delay_count=1);
//            {
//                count_score++;
//                score+=20;
//            }
//
//            //Count+=2;
//            call=1;
//            //position_update();
//            bonusstate=0;
//            if(count_score%5==0)
//            {
//                bonusSpawn();
//            }


        }
        printf("%d\n",count_score);
    }
    else if(gamestate==gn1)
    {
        iShowBMP(0,0,"BG1.bmp");
        if(count_score%5==0)
        {
            if(call % 300 ==0 )
            {
                bonusstate=0;
            }
            if(bonusstate)
            {
                iShowBMP2(bonusX,bonusY,"bonus4.bmp",0);
            }
            call++;
            // printf("%d\n",call);
        }
        iShowBMP2(fruitX,fruitY,"Food.bmp", 255);
        itoa(score,score_str,10);
        iSetColor(0,0,0);
        iText(1002,650,"score:",GLUT_BITMAP_TIMES_ROMAN_24);
        iText(1072,650,score_str,GLUT_BITMAP_TIMES_ROMAN_24);
        //iFilledRectangle(fruitX,fruitY,10,10);
        for (j=0; j<=Count-1; j++)
        {
            if (j==0)
                iSetColor(0, 0, 255);
            else
                iSetColor(0,255,0);
            iFilledRectangle(positionX[j],positionY[j],10,10);
        }
        iSetColor(255,127,39);
        iFilledRectangle(10,50,950,20);
        iFilledRectangle(10,50,20,650);
        iFilledRectangle(950,50,20,650);
        iFilledRectangle(10,700,960,20);
        iSetColor(23,34,198);
        iFilledRectangle(300,400,400,5);
        iFilledRectangle(405,300,5,200);
        iFilledRectangle(600,300,5,200);

        snake_death();
        if (positionX[0]<30 || positionY[0]<70 || positionY[0]>680 || positionX[0]>950 || (d_21))
            gamestate=3;
        if (positionX[0] >= fruitX && positionX[0] <= (fruitX+25) && positionY[0] >= fruitY && positionY[0] <= (fruitY+25) )
        {
            FruitSpawn();
            score+=10;
            count_score++;
            Count+=2;
            position_update();
            call=1;
            bonusstate=1;
            delay_count=0;
        }
        if (positionX[0] >= bonusX && positionX[0] <= (bonusX+57) && positionY[0] >= bonusY && positionY[0] <= (bonusY+60) )
        {

            delay_count++;
            bonusSpawn();
            count_score++;
            score+=20;
            Count+=4;
            call=1;




//            delay_count++;
//
//            if(delay_count=1);
//            {
//                count_score++;
//                score+=20;
//            }
//
//            //Count+=2;
//            call=1;
//            //position_update();
//            bonusstate=0;
//            if(count_score%5==0)
//            {
//                bonusSpawn();
//            }


        }
        printf("%d\n",count_score);
    }

    else if(gamestate==gn)
    {
        iShowBMP(0,0,"BG1.bmp");
        if(count_score%5==0)
        {
            if(call % 300 ==0 )
            {
                bonusstate=0;
            }
            if(bonusstate)
            {
                iShowBMP2(bonusX,bonusY,"bonus4.bmp",0);
            }
            call++;
            // printf("%d\n",call);
        }
        iShowBMP2(fruitX,fruitY,"Food.bmp", 255);
        itoa(score,score_str,10);
        iSetColor(0,0,0);
        iText(1002,650,"score:",GLUT_BITMAP_TIMES_ROMAN_24);
        iText(1072,650,score_str,GLUT_BITMAP_TIMES_ROMAN_24);
        //iFilledRectangle(fruitX,fruitY,10,10);
        for (j=0; j<=Count-1; j++)
        {
            if (j==0)
                iSetColor(0, 0, 255);
            else
                iSetColor(0,255,0);
            iFilledRectangle(positionX[j],positionY[j],10,10);
        }
        iSetColor(255,127,39);
        iFilledRectangle(10,50,950,20);
        iFilledRectangle(10,50,20,650);
        iFilledRectangle(950,50,20,650);
        iFilledRectangle(10,700,960,20);
        iSetColor(100,0,234);
        iFilledRectangle(300,300,8,200);
        iFilledRectangle(700,300,8,200);
        iFilledRectangle(100,500,6,50);
        iFilledRectangle(100,200,6,50);
        iFilledRectangle(500,500,6,50);
        iFilledRectangle(900,200,6,50);
        iFilledRectangle(900,500,6,50);
        iFilledRectangle(500,200,6,50);


        snake_death();
        if (positionX[0]<30 || positionY[0]<70 || positionY[0]>680 || positionX[0]>950 || (d_1) || (d_2) ||(d_3) ||(d_4)||(d_5)||(d_6)||(d_7)||(d_8))
            gamestate=3;
        if (positionX[0] >= fruitX && positionX[0] <= (fruitX+25) && positionY[0] >= fruitY && positionY[0] <= (fruitY+25) )
        {
            FruitSpawn();
            score+=10;
            count_score++;
            Count+=2;
            position_update();
            call=1;
            bonusstate=1;
            delay_count=0;
        }
        if (positionX[0] >= bonusX && positionX[0] <= (bonusX+57) && positionY[0] >= bonusY && positionY[0] <= (bonusY+60) )
        {
            delay_count++;

            bonusSpawn();
            count_score++;
            score+=20;
            Count+=4;
            call=1;
            //position_update();
            bonusstate=0;
//            if(count_score%5==0)
//            {
//
//            }
        }
    }
    else if(gamestate==1)
    {

        iShowBMP(0,0,"highscore2.bmp");
        FILE *fp;
        fp=fopen("highscore.txt","r");
        //static int i=0;

        for(int i=0; i<3; i++)
        {

            fscanf(fp,"%s",score_var[i].name);
                        fscanf(fp,"%s",score_var[i].score_value);

            printf("%s %s\n",score_var[i].name,score_var[i].score_value);

        }

        //qsort(score_var,3,sizeof(h_score),cmp);
        for(int j=0;j<i; j++)
            printf("%s %s\n",score_var[i].name,score_var[i].score_value);
        iSetColor(0,0,90);


        iText(300,520,score_var[0].name,GLUT_BITMAP_TIMES_ROMAN_24);
        iText(400,520,score_var[0].score_value,GLUT_BITMAP_TIMES_ROMAN_24);
        iText(300,420,score_var[1].name,GLUT_BITMAP_TIMES_ROMAN_24);
        iText(400,420,score_var[1].score_value,GLUT_BITMAP_TIMES_ROMAN_24);
        iText(300,320,score_var[2].name,GLUT_BITMAP_TIMES_ROMAN_24);
        iText(400,320,score_var[2].score_value,GLUT_BITMAP_TIMES_ROMAN_24);
//            iText(300,220,score_var[3].name,GLUT_BITMAP_TIMES_ROMAN_24);
//            iText(400,220,score_var[3].score_value,GLUT_BITMAP_TIMES_ROMAN_24);

        //iText(500,500,"sdfghjk",GLUT_BITMAP_HELVETICA_18);

    }
    else if(gamestate==2)
    {
        iShowBMP(0,0,"images (3).bmp");
        iShowBMP2(5,620,"backbutton4.bmp",255);
    }
    else if (gamestate==3)
    {
        //int high_score_count=0;
        add_score_count++;
        iClear();
        iShowBMP(0,0,"snakegameover.bmp");
        iSetColor(255,255,255);
//        iText(600,360,"GAME OVER",GLUT_BITMAP_TIMES_ROMAN_24);
        iText(547,300,"YOUR SCORE is",GLUT_BITMAP_TIMES_ROMAN_24);
        iText(725,300,score_str,GLUT_BITMAP_TIMES_ROMAN_24);
        iText(550,100,"Press any key to continue",GLUT_BITMAP_TIMES_ROMAN_24);
        if(add_score_count==1)
        {
            strcpy(str2,h_name);
            FILE *fp;
            fp=fopen("highscore.txt","r");
            //int h_score=atoi(score_str);
            for(int i=0; i<3; i++)
            {
                fscanf(fp,"%s",score_var[i].name);
                fscanf(fp,"%s",score_var[i].score_value);
//                if(score_str>score_var[i].score_value)
//                {
//                    score_var[i].score_value=score_str;
//                }
            }
            qsort(score_var,3,sizeof(h_score),cmp);
            for(int i=2; i>=0; i--)
            {
                if(score_str>score_var[i].score_value)
                {
                    strcpy(score_var[i].score_value,score_str);
                    strcpy(score_var[i].name,str2);

                }
                //fprintf(fs,"%s %s\n",score_var[i].name,score_var[i].score_value);
            }

//fprintf(fp,"%s %s\n",str2,score_str);

            fclose(fp);
            fp=fopen("highscore.txt","w");
            for(int i=0 ;i<3; i++)
            {
                fprintf(fp,"%s %s\n",score_var[i].name,score_var[i].score_value);
            }
            fclose(fp);
            //fs=fopen("highscore.txt","r");
//            while(!feof(fs))
//            {
//
//            }
        }

    }
    else if(gamestate==nm)
    {
        iSetColor(25,200,125);
        iText(500,500,"Level-1",GLUT_BITMAP_TIMES_ROMAN_24);
        iText(700,500,"Level-2",GLUT_BITMAP_TIMES_ROMAN_24);
        iText(500,400,"Level-3",GLUT_BITMAP_TIMES_ROMAN_24);
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


        if(gamestate==hm && mx >=bCordinate[0].x && mx <= bCordinate[0].x+260 && my >=bCordinate[0].y &&my<=bCordinate[0].y+90)
        {

            gamestate=enter_name;
        }

        else if(gamestate==hm && mx >=bCordinate[1].x && mx <= bCordinate[1].x+260 && my >=bCordinate[1].y &&my<=bCordinate[1].y+90)
        {
            gamestate=hs;
        }
        else if(gamestate==hm && mx >=bCordinate[2].x && mx <= bCordinate[2].x+260 && my >=bCordinate[2].y &&my<=bCordinate[2].y+90)
        {
            gamestate=ins;
        }
        else if(gamestate==hm && mx >=bCordinate[3].x && mx <= bCordinate[3].x+260 && my >=bCordinate[3].y &&my<=bCordinate[3].y+90)
        {
            exit(0);
        }
        else if(gamestate==1 && mx>=30 && mx<= 215 && my >= 75 && my <= 130)
        {
            gamestate=hm;
        }
        else if(gamestate==2 && mx>=5 && mx<= 205 && my>= 620 && my<= 620+99)
        {
            gamestate=hm;
        }
        else if(gamestate==nm && mx>=500 &&mx<=540 && my>=500 && my<=530)
            gamestate=g;
        else if(gamestate==nm && mx>=700 &&mx<=740 && my>=500 && my<=530)
            gamestate=gn1;
        else if(gamestate==nm && mx>=500 &&mx<=560 && my>=400 && my<=430)
            gamestate=gn;


        printf("%d %d\n",mx,my);

    }
    if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
    {
        //place your codes here

    }
}

void iKeyboard(unsigned char key)
{
//    if(key=='d')
//        Dif++;
//    if(key=='s')
//        Dif--;
    if(key == 'p')
    {
        //do something with 'q'
        //iPauseTimer(0);
        p=1;
        //iSetColor(133,34,84);
        //iText(500,500,"Paused Press 'r' to resume",GLUT_BITMAP_TIMES_ROMAN_24);
    }
    if(key == 'r')
    {
        //iResumeTimer(0);
        p=0;
    }
//    if(gamestate=over && key=='\r')
//    {
//        gamestate=hm;
//    }
    if(gamestate==enter_name && key=='\r' )
    {
        //strcpy(h_name,str2);
        gamestate=nm;
        //strcpy(h_name,score_name.name);
    }
    else
    {
        h_name[len]=key;
        len++;
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
    int ychange=150;
    for(int i=3; i>=0; i--)
    {
        bCordinate[i].x=150;
        bCordinate[i].y=ychange;
        ychange+=150;

    }
//    FILE *fs;
//    fs=fopen("highscore.txt","a");
//    int h_score=atoi(score_str);
//    fprintf(fs,"%d",h_score);
//    fclose(fs);

    FruitSpawn();
    bonusSpawn();
    Count=3;
    iSetTimer(20,position);
    iSetTimer(20,position_update);



    iInitialize(width, height, "Ultimate Snake");

    return 0;
}

