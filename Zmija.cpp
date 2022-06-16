#include<stdio.h>
#include<windows.h>
#include<stdlib.h>
#include<conio.h>
#include<ctime>
#define N 20
#define M 40

int i,j,Polje[N][M],x,y,Gy,Glava,Rep,Igra,Voce,a,b,var,dir,score,Highscore,Brzina;

FILE * f;
void ZmijaInicijalizacija()
{
	f=fopen("highscore.txt","r");
	fscanf(f,"%d",&Highscore);
	fclose(f);
	
	for(i=0;i<N;i++)
	{
		for(j=0;j<M;j++)
		{
			Polje[i][j]=0;
		}
	}
	
	x=N/2;y=M/2; Gy = y; Glava = 5; Rep = 1; Igra = 0; Voce = 0, dir='d',score = 0,Brzina = 50;
	
	for(i=0;i<Glava;i++)
	{
		Gy++;
		Polje[x][Gy-Glava] = i+1;
	}
	
}


void print()
{
	for(i=0;i<=M+1;i++)
	{
		if(i==0)
		{
			printf("%c",201);
		}
		else if(i==M+1)
		{
			printf("%c",187);
		}
		else
		{
			printf("%c",205);
		}
	}
	printf("   Current score: %d    Highscore: %d",score,Highscore);
	printf("\n");
	
	for (i=0;i<N;i++)
	{
		printf("%c",186);
		for(j=0;j<M;j++)
		{
			if(Polje[i][j]==0) printf(" ");
			if(Polje[i][j]>0 && Polje [i][j]!=Glava) printf("%c",176);
			if(Polje[i][j]==Glava) printf ("%c",178);
			if(Polje[i][j]==-1) printf("%c",15);
			if(j==M-1) printf("%c\n",186);
			
		}
	}
	
	for(i=0;i<=M+1;i++)
	{
		if(i==0)
		{
			printf("%c",200);
		}
		else if(i==M+1)
		{
			printf("%c",188);
		}
		else
		{
			printf("%c",205);
		}
	}
}
void ResetPozicijeEkrana()
{
	HANDLE hOut;
	COORD Position;
	hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	Position.X = 0;
	Position.Y = 0;
	SetConsoleCursorPosition(hOut, Position);
}

void NasumicnoVoce()
{
	srand(time(0));
	a = 1 + rand() % 18;
	b = 1 + rand() % 38;
	
	if(Voce == 0 && Polje [a][b]==0)
	{
		Polje[a][b] = -1;
		Voce= 1;
		if(Brzina>10 && score !=0) Brzina = Brzina -5;
	}
}

int getch_noblock()
{
	if(_kbhit())
		return _getch();
	else
		return -1;
}

void KrajIgre()
{
	printf("\a");
	Sleep(1500);
	system("Cls");
	if(score>Highscore)
	{
		printf("New Highscore %d !!!!!!!!\n\n",score);
		system("pause");
		f=fopen("highscore.txt","w");
		fprintf(f,"d",score);
		fclose(f);
	}
	
	system("Cls");
	printf("\n\n          GAME OVER!!!!!");
	printf("              Score:  %d \n\n",score);
	printf("              Pritisni Enter da igras opet ili ESC da izadjes\n");
	while(1)
	{
		var = getch_noblock();
		if (var == 13)
		{
			Igra = 0;
			ZmijaInicijalizacija();
			break;
		}
		else if (var == 27)
		{
			Igra = 1;
			break;
		}
	}
	system("Cls");
}

void Pomeranje()
{
	var = getch_noblock();
	var = tolower(var);
	
	if(((var=='d'||var=='a')||(var=='s'||var=='w'))
	&&(abs(dir-var)>5)) dir = var;
	if(dir == 'd')
	{
		y++;
		if(Polje[x][y]!=0 && Polje[x][y]!=-1) KrajIgre();
		if(y==M-1) y = 0;
		if(Polje[x][y]==-1)
		{
			Voce = 0;
			score +=5;
			Rep -= 2;
		}
		Glava++;
		Polje[x][y] = Glava;
	}
	if(dir == 'a')
	{
		y--;
		if(Polje[x][y]!=0 && Polje[x][y]!=-1) KrajIgre();
		if(y==0) y = M-1;
		if(Polje[x][y]==-1)
		{
			Voce = 0;
			score +=5;
			Rep -= 2;
		}
		Glava++;
		Polje[x][y] = Glava;
	}
	if(dir == 'w')
	{
		x--;
		if(Polje[x][y]!=0 && Polje[x][y]!=-1) KrajIgre();
		if (x==-1) x = N-1;
		if(Polje[x][y]==-1)
		{
			Voce = 0;
			score +=5;
			Rep -= 2;
		}
		Glava++;
		Polje[x][y] = Glava;
	}
	if(dir == 's')
	{
		x++;
		if(Polje[x][y]!=0 && Polje[x][y]!=-1) KrajIgre();
		if (x==N-1) x = 0;
		if(Polje[x][y]==-1)
		{
			Voce = 0;
			score +=5;
			Rep -= 2;
		}
		Glava++;
		Polje[x][y] = Glava;
	}
	
}

void PomeranjeRepa()
{
	for(i=0;i<N;i++)
	{
		for(j=0;j<M;j++)
		{
			if(Polje[i][j]==Rep)
			{
				Polje[i][j] = 0;
			}
		}
	}
	Rep++;
}

int main()
{
	ZmijaInicijalizacija();
	
	while(Igra == 0)
	{
		print();
		ResetPozicijeEkrana();
		NasumicnoVoce();
		Pomeranje();
		PomeranjeRepa();
		Sleep(Brzina);
	}
	
}
