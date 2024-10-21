//ʹ��GBK
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <stdbool.h>
#include <windows.h>
#include <time.h>
#include "const.h"

#define RED SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_RED)
#define GREEN SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_GREEN)
#define BLUE SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_BLUE)
#define GREENPLUS SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_GREEN|FOREGROUND_INTENSITY)
#define REDPLUS SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_RED|FOREGROUND_INTENSITY)
#define BLUEPLUS SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_BLUE|FOREGROUND_INTENSITY)
#define YELLO SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_GREEN|FOREGROUND_RED|FOREGROUND_INTENSITY)
#define INDIG SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_GREEN|FOREGROUND_BLUE|FOREGROUND_INTENSITY)
#define MagentaPlus SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_RED|FOREGROUND_BLUE|FOREGROUND_INTENSITY)
#define White SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE|FOREGROUND_INTENSITY)
#define Other SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_RED&FOREGROUND_GREEN|FOREGROUND_BLUE|FOREGROUND_INTENSITY)

struct mine Mine[X][Y];

void Reset(void);
void Init(int,int);
void Play(void);
bool Not_stepping_on_the_mine(void);
int FindMineNum(int,int);
int CountFlagsNum(void); 
void Display(int,int);
void EndDisplay(void);
void Open_large_area(int,int);
void Open_side_of_blank(void);
bool IfWin(void);
void End(bool);

int main(void)
{
	char Chioce;
	srand((unsigned)(time(NULL)));
	A:
	Play();
	Sleep(2500);
	system("cls");
	EndDisplay();
	getchar();
	printf("����һ��?(Yes[Y]/No[N]\n");
	Ch:
	Chioce = getch();
	switch(Chioce)
	{
		case 'Y':
		case 'y':
		{
			Reset();
			system("cls"); 
			goto A;
		}
		case 'N':
		case 'n':
		{
			return;
		}
		default:
		{
			goto Ch;
		}
	}
	return 0;
}

/**
*����Mine�ṹ. 
*/
void Reset(void)
{
	int x,y;
	for(x = 0;x < X;x++)
	{
		for(y = 0;y < Y;y++)
		{
			Mine[x][y].Num = 0;
			Mine[x][y].Mark = Close;
		}
	}
}

/**
*����Ҵ�һ������ʱ����ʼ��Mine�ṹ.
*@param Posx: ��ҵ������ĺ�������ֵ.
*@param Posy: ��ҵ���������������ֵ.
*/
void Init(int Posx,int Posy)
{
	int x,y,tmp;
	for(x = 0;x < X;x++)
	{
		for(y = 0;y < Y;y++)
		{
			Mine[x][y].Mark = Close;
			Mine[x][y].Num = 0;
		} 
	} 
	tmp = 0;
	while(tmp < 10)
	{
		Again:
		x = rand()%X;
		y = rand()%Y;
		if(x == Posx && y == Posy)
		{
			goto Again;
		} 
		if(Mine[x][y].Num != MINE)
		{
			Mine[x][y].Num = MINE;
		}
		else
		{
			goto Again; 
		} 
		tmp++;
	}
	for(x = 0;x < X;x++)
	{
		for(y = 0;y < Y;y++)
		{
			if(Mine[x][y].Num != MINE)
			{
				Mine[x][y].Num = FindMineNum(x,y);							//��Ԫ����Χ���ڶ��ٸ�����. 
			}
		}
	}
}

/**
*Ѱ��Ŀ�귽��ľŹ��������ڴ��ڵ��׵���Ŀ.
*@param x:Ŀ�귽��ĺ�����.
*@param y:Ŀ�귽���������. 
*/
int FindMineNum(int x,int y)
{
	int Count = 0;
	if(x-1 >= 0 && y-1 >= 0)
	{
		if(Mine[x-1][y-1].Num == MINE)
		{
			Count++;
		}
	}
	if(x-1 >= 0)
	{
		if(Mine[x-1][y].Num == MINE)
		{
			Count++; 
		}
	}
	if(y-1 >= 0)
	{
		if(Mine[x][y-1].Num == MINE)
		{
			Count++; 
		}
	}
	if(x+1 < X && y-1 >= 0)
	{
		if(Mine[x+1][y-1].Num == MINE)
		{
			Count++; 
		}
	}
	if(x+1 < X)
	{
		if(Mine[x+1][y].Num == MINE)
		{
			Count++; 
		}
	}
	if(x-1 >= 0 && y+1 < Y)
	{
		if(Mine[x-1][y+1].Num == MINE)
		{
			Count++; 
		}
	}
	if(y+1 < Y)
	{
		if(Mine[x][y+1].Num == MINE)
		{
			Count++; 
		}
	}
	if(x+1 < X && y+1 < Y)
	{
		if(Mine[x+1][y+1].Num == MINE)
		{
			Count++; 
		}
	}
	return Count;
}

