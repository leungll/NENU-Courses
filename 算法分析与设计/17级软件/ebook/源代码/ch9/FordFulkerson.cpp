//求最大流的福特-富尔克逊算法
#include <stdio.h>
#include <string.h>
#define INF 0x3f3f3f3f						//∞
#define MAXV 20
//问题表示
int n=7,s=0,t=n-1;						//分别表示起点、终点和顶点个数
int f[][MAXV]={{0,6,10,INF,INF,INF,INF},//一个网络流
	{INF,0,INF,3,6,INF,INF},{INF,3,0,0,INF,7,INF},
	{INF,INF,INF,0,1,1,3},{INF,INF,INF,INF,0,INF,7},
	{INF,INF,INF,1,INF,0,6},{INF,INF,INF,INF,INF,INF,0}};
int c[][MAXV]={{0,8,14,INF,INF,INF,INF},	//一个网络流容量
	{INF,0,INF,3,6,INF,INF},{INF,5,0,3,INF,8,INF},
	{INF,INF,INF,0,4,3,10},	{INF,INF,INF,INF,0,INF,7},
	{INF,INF,INF,3,INF,0,6},{INF,INF,INF,INF,INF,INF,0}};
//求解结果表示
int maxf=0;									//最大流量			
//求解过程表示
int pre[MAXV];
int a[MAXV];
int visited[MAXV];
void DFS(int u)							//从顶点u出发求一条增广路径
{
	int v;
	if (visited[t]==1)					//若终点已标记，返回
		return;
	visited[u]=1;						//置已访问标志
	for (v=1;v<=t;v++)					//遍历前向边
	{
		if (c[u][v]>0 && c[u][v]!=INF && visited[v]==0 && c[u][v]>f[u][v])
		{
			a[v]=c[u][v]-f[u][v];
			pre[v]=u;
			DFS(v);
		}
	}
	for (v=1;v<=t;v++)					//遍历后向边
	{
		if (c[v][u]>0 && c[v][u]!=INF && visited[v]==0 && f[v][u]>0)
		{
			a[v]=f[v][u];
			pre[v]=-u;
			DFS(v);
		}
	}
}
void argument(int pre[])				//调整pre指定路径的流量
{
	int u,v,min=INF;
	for (v=s;v<=t;v++)
		if (a[v]!=0 && a[v]<min)
			min=a[v];					//求最小调整流量
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
void FordFulkerson()					//求最大流的福特-富尔克逊算法
{
	while (true)
	{
		memset(visited,0,sizeof(visited));
		memset(pre,-1,sizeof(pre));
		memset(a,0,sizeof(a));
		pre[s]=0; a[s]=INF;
		DFS(s);
		if (visited[t]==0)		//没有标记终点时退出循环
			break;
		argument(pre);
	}
	for (int v=1;v<=t;v++)			//从起点流出的流量和为最大流量			
		if (c[s][v]!=0 && c[s][v]!=INF)
			maxf+=f[s][v];
}
void main()
{
	FordFulkerson();
	printf("求解结果\n");
	printf("    最大流量=%d\n",maxf);	//输出:20
}
