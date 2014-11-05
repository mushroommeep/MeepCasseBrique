/******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <iostream>
#include <termios.h>
#include <fcntl.h>
using namespace std;

/* retourne 0 si aucune touche n'est appuyée, 
 * sinon retourne le code ASCII de la touche */
int read_keybord();
/******************************************************************************/
#define H 20
#define L 40

char screen[H][L];
void clear_screen (){
  system ("clear");
  for(int i=0;i<H;i++){
    for (int j=0;j<L;j++)
      cout << screen [i][j];
    cout << endl;
    }
}
void screen_display() {
  for (int i=0; i<H; i++) {
    for (int j=0; j<L; j++) 
      if (i==0||j==0 || j==L-1 || i==H-1)
	screen [i][j]='*';
      else
	screen[i][j]= ' ';
    cout << endl;
  }
}

void barre(int key){
  int bA= L/2-4, bD=L/2+4;
  for (int i=0;i<H;i++){
    for (int j =0; j<L;j++)
      if( i== H-3 && j>bA && j < bD)
	screen [i][j]='_';
  }
  if (key == 'a')
    { 
      if ( bA >=1)
	{
	  bA-=3;
	  bD-=3;
	}
    }
  if (key=='d')
    {
      if( bD <= L-1)
	{
	  bA +=3;
	  bD+=3;
	}
    }
}

/******************************************************************************/
int x=1,y=1,a=1,b=1;
void update_game(int key){
  screen[x][y]='o';
  if(x==H-2)   a=-1;
  if(x==1)     a=1;
  if(y==L-2)   b=-1;
  if(y==1)     b=1;
  x+=a; y+=b;
}

/******************************************************************************/

int main() {
  int key;
  do {
    key = read_keybord();
    clear_screen();
    screen_display(); 
    update_game(key);
    barre(key);
    usleep(20*10000);
  } while (key != 'q');
}
/* Mettre votre code source ici */


/******************************************************************************/

int kbhit(void)
{
  struct termios oldt, newt;
  int ch;
  int oldf;

  tcgetattr(STDIN_FILENO, &oldt);
  newt = oldt;
  newt.c_lflag &= ~(ICANON | ECHO);
  tcsetattr(STDIN_FILENO, TCSANOW, &newt);
  oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
  fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);

  ch = getchar();

  tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
  fcntl(STDIN_FILENO, F_SETFL, oldf);

  if(ch != EOF)
  {
    ungetc(ch, stdin);
    return 1;
  }

  return 0;
}

int read_keybord() {
  int key;
  if (kbhit())
    key = getc(stdin);
  else
    key = 0;
  return key;
}

/******************************************************************************/
/******************************************************************************/
