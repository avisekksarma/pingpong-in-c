//backup--1vs1
//player1 = bottom player
//player2 = top player
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <stdbool.h>
#define width 60
#define height 40
void checkkeys();
void draw();
void changevalues();
void setvalues();     //gives initial position of ball,bat and many others.
void ResetScreenPosition();
void hidecursor();
void drawFirstScreen();
void clear_screen();
void newgame_function();     //complete this for new game login system.
void continuegame_function();
void gotoxy(int x, int y);
void bullet1_manager();
void bullet2_manager();
int highscore1,highscore2;
int curr_hashes1 = 15;
int curr_hashes2 = 15;
int side1;
int side2;
int ballx,bally;   // determines position of ball
int x1,y1;
int x2,y2;
int score1=0,score2=0;
int lives1=3,lives2=3;
int value_of_vel[3] ={1,-1,0};
int vel_x;  //vel_x and vel_y could be 1 ,-1 or 0.This is velocity of ball.
int vel_y;
int running = 1;
int increment_in_ballx,increment_in_bally;
FILE* fp1;
FILE* fp2;
FILE* fp3;
FILE* fp4;
typedef struct
{
    int x[10];
    int y[10];
    int counter;
    bool isbulletON;
}bullet;

bullet bullet1,bullet2;
void main()
{

    srand(time(NULL));
    setvalues();   //sets the initial position of bat and ball to be displayed in console.

    char ch;
    int choose;
    initial_screen_label:
    system("cls");
    drawFirstScreen();
    gotoxy(0,28);
    printf(" Welcome to PING-PONG game.\n");
    printf(" -> 1.NEWGAME \n");
    printf(" -> 2.CONTINUE \n");
    printf(" -> 3.HIGHSCORES \n");
    printf(" -> 4.INSTRUCTIONS \n");
    printf(" -> 5.QUIT\n");
    scanf("%d",&choose);
    switch(choose)
    {
        case 1:
          break;
        case 2:
          fp1 = fopen("score1.txt","r");
          fscanf(fp1,"%d",&score1);
          fclose(fp1);
          fp2 = fopen("score2.txt","r");
          fscanf(fp2,"%d",&score2);
          fclose(fp2);

          if (score1 == 0 && score2 == 0)   //score1 = 0 and score 2 =0  means last game had ended not exited.
          {
            system("cls");                 //this block is for not continuing previous game.
            drawFirstScreen();

            gotoxy(0,28);
            printf("No game to continue.Previous game had ended.\n");
                  if (getch())
                      {
                          goto initial_screen_label;
                      }
          }
          else      // continuing previous game.
          {
            fp3 = fopen("lives1.txt","r");
            fscanf(fp3,"%d",&lives1);
            fclose(fp3);
            fp4 = fopen("lives2.txt","r");
            fscanf(fp4,"%d",&lives2);
            fclose(fp4);
             goto label;
          }

          break;
        case 3:
          system("cls");
          drawFirstScreen();
          gotoxy(0,28);
          printf("HIGHSCORES:");
          gotoxy(0,30);
          printf("HIGHSCORE1 = %d ",highscore1);
          gotoxy(0,32);
          printf("HIGHSCORE2 = %d ",highscore2);
          if (getch())
          {
              goto initial_screen_label;
          }
          break;
        case 4:
          system("cls");
          drawFirstScreen();
          gotoxy(0,28);
          printf("1.Player1 is bottom player and Player2 is top player.\n");
          printf("2.Each player has 3 lives and whoever loses lives first loses and another player wins.\n");
          printf("3.Press \'a\' and \'d\' to move bottom player and press \'j\' and \'l\' to move top player.");
          if (getch())
          {
              goto initial_screen_label;
          }
          break;
        case 5:
            running = 0;
            break;
        default:
            goto initial_screen_label;
            break;

    }


    lives1_continuegame_func();   // done in order to put 3,3 values to files else 0,0 would be stored there unlike in score.
    lives2_continuegame_func();
    label:
    hidecursor();
    clear_screen();

    while(running)
    {
        ResetScreenPosition();
        draw();
        checkkeys();
        changevalues();
        gotoxy(80,20);
        printf("SCORES: \t\t\t LIVES:");
        gotoxy(80,22);
        printf("Player 1 = %d\t\t\t Player 1 = %d",score1,lives1);
        gotoxy(80,24);
        printf("Player 2 = %d\t\t\t Player2 = %d",score2,lives2);
        gotoxy(80,10);
        printf("HIGHSCORE1 = %d",highscore1);
        gotoxy(80,11);
        printf("HIGHSCORE2 = %d",highscore2);


        if (lives1==0)
        {
            clear_screen();
            gotoxy(80,15);
            printf("Player2(X) won the Ping-Pong game.");

        }
        else if (lives2 == 0)
        {
            clear_screen();
            gotoxy(80,15);
            printf("Player1(#) won the Ping-Pong game.");
        }
        gotoxy(80,20);
        if ((lives1== 0 || lives2 == 0) && (score1>highscore1))
            {

                fp1 = fopen("highscore1.txt","w");
                fprintf(fp1,"%d",score1);
                printf("New HIGHSCORE of player1(#) = %d !!!",score1);
                fclose(fp1);
            }
        gotoxy(80,22);
        if ((lives1== 0 || lives2 == 0) && (score2>highscore2))
            {

                fp2 = fopen("highscore2.txt","w");
                fprintf(fp2,"%d",score2);
                printf("New HIGHSCORE of player2(X) = %d !!!\n\n",score2);
                fclose(fp2);
            }

    }
gotoxy(80,28);
printf("SCORES:\n");
gotoxy(80,30);
printf("Player1(#) = %d  and  Player2(X) = %d.\n",score1,score2);
gotoxy(80,32);
printf("Game ended.Do you want to play the game again? ");

ch = getch();
if (ch == 'y' || ch == 'Y')
{

    lives1 = 3,lives2 = 3;
    score1 =0,score2 = 0;
    running =1;
    goto label;
}
score1 = 0;  // done in order  to decide whether to continue game or not based on previous game ended or not.
score2 = 0;
score1_continuegame_func();   //to put scores in the file so that we can store that value during "continue checking".
score2_continuegame_func();
clear_screen();
main();
}
void draw()
{

   int i,j,m;
   for (j = 0;j <3 ;j++)
   {
           for (i =0;i < 20;i++)
        {
               printf("   ");
        }
           printf("\n");
   }
   for (i = 0; i < height;i++)
   {
       for (j = 0; j < width; j++)
       {
           if (i == 0 || i == height-1|| j == 0|| j == width-1)
           {
                printf("%c",178);   //prints border.
           }
           else
           {
               if (i == y1 && j == x1)
                {

                   for (m = 0; m < curr_hashes1; m++)
                    {
                            printf("%c",220); // prints bat1(bottom).
                            if (m!=(0))   //curr_hashes-anynumber(0 to (curr_hashes-1)) is valid because we want to avoid j++ one time.
                                j++;
                    }
                }
               else if  (i == y2 && j == x2)
                {

                   for (m = 0; m < curr_hashes2; m++)
                    {
                            printf("%c",220);   //prints bat2(top).
                            if (m!=(0))   //curr_hashes-anynumber(0 to (curr_hashes-1)) is valid because we want to avoid j++ one time.
                                j++;
                    }
                }

                else if (j == ballx && i == bally)
                    printf("%c",223);    //prints ball
                else if (bullet1.isbulletON && (i == bullet1.y[0] && j == bullet1.x[0]))
                    printf("%c",156);           //draws bullet1.
                else if (bullet2.isbulletON && (i == bullet2.y[0] && j == bullet2.x[0]))
                    printf("%c",190);           //draws bullet2.
               else

                    printf(" ");
            }
        }
        printf("\n");
    }
}
void checkkeys()
{

    char c;

    if (kbhit())   // for first bat that is lower bat.
    {
        c = getch();
    }
    switch(c)
    {
    case 'a':
        side1 = -1;
        break;
    case 'd':
        side1 = 1;
        break;
    case 's':
        bullet1_manager();
        break;
    default:
        break;
    }

    //for second bat that is upper bat.
    if (kbhit())
    {
        c = getch();
    }
    switch(c)
    {
    case 'j':
        side2 = -1;
        break;
    case 'l':
        side2 = 1;
        break;
    case 'k':
        bullet2_manager();
        break;
    default:
        break;
    }
}

                                                         //CHANGEVALUE FUNCTION.