/**
*��Ҳ�����������.
*/
void Play(void)
{
	int Posx,Posy;
	char ch;
	bool bFirst = false;
	Posx = Posy = 0;
	bool bWin = false;
	
	//�Ƿ���. 
	while(Not_stepping_on_the_mine())
	{
		system("cls");
		Display(Posx,Posy);
		ch = getch();
		switch(ch)
		{
			case 'w':
			case 'W':
			{
				Posy--;
				Posy %= Y;
				break;
			}
			case 's':
			case 'S':
			{
				Posy++;
				Posy %= Y;
				break;
			}
			case 'a':
			case 'A':
			{
				Posx--;
				Posx %= X;
				break;
			}
			case 'd':
			case 'D':
			{
				Posx++;
				Posx %= X;
				break;
			}
			/*Open����*/
			case 'o':
			case 'O':
			{
				/*���������ڷ��״̬���ſ��Դ�*/
				if(Mine[Posx][Posy].Mark == Close)
				{
					if(!bFirst)
					{
						Init(Posx,Posy);
						bFirst = true;
						Mine[Posx][Posy].Mark = Open;
						if(Mine[Posx][Posy].Num == 0)
						{
							Open_large_area(Posx,Posy);
							Open_side_of_blank();
						}
					}
					else
					{
						Mine[Posx][Posy].Mark = Open;
						if(Mine[Posx][Posy].Num == 0)
						{
							//�ݹ�򿪿����� 
							Open_large_area(Posx,Posy);
							Open_side_of_blank();
						}
					}
				}
				break;
			}
			/*Flags����*/
			case 'f':
			case 'F':
			{
				//Flagsû�б�����. 
				if(CountFlagsNum() < 10 || Mine[Posx][Posy].Mark == Flags)
				{
					if(Mine[Posx][Posy].Mark == Flags)
					{
						Mine[Posx][Posy].Mark = Close;
					}
					else if(Mine[Posx][Posy].Mark == Close)
					{
						Mine[Posx][Posy].Mark = Flags;
					}
				}
				break;
			}
			default:
			{
				break;
			}
		}
		//�����Ƿ�ȫ�����. 
		if(IfWin())
		{
			bWin = true;
			break;
		}
	}
	
	//������ʾս��. 
	system("cls");
	Display(Posx,Posy);
	
	//����. 
	End(bWin);
	return;
}

/**
*ͳ��Mine�ṹ�е�Flags��Ŀ. 
*/
int CountFlagsNum(void)
{
	int Count = 0;
	int x,y;
	for(x = 0;x < X;x++)
	{
		for(y = 0;y < Y;y++)
		{
			if(Mine[x][y].Mark == Flags)
			{
				Count++;
			}
		}
	}
	return Count;
}

/**
*�ݹ��Ŀ��������Χ�հ�����.
*@param x:Ŀ�����������.
*@param y:Ŀ������������.
*/
void Open_large_area(int x,int y)
{
	Mine[x][y].Mark = Open;
	if(Mine[x+1][y].Num == 0 && x+1 < X && Mine[x+1][y].Mark != Open)	/*���������򲻳���Mine���ֵ*/
	{
		Mine[x+1][y].Mark = Open;
		Open_large_area(x+1,y);
	}
	if(Mine[x-1][y].Num == 0 && x-1 >= 0 && Mine[x-1][y].Mark != Open)	/*����������С��Mine��Сֵ*/ 
	{
		Mine[x-1][y].Mark = Open;
		Open_large_area(x-1,y);
	}
	if(Mine[x][y+1].Num == 0 && y+1 < Y && Mine[x][y+1].Mark != Open)
	{
		Mine[x][y+1].Mark = Open;
		Open_large_area(x,y+1);
	}
	if(Mine[x][y-1].Num == 0 && y-1 >= 0 && Mine[x][y-1].Mark != Open)
	{
		Mine[x][y-1].Mark = Open;
		Open_large_area(x,y+1);
	}
}

