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

#define SIZE 4//为什么SIZE 不能用const？

const int ROWS=20;//使用const 类型常量比用define好
const int COLS=10;


using namespace std;

struct Coordinate//字如其名，就是坐标
{
    int x;
    int y;
};

//七种基本类型

Coordinate coordinate[7][4]=//第0个是4*4，第3个是2*2，其余是3*3
{
    {{1,0},{1,1},{1,2},{1,3}},//一条横线，4*4方格
    {{0,0},{1,0},{1,1},{1,2}},//3*3
    {{1,0},{1,1},{1,2},{0,2}},//3*3
    {{0,0},{0,1},{1,0},{1,1}},//田字形2*2
    {{1,0},{1,1},{0,1},{0,2}},//之字形1 3*3
    {{1,0},{1,1},{1,2},{0,1}},//土字形 3*3
    {{0,0},{0,1},{1,1},{1,2}}//之字形2 3*3
};


struct Part//用来储存现在part的信息的结构
{
	int type;
    Coordinate con[4];
    int line;
};

void Refresh(int matrix[ROWS][COLS],Part * part);
void DownStair(int matrix[ROWS][COLS],int i);
void Clean(int matrix[ROWS][COLS]);
Part * GetPart(Part * part);
bool rotate(Part * part，int matrix[ROWS][COLS])；
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
	tag:while(Falling(part,matrix))
	{
		Clean(matrix);
		Refresh(matrix,part);
	}
	part=GetPart(part);
	goto tag;
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
	Sleep(100);
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
	part=new Part;
	part->type=rand()%7;
	for(int i=0;i<4;i++)
	{
		part->con[i].x=coordinate[part->type][i].x;
		part->con[i].y=coordinate[part->type][i].y;
	}
	part->line=0;
	return part;
}

bool Falling(Part * part,int matrix[ROWS][COLS])//判断是否在下落，如果下落，返回true并将part->line++，否则，返回false
{
	rotate(part);
	for(int i=0;i<4;i++)
	{

		if(matrix[part->con[i].x+part->line+1][part->con[i].y]!=0||part->line>=ROWS-1)
			{
				for(int i=0;i<4;i++)
					matrix[part->con[i].x+part->line][part->con[i].y]=1;
				return false;

			}
	}
	part->line++;
	return true;
}

bool rotate(Part * part，int matrix[ROWS][COLS])//这个函数还是有点问题，我们要考虑到能不能旋转
{	
	int stat=0;
	Coordinate xy[SIZE];
	switch(part->type)
	{
		case 0:stat=3; break;
		case 3:stat=1; break;
		default:stat=2;break;
	}
	for(int i=0;i<SIZE;i++)
    {
       xy[i].x=part->con[i].y,xy[i].y=stat-part->con[i].x;
       if(matrix[xy[i].x+part->line][matrix[xy[i].y]!=0)
      	return false

    }
    return true;
}

