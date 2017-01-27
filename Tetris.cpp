/*
This is my personal project Tetris,simple but interesting.
My name is Elliott Zheng,from Software School.Xiamen University
The way to get in touch with me:
	E-mail:elliott.zheng@foxmail.com
The start time:2017/1/27 
*/
#include<iostream>
#include<cstring>
#include<cstdlib>
#include<time.h>
#include<windows.h>
#define SIZE 4

const int ROWS=20;//使用const 类型常量比用define好
const int COLS=10;


using namespace std;
/*想法，一个用来储存坐标的数组。*/
struct Coordinate
{
    int x;
    int y;
};

Coordinate coordinate[7][4]=
{
    {{4,0},{4,1},{4,2},{4,3}},
    {{1,1},{1,2},{2,1},{2,2}},
    {{4,1},{4,2},{4,3},{3,3}},
    {{4,1},{4,2},{4,3},{3,2}},
    {{4,0},{4,1},{4,2},{3,0}},
    {{3,1},{3,2},{4,2},{4,3}},
    {{4,0},{4,1},{3,1},{3,2}}
};


struct Part
{
    Coordinate con[4];
    int line;
};

void Refresh(int matrix[ROWS][COLS],Part * part);
void DownStair(int matrix[ROWS][COLS],int i);
void Clean(int matrix[ROWS][COLS]);
Part * GetPart(Part * part);
void rotate(Part * part);
bool Falling(Part * part,int matrix[ROWS][COLS]);


int main()
{
	int matrix[ROWS][COLS]={0};
	for(int i=ROWS-1;i>ROWS-3;i--)
	{
		for(int j=0;j<COLS;j++)
		matrix[i][j]=1;
	}
	Part * part=GetPart(NULL);
	while(Falling(part,matrix))
	{
		Clean(matrix);
		Refresh(matrix,part);
	}
	return 0;
}

//刷新
void Refresh(int matrix[ROWS][COLS],Part * part)
{
	system("cls");//先清空屏幕
	int copy[ROWS][COLS];

	for(int i=0;i<ROWS;i++)
	{
		for(int j=0;j<COLS;j++)
			copy[i][j]=matrix[i][j];
	}
	for(int i=0;i<4;i++)
		copy[part->con[i].x+part->line][part->con[i].y]=1;
	for(int i=0;i<ROWS;i++)
	{
		for(int j=0;j<COLS;j++)
			cout<<copy[i][j]<<"  ";
		cout<<endl;
	}
	Sleep(500);
}


void Clean(int matrix[ROWS][COLS])//在part停止下落之后就可以开始消除了
{
	for(int i=ROWS-1;i>=0;i--)
	{
		bool bfull=false;
		for(int j=0;j<COLS&&matrix[i][j]!=0;j++)
		{
			if(j==COLS-1)
				bfull=true;
		}
		if(bfull)//如果全满的话就消掉这一层,整体下移一层
		{
			for(int j=0;j<COLS;j++)
			matrix[i][j]=0;
			DownStair(matrix,i);
		}

	}
}
void DownStair(int matrix[ROWS][COLS],int i)//在消掉一行后整体下移
{
	for(int di=i-1;di>=0;di--)
	{
		for(int dj=0;dj<COLS;dj++)
			matrix[di+1][dj]=matrix[di][dj];
	}
	for(int dj=0;dj<COLS;dj++)
			matrix[0][dj]=0;
}

Part * GetPart(Part * part)
{
	delete part;
	srand((unsigned)time(NULL));
	int index=int(rand()%7);
	part=new Part;
	for(int i=0;i<4;i++)
	{
		part->con[i].x=coordinate[index][i].x;
		part->con[i].y=coordinate[index][i].y;
	}
	part->line=0;
	return part;
}

bool Falling(Part * part,int matrix[ROWS][COLS])//判断是否在下落，如果下落，返回true并将part->line++，否则，返回false
{
	for(int i=0;i<4;i++)
	{
		if(matrix[part->con[i].x+part->line+1][part->con[i].y]!=0||part->line>=19)
		{
			return false;
		}
	}
	part->line++;
	rotate(part);
	return true;
}

void rotate(Part * part)
{
	for(int i=0;i<4;i++)
	{
		int x=part->con[i].x;
        int y=part->con[i].y;
        part->con[i].x=y;
       	part->con[i].y=3-x;
	}
}