void Open_side_of_blank(void)
{
	for(int x = 0;x < X;x++)
	{
		for(int y = 0;y < Y;y++)
		{
			if(Mine[x][y].Num == 0 && Mine[x][y].Mark == Open)
			{
				if(Mine[x+1][y].Num && x+1 < X && Mine[x+1][y].Mark == Close)
				{
					Mine[x+1][y].Mark = Open;
				}
				if(Mine[x][y+1].Num && y+1 < Y && Mine[x][y+1].Mark == Close)
				{
					Mine[x][y+1].Mark = Open;
				}
				if(Mine[x-1][y].Num && x-1 >= 0 && Mine[x-1][y].Mark == Close)
				{
					Mine[x-1][y].Mark = Open;
				}
				if(Mine[x][y-1].Num && y-1 >= 0 && Mine[x][y-1].Mark == Close)
				{
					Mine[x][y-1].Mark = Open;
				}
				if(Mine[x-1][y-1].Num && y-1 >= 0 && x-1 >= 0 && Mine[x-1][y-1].Mark == Close)
				{
					Mine[x-1][y-1].Mark = Open;
				}
				if(Mine[x+1][y+1].Num && y+1 < Y && x+1 < X && Mine[x+1][y+1].Mark == Close)
				{
					Mine[x+1][y+1].Mark = Open;
				}
				if(Mine[x-1][y+1].Num && y+1 < Y && x-1 >= 0 && Mine[x-1][y+1].Mark == Close)
				{
					Mine[x-1][y+1].Mark = Open;
				}
				if(Mine[x+1][y-1].Num && y-1 >= 0 && x+1 < X && Mine[x+1][y-1].Mark == Close)
				{
					Mine[x+1][y-1].Mark = Open;
				}
			}
		}
	}
}

/**
*��ʾMine�ṹ�ĺ���. 
*/

void Display(int Posx,int Posy)
{
	printf("***********ɨ��***********\n");
	for(int y = 0;y < Y;y++)
	{
		for(int x = 0;x < X;x++)
		{
			printf(" ");
			if(x == Posx && y == Posy)
			{
				YELLO;
			}
			switch(Mine[x][y].Mark)
			{
				case Open:
				{
					if(Mine[x][y].Num == MINE)
					{
						printf("%c",MineIcon);
					}
					else
					{ 
						printf("%d",Mine[x][y].Num);
					}
					break;
				}
				case Close:
				{
					printf("%c",Block);
					break;
				}
				case Flags:
				{
					printf("%c",FlagsIcon);
					break;
				}
			}
			White;
			printf(" ");
		}
		printf("\n");
	}
	printf("\n");
	printf("ɨ��ʣ��:%d",(10 - CountFlagsNum()));
}

/**
*��Ϸ�������Mine�ṹ��ʾ.
*/
void EndDisplay(void)
{
	int x,y;
	
	printf("***********ɨ��***********\n");
	
	for(y = 0;y < Y;y++)
	{
		for(x = 0;x < X;x++)
		{
			White;
			if(Mine[x][y].Mark == Flags && Mine[x][y].Num == MINE)
			{
				REDPLUS;
				printf(" R ");
			}
			else if(Mine[x][y].Num == MINE)
			{
				GREENPLUS;
				printf(" %c ",MineIcon);
			}
			else
			{
				printf(" %d ",Mine[x][y].Num);
			}
		}
		printf("\n");
	}
	
	printf("\n");
}

/**
*�Ƿ���. 
*/
bool Not_stepping_on_the_mine(void)
{
	int x,y;
	for(x = 0;x < X;x++)
	{
		for(y = 0;y < Y;y++)
		{
			if(Mine[x][y].Mark == Open && Mine[x][y].Num == MINE)
			{
				return 0;
			}
		}
	}
	return 1;
}

/**
*�����Ƿ�������. 
*/
bool IfWin(void)
{
	int x,y;
	if(CountFlagsNum() == 10)
	{
		for(x = 0;x < X;x++)
		{
			for(y = 0;y < Y;y++)
			{
				if(Mine[x][y].Mark == Flags && Mine[x][y].Num != MINE)
				{
					return false; 
				}
			}
		}
	}
	else
	{
		return false;
	}
	return true;
} 

/**
*��Ϸ����.
*@param Rel:�Ƿ�ʤ��������.ʤ��(true)/ʧ��(false). 
*/
void End(bool Rel)
{
	if(Rel)
	{
		printf("\n\n��ϲ��Ӯ��!��ʱ:%.2lf(s)\n\n",(double)(clock()/1000.0));
	}
	else
	{
		printf("\n\n��Ǹ��������!��ʱ:%.2lf(s)\n\n",(double)(clock()/1000.0));
	}
	return;
}
