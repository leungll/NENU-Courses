#include <stdio.h>
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
void disppath()						//输出一条迷宫路径
{
	for (int i=0; i<n;i++)
	{
		printf("    ");
		for(int j=0; j<n;j++)
			printf("%c",Maze[i][j]);
		printf("\n");
	}
}
void DFS(int x,int y)			 //求从(x,y)出发的一条迷宫路径
{
	if (x==n-1 && y==n-1) //找到一条路径,输出
	{
		Maze[n-1][n-1]=' ';
		disppath();
		return;
	}
	else
	{	for (int k=0;k<4;k++)				 //试探每一个方位
			if(x>=0 && y>=0 && x<n && y<n && Maze[x][y]=='O')
			{								//若(x,y)方块的可走的
				Maze[x][y]=' ';				//将该方块设置为空字符
				DFS(x+V[k],y+H[k]);			//查找(x,y)周围的每一个相邻方块
				Maze[x][y]='O';				//若从该相邻方块出发没有找到路径,恢复(x,y)
			}
	}
}
void main()
{
	int x=0,y=0;		//指定入口,出口默认为(n-1,n-1)
	printf("一条迷宫路径:\n");
	DFS(x,y);			//求(0,0)->(7,7)的一条迷宫路径
}
