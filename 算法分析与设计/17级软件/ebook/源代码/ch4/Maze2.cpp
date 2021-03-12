#include <stdio.h>
#define MAXQ 100					//队列大小
#define MAxN 10						//最大迷宫大小
//问题表示
int n=8;							//迷宫大小
char Maze[MAxN][MAxN]=
{	{'O','X','X','X','X','X','X','X'},
	{'O','O','O','O','O','X','X','X'},
	{'X','O','X','X','O','O','O','X'},
	{'X','O','X','X','O','X','X','O'},
	{'X','O','X','X','X','X','X','X'},
	{'X','O','X','X','O','O','O','X'},
	{'X','O','O','O','O','X','O','O'},
	{'X','X','X','X','X','X','X','O'}
};
int H[4] = {0, 1, 0, -1};			//水平偏移量,下标对应方位号0～3
int V[4] = {-1, 0, 1, 0};			//垂直偏移量
struct Position						//队列元素类型
{
	int x,y;						//当前方块位置
	int pre;						//前驱方块的下标
};
Position qu[MAXQ];					//定义一个队列qu
int front=-1,rear=-1;				//定义队头和队尾

void disppath(int front)			//输出一条迷宫路径
{
	int i,j;
	for (i=0; i<n;i++)				//将所有'*'改为'O'
		for (j=0;j<n;j++)
			if (Maze[i][j]=='*')
				Maze[i][j]='O';
	int k=front;
	while (k!=-1)					//即路径上的方块改为' '
	{
		Maze[qu[k].x][qu[k].y]=' ';
		k=qu[k].pre;
	}
	for (i=0; i<n;i++)				//输出迷宫路径
	{	printf("    ");
		for(int j=0; j<n;j++)
			printf("%c",Maze[i][j]);
		printf("\n");
	}
}
void BFS(int x,int y)			 //求从(x,y)出发的一条迷宫路径
{
	Position p,p1,p2;
	p.x=x; p.y=y; p.pre=-1;			//建立入口结点
	Maze[p.x][p.y]='*';				//改为'*'避免重复查找
	rear++; qu[rear]=p;				//入口方块进队
	while (front!=rear)				//队不空循环
	{
		front++; p1=qu[front];		//出队方块p1;
		if (p1.x==n-1 && p1.y==n-1)	//找到出口
		{
			disppath(front);		//输出路径
			return;
		}
		for (int k=0;k<4;k++)		//试探p1的每个相邻方位
		{
			p2.x=p1.x+V[k];			//找到p1的相邻方块p2
			p2.y=p1.y+H[k];
			if (p2.x>=0 && p2.y>=0 && p2.x<n && p2.y<n && Maze[p2.x][p2.y]=='O')
			{	//方块p2有效并且可走
				Maze[p2.x][p2.y]='*';	//改为'*'避免重复查找
				p2.pre=front;
				rear++;	qu[rear]=p2;	//方块p2进队
			}
		}
	}
}
void main()
{
	int x=0,y=0;		//指定入口,出口默认为(n-1,n-1)
	printf("一条迷宫路径:\n");
	BFS(x,y);			//求(0,0)->(7,7)的一条迷宫路径
}