void changevalues()
{
    int count11 =0,count22 = 0;
    int m1,m2,count1_forballtapping = 0,count2_forballtapping = 0,count1_forbullethitting = 0,count2_forbullethitting = 0;
    if(side1 == 1 && x1<(60-1*curr_hashes1-1))
    {
       x1+=3;

    }
    if (side1 == -1  && x1 > 3)
    {
        x1-=3;
    }
      //for bat2
      if(side2 == 1 && x2<(60-1*curr_hashes2-1))
    {
       x2+=3;
    }
    if (side2 == -1  && x2 > 3) //this '3' must equal to x2-= or x2+=3.
    {
        x2-=3;
    }
    if (bullet1.isbulletON)
    {
        bullet1.y[0]-=2;
    }
    if (bullet2.isbulletON)
    {
        bullet2.y[0]+=2;
    }

  // checking for game running or not  and bouncing ball in the bat.
    for (m1=0;m1<curr_hashes1;m1++)      //ball tapping checker , bullet hitting checker for bat1(bottom player.)
    {
        if (ballx == (x1+m1))
            count1_forballtapping++;
        if (bullet2.x[0] == (x1+m1) )
            count1_forbullethitting++;
    }
    for (m2=0;m2<curr_hashes2;m2++)     //ball tapping checker , bullet hitting checker for bat2(top player.)
    {
        if (ballx == (x2+m2))
            count2_forballtapping++;
        if (bullet1.x[0] == (x2+m2) )
            count2_forbullethitting++;
    }

    if(count1_forballtapping == 0 && bally >= y1+1)
    {    lives1= lives1-1;
         lives1_continuegame_func();
         if (lives1 != 0)
         {
            srand(time(NULL));         //replacement of "goto label;"
            setvalues();
         }
         else
            {
               running = 0;
            }

    }else if (count2_forballtapping == 0 && bally <= 0)
    {
         lives2=lives2-1;
         lives2_continuegame_func();
         if (lives2 != 0)
         {
             srand(time(NULL));
             setvalues();         //replacement of "goto label;"
         }
         else
          {
            running = 0;
          }
    }
    else if ( count2_forballtapping == 1 && bally <= 2)    //for player2 tapping on bat
    {
        score2++;
        score2_continuegame_func();
        vel_y = -1;
    }
    else if (count1_forballtapping == 1 && bally >= y1 )   //for player1  tapping on bat
    {
       score1++;
       score1_continuegame_func();
       vel_y = 1;
    }
    else if (count1_forbullethitting == 1 && bullet2.y[0] >= y1 && bullet2.isbulletON)   //if bullet2 hits bat1.
    {
        curr_hashes1--;
        bullet2.isbulletON = false;
    }
    else if (count2_forbullethitting == 1 && bullet1.y[0] <=2 && bullet1.isbulletON)     //if bullet1 hits bat2.
    {
        curr_hashes2--;
        bullet1.isbulletON = false;
    }
    else if(ballx >= 58)
    {
          vel_x =-1;
    }
    else if (ballx <=0 )
    {
          vel_x =1;
    }

    //movement of ball in x direction according to vel_x.
    switch(vel_x)
    {
    case 1:
        ballx+=1;
        break;
    case -1:
        ballx-=1;
        break;
    case 0:
        ballx =ballx;
        break;
    default:
        break;
    }

    //movement of ball in y direction according to vel_y.
    switch(vel_y)
    {
    case 1:
        bally-=1;
        break;
    case -1:
        bally+=1;
        break;
    case 0:
        bally =bally;
        break;
    default:
        break;
    }
}

