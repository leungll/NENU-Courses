//动态规划求解TSP问题
#include "Graph.cpp"
#include <stdio.h>
#include <string.h>
#include <set>
#include <vector>
using namespace std;
#define MAX 11								//顶点个数n对应的最多二进制位数
#define min(x,y) ((x)<(y)?(x):(y))
typedef set< int > SET;						//采用set<int>表示顶点集合
//问题表示
int s=0;									//指定起点为0
MGraph g;									//图的邻接矩阵
//求解结果表示
int dp[1<<MAX][MAX];
int minpathlen;								//存放最短路径长度
vector<int> minpath;						//存放最短路径(逆向)
void solve()								//求TSP问题
{
	int n=g.n-1;							//n为顶点个数减1（除开起点0）
	memset(dp,0,sizeof(dp));				//dp元素初始化为0
	for(int V=0; V<=(1<<n)-1; V++)
	{
		for(int i=1; i<=n; i++)				//先对1~n的顶点枚举
			if(V & (1<<(i-1)))				//顶点i在集合V中的情况
			{
				if(V==(1<<(i-1)))			//如果V={i}
					dp[V][i]=g.edges[0][i];
				else
				{
					dp[V][i]=INF;
					for(int j=1; j<=n; j++)
						if(V & (1<<(j-1)) && i!=j)	//枚举V中顶点i外的其他顶点j
							dp[V][i]=min(dp[V][i],dp[V^(1<<(i-1))][j]+g.edges[j][i]);
               	}
           	}
	}
}
void BuildPath()				//构建最短路径
{
	minpathlen=INF;
	int n=g.n-1;
	int V=(1<<n)-1,minj;
	for(int j=1; j<=n; j++)		//求最短路径长度
	{
		if (minpathlen>dp[V][j]+g.edges[j][0])
		{
			minpathlen=dp[V][j]+g.edges[j][0];
			minj=j;
		}
	}
	while (V!=0)					//求最短路径
	{
		minpath.push_back(minj);
		V=(V^(1<<(minj-1)));		//从V中删除顶点minj
		int mindp=INF;
		for (int i=1;i<=n;i++)		//查找dp[V][*]中不为0的最小dp[V][minj]
		{
			if (dp[V][i]!=0 && dp[V][i]<mindp)
			{
				mindp=dp[V][i];
				minj=i;
			}
		}
	}
}
void main()
{
	int A[][MAXV]={						//一个带权有向图
		{0,8,5,6},{6,0,8,5},{8,9,0,5},{7,7,8,0}};
	int n=4,e=12;
	CreateMat(g,A,n,e);					//创建图的邻接矩阵g
	solve();
	BuildPath();
	printf("求解结果\n");
	printf("    最短路径长度: %d\n",minpathlen);
	printf("    最短路径: 0→");
	for (int i=minpath.size()-1;i>=0;i--)
		printf("%d→",minpath[i]);
	printf("0\n");
}
