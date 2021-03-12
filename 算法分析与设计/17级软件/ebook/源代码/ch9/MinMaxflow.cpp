//求最小费用最大流算法
#include <stdio.h>
#include <string.h>
#define MAXV 10
#define INF 0x3f3f3f3f
//问题表示
int n=6,s=0,t=n-1;						//分别表示起点、终点和顶点个数
int c[MAXV][MAXV]={{0,4,5,INF,INF,INF}, //一个网络流容量
	{INF,0,1,3,INF,INF},{INF,INF,0,INF,2,INF},
	{INF,INF,INF,0,INF,5},{INF,1,INF,3,0,2},
	{INF,INF,INF,INF,INF,0}};
int b[MAXV][MAXV]={{0,1,3,INF,INF,INF},	//一个网络流单位流量费用
	{INF,0,1,3,INF,INF},{INF,INF,0,INF,4,INF},
	{INF,INF,INF,0,INF,2},{INF,2,INF,1,0,4},
	{INF,INF,INF,INF,INF,0}};
//求解结果表示
int w[MAXV][MAXV];				//一个赋权图w
int f[MAXV][MAXV];				//网络流
int maxf=0;						//最大流量
int mincost=0;					//最大流最小费用
void Createw()					//由c、b和f构造赋权图w
{
	int i,j;
	for (i=0;i<n;i++)			//w数组元素初始化
		for (j=0;j<n;j++)
			w[i][j]=INF;
	for (i=0;i<n;i++)
		for (j=0;j<n;j++)
		{
			if (c[i][j]!=0 && c[i][j]<INF)
			{
				if (f[i][j]<c[i][j])
					w[i][j]=b[i][j];
				else if (f[i][j]==c[i][j])
					w[i][j]=INF;
				if (f[i][j]>0)
					w[j][i]=-b[i][j];
				else if (f[i][j]==0)
					w[j][i]=INF;
			}
			else if (i==j)
				w[i][j]=0;
		}
}
bool BellmanFord(int path[])		//对w求从s到t的最短路径path
{
	int dist[MAXV];					//dist[i]存放s到顶点i的最短路径长度
	for (int i=0;i<n;i++)			//初始化
	{
		dist[i]=w[s][i];			//对dist(0)[i]初始化
		if (i!=s && dist[i]<INF) 
			path[i]=s;				//对path(0)[i]初始化
		else 
			path[i]=-1;
	}
	for (int k=1;k<n;k++)
	{
		for (int u=0;u<n; u++)		//修改每个顶点的dist[u]和path[u]
		{
			if (u!=s)
			{
				for (int i=0;i<n;i++)	//考虑其他每个顶点
				{
					if (w[i][u]<INF && dist[u]>dist[i]+w[i][u])
					{
						dist[u]=dist[i]+w[i][u];
						path[u]=i;
					}
				}
			}
		}
	}
	if (path[t]==-1)
		return false;	//当没有从起点到终点的最短路径,返回false
	else
		return true;	//当存在从起点到终点的最短路径,返回true
}
int Getargpathmin(int path[])	//求path表示的最小调整量min
{
	int i,j,min=INF;
	j=t; i=path[j];							//从终点t向前调整
	while (true)
	{
		if (c[i][j]>0 && c[i][j]<INF)		//处理前向边
		{
			if (c[i][j]-f[i][j]<min)
				min=c[i][j]-f[i][j];
		}
		if (c[j][i]>0 && c[j][i]<INF)		//处理后向边
		{
			if (f[j][i]<min)
				min=f[j][i];
		}
		if (i==s) break;					//当到达起点时退出循环
		j=i;
		i=path[j];
	}
	return min;
}
void argument(int path[],int min)		//根据最小调整量min对增广链进行调整
{
	int i,j;
	j=t,i=path[j];
	maxf+=min;
	while (true)
	{
		if (c[i][j]>0 && c[i][j]<INF)		//前向边调整
		{
			f[i][j]+=min;
			mincost+=min*b[i][j];			//累计最小费用
		}
		if (c[j][i]>0 && c[j][i]<INF)		//后向边调整
		{
			f[j][i]-=min;
			mincost+=-min*b[j][i];			//累计最小费用
		}
		if (i==s) break;					//当到达起点时退出循环
		j=i;
		i=path[j];
	}
}
void FordFulkerson()			//求最小费用最大流f
{
	int k=0;
	int path[MAXV],min;
	while (true)
	{
		Createw();
		if (BellmanFord(path))
		{
			min=Getargpathmin(path);
			argument(path,min);
		}
		else break;
	}
}
void main()
{
	memset(f,0,sizeof(f));		
	FordFulkerson();
	printf("求解结果\n");
	printf("    最大网络流量: %d\n",maxf);
	printf("    最大流最小费用: %d\n",mincost);
}