void setvalues()
{

    int temp1 = rand()%2;
    vel_x = value_of_vel[temp1];
    temp1 = rand()%2;
    vel_y = value_of_vel[temp1];
    ballx=10;
    bally =20;
    x1=15;
    y1=37;
    x2 = 15;
    y2 = 1;
    fp1 = fopen("highscore1.txt","r");
    fp2 = fopen("highscore2.txt","r");
    fscanf(fp1,"%d",&highscore1);
    fscanf(fp2,"%d",&highscore2);
    fclose(fp1);
    fclose(fp2);

}
void ResetScreenPosition()
{
    HANDLE hOut;
    COORD Position;
    hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    Position.X = 0;
    Position.Y = 0;
    SetConsoleCursorPosition(hOut,Position);
}

void gotoxy(int x, int y)
{
  COORD coord;
  coord.X = x;
  coord.Y = y;
  SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
void hidecursor()
{
   HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
   CONSOLE_CURSOR_INFO info;
   info.dwSize = 100;
   info.bVisible = FALSE;
   SetConsoleCursorInfo(consoleHandle, &info);
}
void drawFirstScreen()
{


    gotoxy(17,5);
    printf("PPPPPPPPP  IIIIIIIII  N       N  GGGGGGGGG");
    gotoxy(17,6);
    printf("P       P      I      NN      N  G");
    gotoxy(17,7);
    printf("P       P      I      N N     N  G");
    gotoxy(17,8);
    printf("P       P      I      N  N    N  G");
    gotoxy(17,9);
    printf("P       P      I      N   N   N  G");
    gotoxy(17,10);
    printf("PPPPPPPPP      I      N    N  N  G   GGGGG");
    gotoxy(17,11);
    printf("P              I      N     N N  G   G   G");
    gotoxy(17,12);
    printf("P              I      N      NN  G   G   G");
    gotoxy(17,13);
    printf("P          IIIIIIIII  N       N  GGGGG   G");
    gotoxy(17,14);
    printf("                   |||");
    gotoxy(17,15);
    printf("                   |||");
    gotoxy(17,16);
    printf("PPPPPPPPP      O      N       N  GGGGGGGGG");
    gotoxy(17,17);
    printf("P       P     O O     NN      N  G");
    gotoxy(17,18);
    printf("P       P    O   O    N N     N  G");
    gotoxy(17,19);
    printf("P       P   O     O   N  N    N  G");
    gotoxy(17,20);
    printf("P       P  O       O  N   N   N  G");
    gotoxy(17,21);
    printf("PPPPPPPPP   O     O   N    N  N  G   GGGGG");
    gotoxy(17,22);
    printf("P            O   O    N     N N  G   G   G");
    gotoxy(17,23);
    printf("P             O O     N      NN  G   G   G");
    gotoxy(17,24);
    printf("P              O      N       N  GGGGG   G");

}

void clear_screen( void )
{
  DWORD n;
  DWORD size;
  COORD coord = {0};
  CONSOLE_SCREEN_BUFFER_INFO csbi;
  HANDLE h = GetStdHandle ( STD_OUTPUT_HANDLE );
  GetConsoleScreenBufferInfo ( h, &csbi );
  size = csbi.dwSize.X * csbi.dwSize.Y;
  FillConsoleOutputCharacter ( h, TEXT ( ' ' ), size, coord, &n );
  GetConsoleScreenBufferInfo ( h, &csbi );
  FillConsoleOutputAttribute ( h, csbi.wAttributes, size, coord, &n );
  SetConsoleCursorPosition ( h, coord );
}

void score2_continuegame_func()
{
    fp2 = fopen("score2.txt","w");
    fprintf(fp2,"%d",score2);
    fclose(fp2);

}

void score1_continuegame_func()
{
    fp1 = fopen("score1.txt","w");
    fprintf(fp1,"%d",score1);
    fclose(fp1);
}

void lives1_continuegame_func()
{
    fp3 = fopen("lives1.txt","w");
    fprintf(fp3,"%d",lives1);
    fclose(fp3);
}

void lives2_continuegame_func()
{
    fp4 = fopen("lives2.txt","w");
    fprintf(fp3,"%d",lives2);
    fclose(fp3);
}

void bullet1_manager()     //managing bullet1 function.
{
    //bullet1.counter = 0;
    bullet1.x[0] = (x1) + (curr_hashes1)/2;
    bullet1.y[0] =  37;
    bullet1.isbulletON = true;
}

void bullet2_manager()     //managing bullet2 function.
{
    //bullet2.counter = 0;
    bullet2.x[0] = (x2) + (curr_hashes2)/2;
    bullet2.y[0] =  2;
    bullet2.isbulletON = true;
}
