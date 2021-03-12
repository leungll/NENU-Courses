#include <string.h>
#include <map>
using namespace std;
#define MAX 21
#define INF 0x3f3f3f3f
//问题表示
int n;							//顶点个数
int start;						//起点编号
int end;						//终点编号
int c[MAX][MAX];				//存放边长度
int pre[MAX];					//存放最短路径上当前顶点的后继顶点
map<int,char *> vname;			//存放编号对应的顶点名称

int dp[MAX];
int Count=1;					//计算步骤
void Init()						//初始化
{
	n=10;
	start=0;
	end=9;
	memset(c,INF,sizeof(c));
	for (int i=0;i<n;i++)		//初始化为-1
		dp[i]=-1;
	for (int j=0;j<n;j++)
		c[j][j]=0;
	c[0][1]=2; c[0][2]=4; c[0][3]=3;
	c[1][4]=7; c[1][5]=4;
	c[2][4]=3; c[2][5]=2; c[2][6]=4;
	c[3][4]=6; c[3][5]=2; c[3][6]=5;
	c[4][7]=3; c[4][8]=4;
	c[5][7]=6; c[5][8]=3;
	c[6][7]=3; c[6][8]=3;
	c[7][9]=3;
	c[8][9]=4;
	vname[0]="A";
	vname[1]="B1";	vname[2]="B2";	vname[3]="B3";
	vname[4]="C1";	vname[5]="C2";	vname[6]="C3";
	vname[7]="D1";	vname[8]="D2";
	vname[9]="E";
}
int f(int s)								//动态规划问题的顺序解法
{
	if (dp[s]!=-1) return dp[s];
	if (s==start)								//找到终点
	{
		dp[s]=0;
		printf("  (%d) f(%s)=0\n",Count++,vname[s]);
		return dp[s];
	}
	else
	{
		int cost,mincost=INF,mini;
		for (int i=0;i<n;i++)				//查找顶点s的前驱顶点
		{
			if (c[i][s]!=0 && c[i][s]!=INF)	//顶点i到s有边
			{
				cost=f(i)+c[i][s];			//先求出前驱顶点的f值
				if (mincost>cost)
				{
					mincost=cost;
					mini=i;
				}
			}
		}
		dp[s]=mincost;
		pre[s]=mini;
		printf("  (%d) f(%s)=f(%s)+c(%s,%s)=%d, ",Count++,vname[s],vname[mini],vname[mini],vname[s],dp[s]); 
		printf("pre(%s)=%s\n",vname[s],vname[mini]);
		return dp[s];
	}
}
void main()
{
	Init();
	printf("%s→%s求解过程\n",vname[start],vname[end]);
	f(end);
}



