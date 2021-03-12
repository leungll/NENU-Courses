//求最大流的福特-富尔克逊算法
#include <stdio.h>
#include <string.h>
#define INF 0x3f3f3f3f						//∞
#define MAXV 20
int pre[MAXV],a[MAXV],visited[MAXV];		//全局变量
int s,t,n;									//全局变量，分别表示起点、终点和顶点个数
int maxf=0;									//最大流量
void DFS(int c[][MAXV],int f[][MAXV],int u)	//求一条增广路径
{
	int v;
	if (visited[t]==1)		//若终点已标记，返回
		return;
	visited[u]=1;			//置已访问标志
	for (v=1;v<=t;v++)		//遍历前向边
	{
		if (c[u][v]>0 && c[u][v]!=INF && visited[v]==0 && c[u][v]>f[u][v])
		{
			a[v]=c[u][v]-f[u][v];
			pre[v]=u;
			DFS(c,f,v);
		}
	}
	for (v=1;v<=t;v++)		//遍历后向边
	{
		if (c[v][u]>0 && c[v][u]!=INF && visited[v]==0 && f[v][u]>0)
		{
			a[v]=f[v][u];
			pre[v]=-u;
			DFS(c,f,v);
		}
	}
}
void argument(int f[][MAXV],int pre[],int a[])		//调整流量
{
	int u,v,min=INF;
	for (v=s;v<=t;v++)
		if (a[v]!=0 && a[v]<min)
			min=a[v];					//求最小调整流量
	maxf+=min;
	u=t; v=pre[u];						//从路径的终点开始调整
	while (true)
	{
		if (v>=0)						//调整正向边
		{
			f[v][u]+=min;
			u=v;

		}
		else							//调整反向边
		{
			f[u][-v]-=min;
			u=-v;
		}
		if (u==s) break;				//到达起点结束
		v=pre[u];
	}
}
int FordFulkerson(int c[][MAXV],int f[][MAXV])	//求最大流
{
	int count=0;
	while (true)
	{
		memset(visited,0,sizeof(visited));
		memset(pre,-1,sizeof(pre));
		memset(a,0,sizeof(a));
		pre[s]=0; a[s]=INF;
		DFS(c,f,s);
		if (visited[t]==0)		//没有标记终点时退出循环
			break;
		argument(f,pre,a);
	}
	return maxf;				//返回最大流量
}
void main()
{
	int f[MAXV][MAXV];
	memset(f,0,sizeof(f));			//一个零网络流,从零流开始调整，maxf=所有最小调整量之和
	int c[][MAXV]={					//一个网络流容量
		{0,8,14,INF,INF,INF,INF},
		{INF,0,INF,3,6,INF,INF},
		{INF,5,0,3,INF,8,INF},
		{INF,INF,INF,0,4,3,10},
		{INF,INF,INF,INF,0,INF,7},
		{INF,INF,INF,3,INF,0,6},
		{INF,INF,INF,INF,INF,INF,0}};
	n=7; s=0; t=n-1;
	printf("最大流量=%d\n",FordFulkerson(c,f));
}
