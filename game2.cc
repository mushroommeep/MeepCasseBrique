#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <iostream>
#include <termios.h>
#include <fcntl.h>
#include <time.h>
#define H 15
#define L 30
using namespace std;
char tab[H][L];
bool flag[100];
int read_keybord();
bool a=false,end;
int count=1,vit = 20*10000,c;

// creer le cadre
 void cadre() { 
  for (int i=0; i<H;++i) {
      for (int j=0; j<L;++j)
	if (i==0||i==H-1||j==L-1||j==0)
	  tab[i][j]='*';
      cout << endl;
    }
  for (int i=0; i<H; ++i){
      for(int j=0;j<L;++j)
	cout << tab[i][j];
      cout<< endl;
    }
}

// Effacer l'ecran
void Effacer() {
  for (int i=1; i<H-1;++i)
    for (int j=1; j<L-1;++j)
      tab[i][j] = ' '; 
}

int n=10,longeur=10;
int key=read_keybord();
int x,y;
int dx=1,dy;
bool p;
   
// Creer la barre
void barre() {
  for(int i=n+1;i<n+longeur;++i)
	tab[H-2][i]='~';
}

// Creer les briques
void briqueposition(){
 for (int i= 1 ; i < 85 ; i++)
   flag[i]=true;
}
void briques() 
{
  for (int i= 1 ; i < 4 ; i++)
    for (int j = 1 ; j < L-1 ; j++)
      { 
	if(flag[(i-1)*(L-2)+j]==true)
	  tab[i][j]='=';
      }
}
void up_jeux(){
  if(tab[x][y]=='=')
    {
      if(y%2==0){
      flag[(x-1)*(L-2)+y]=false;
      flag[(x-1)*(L-2)+y-1]=false;}
      else {
	  flag[(x-1)*(L-2)+y]=false;
	  flag[(x-1)*(L-2)+y+1]=false;}
      dx=-1*dx;
      count++;
      if(count == 5){
	count=0;
	if( longeur >=5)
	  longeur--;
	vit -= 15000;
	}
    }
}
void veri_brique(){
   for (int i= 1 ; i < 85 ; i++)
     if(flag[i]==true){
       end=false;break;}
     else end=true;
}
void balle() {
  briques();
  up_jeux();
  veri_brique();
  tab[x][y]='O'; 
  if(x==H-1)  p= true;
  if((x==H-3) && (y>n) && (y<n+longeur)) dx=-1;
  if(y==L-2)  dy=-1;
  if (x==1)   dx=1;
  if (y==1)   dy=1;
  if(a) 
    {
      x+=dx;
      y+=dy;}
}
 
void jouer() {
  int key;
  time_t seconds;
  time(&seconds);
  srand((unsigned int)seconds);
  x=rand()%(H-8)+4;
  y=rand()%(L-2)+1;
  dy=rand()%2;
  if(dy==0)dy=-1;
  briqueposition();
  do
    { 
      key=read_keybord();
      Effacer();
      balle();
      barre();
      cadre();
      while (!a){
	key=read_keybord();
      	if(key=='c') a=true;
      }
      usleep(vit);
	if ((key=='a')&&(n>0))
	    n-=4;		
      	if ((key=='d') && (n+longeur<L-1))
	    n+=4; 
    }
   while((key!='q')&&( !p)&& !end);
   if(p){
     for (int i= 1 ; i < 85 ; i++)
       if(flag[i]==false)
	  c++;
     if (c >80)
       cout <<"   VOUS AVEZ PERDU MAIS AVEC UNE CLASS!! "<<endl
	    << "****************************************"<<endl
            << "*               DIAMANT                *"<<endl
            << "*                                      *"<<endl
            << "*               *******                *"<<endl
            << "*              *********               *"<<endl
            << "*                *****                 *"<<endl
	    << "*                  *                   *"<<endl
	    << "****************************************"<<endl;
 
     else if (c >70)
       cout <<"   VOUS AVEZ PERDU MAIS AVEC UNE CLASS!! "<<endl
	    << "****************************************"<<endl
            << "*                 OR                   *"<<endl
            << "*                                      *"<<endl
            << "*               *******                *"<<endl
            << "*              *  gold *               *"<<endl
            << "*               *     *                 *"<<endl
	    << "*                  *                   *"<<endl
	    << "****************************************"<<endl;
     else if (c >60)
       cout <<"   VOUS AVEZ PERDU MAIS AVEC UNE CLASS!! "<<endl
	    << "****************************************"<<endl
            << "*               ARGENT                 *"<<endl
            << "*                                      *"<<endl
            << "*               *******                *"<<endl
            << "*              * argent *              *"<<endl
            << "*               *     *                *"<<endl
	    << "*                  *                   *"<<endl
	    << "****************************************"<<endl;
     else if (c >30)
	cout <<"   VOUS AVEZ PERDU MAIS AVEC UNE CLASS!! "<<endl
	     << "****************************************"<<endl
	     << "*               CUIVRE                 *"<<endl
	     << "*                                      *"<<endl
	     << "*               *******                *"<<endl
	     << "*              * cuivre*               *"<<endl
	     << "*               *     *                *"<<endl
	     << "*                  *                   *"<<endl
	     << "****************************************"<<endl;
     else{
      cout<<" ``````````````````````````````````````````````"<<endl;
      cout<<" *************Vous avez perdu!!! :3************"<<endl;
      cout<<" .............................................."<<endl;}
   }
   if(end){
     cout<<" ``````````````````````````````````````````````"<<endl;
     cout<<" *************** VOUS GAGNEZ!!! :3*************"<<endl;
     cout<<" .............................................."<<endl;}
}
 void lire(){
   cout <<endl<<endl<<endl<<endl;
   cout << " *********************************************************"<<"\n"     
        << " *                 CASSE BRIQUE                          *"<<endl;
   cout << " *                Instructions:                          *"<<endl;
   cout << " * 1. appuyez sur 'c' pour jouer                         *"<<endl
        << " * 2. controllez la barre:                               *"<<endl
        << " *    +a gauche:appuyez sur 'a'                          *"<<endl
        << " *    +a droite:appuyez sur 'd'                          *" << endl
	<< " * 3. la balle touche une brique, la brique sera effacee.*" << endl
        << " *   Quand il n'y a plus de briques, vous gagnerez.      *" << endl;
   cout << " * Si vous ne pouvez pas saisir la balle,vous serez perdu*"<< endl;
   cout << " *                 BONNE CHANCE!!!                       *"<<endl;
   cout << " *********************************************************"<<endl;
   cout <<endl<<endl<<endl<<endl;
 }
  

 int main(){
   int choix;
 do{
	cout << "\n\t --- CASSE BRIQUE --- \n";
	cout<<" 1. lire les instructions. \n";
	cout<<" 2. jouer. \n";
	cout<<" 3. quitter.\n";
	cout<<" Votre choix <numero>: ";
	cin>>choix;
	switch(choix){
	case 1: lire(); 
			break;
	case 2: jouer();
			break;
	case 3: cout<<" A bientot!!!";
			break;
	default: cout<<"<choix invalid> un autre choix, s'il vous plait!";
	}
	
 }while((choix!=3)&&(choix!=2));
 }
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
