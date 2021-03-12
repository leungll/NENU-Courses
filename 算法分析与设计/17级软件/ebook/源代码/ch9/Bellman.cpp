//贝尔曼-福特算法－求单源最短路径
#include "Graph.cpp"
void disp(MGraph g,int dist[],int path[],int k)	//输出dist和path用作调试
{
	int i;
	printf("k=%d\n",k);
	printf("dist:\n");
	for (i=0;i<g.n;i++)
		printf("%4d",i);
	printf("\n");
	for (i=0;i<g.n;i++)
		if (dist[i]!=INF)
			printf("%4d",dist[i]);
		else
			printf("%4s","∞");
	printf("\n");
	printf("path:\n");
	for (i=0;i<g.n;i++)
		printf("%4d",i);
	printf("\n");
	for (i=0;i<g.n;i++)
		printf("%4d",path[i]);
	printf("\n");
}
void Dispath(MGraph g,int dist[],int path[],int v)
//输出从顶点v出发的所有最短路径
{	int i,j,k;
	int apath[MAXV],d;					//存放一条最短路径(逆向)及其顶点个数
	for (i=0;i<g.n;i++)					//循环输出从顶点v到i的路径
		if (i!=v)
		{	printf("  从顶点%d到顶点%d的路径长度为:%d\t路径为:",v,i,dist[i]);
			d=0; apath[d]=i;			//添加路径上的终点
			k=path[i];
			if (k==-1)					//没有路径的情况
				printf("无路径\n");
			else						//存在路径时输出该路径
			{	while (k!=v)
				{	d++; apath[d]=k;
					k=path[k];
				}
				d++; apath[d]=v;		//添加路径上的起点
				printf("%d",apath[d]);	//先输出起点
				for (j=d-1;j>=0;j--)	//再输出其他顶点
					printf(",%d",apath[j]);
				printf("\n");
			}
		}
}
bool hasminusCycle(MGraph g,int dist[])	//判断是否存在负回路
{
	for (int i=0;i<g.n;i++)
		for (int j=0;j<g.n;j++)			//处理每一条边<i,j>
		{
			if (g.edges[i][j]>0 && g.edges[i][j]<INF)
			{
				if (dist[j]>dist[i]+g.edges[i][j])
					return true;		//存在负回路
			}
		}
	return false;						//不存在负回路
}

void BellmanFord(MGraph g,int v)
{
	int i,k,u;
	int dist[MAXV],path[MAXV];
	for (i=0;i<g.n;i++)
	{
		dist[i]=g.edges[v][i];			//对dist(0)[i]初始化
		if (i!=v && dist[i]<INF) 
			path[i]=v;					//对path(0)[i]初始化
		else 
			path[i]=-1;
	}
	disp(g,dist,path,0);
	for (k=1;k<g.n;k++) //从dist(0)[u]递推出dist(1)[u], …,dist(n-1)[u]循环n-1次
	{
		for (u=0;u<g.n; u++)			//修改每个顶点的dist[u]和path[u]
		{
			if (u!=v)
			{
				for (i=0;i<g.n;i++)		//考虑其他每个顶点
				{
					if (g.edges[i][u]<INF && dist[u]>dist[i]+g.edges[i][u])
					{
						dist[u]=dist[i]+g.edges[i][u];
						path[u]=i;
					}
				}
			}
		}
		disp(g,dist,path,k);			//输出调试信息
	}
	Dispath(g,dist,path,v);				//输出最短路径及长度
	printf("是否存在负回路: %d\n",hasminusCycle(g,dist));
}
/*
void main()
{
	int n=7,e=12;
	int v=0;
	MGraph g;
	int A[7][MAXV]={
		{0,4,-6,6,INF,INF,INF},
		{INF,0,1,INF,7,INF,INF},
		{INF,INF,0,INF,6,4,INF},
		{INF,INF,2,0,INF,5,INF},
		{INF,INF,INF,INF,0,INF,6},
		{INF,INF,INF,INF,1,0,-8},
		{INF,INF,INF,INF,INF,INF,0}};
	CreateMat(g,A,n,e);		//创建图的邻接矩阵存储结构g
	printf("图的邻接矩阵:\n");
	DispMat(g);				//输出邻接矩阵g
	printf("从%d顶点出发的最短路径:\n",v);
	BellmanFord(g,v);
	printf("\n");
}
*/
void main()
{
	int n=3,e=3;
	int v=0;
	MGraph g;
	int A[3][MAXV]={
		{0,1,INF},
		{INF,0,-4},
		{2,INF,0}};
	CreateMat(g,A,n,e);		//创建图的邻接矩阵存储结构g
	printf("图的邻接矩阵:\n");
	DispMat(g);				//输出邻接矩阵g
	printf("从%d顶点出发的最短路径:\n",v);
	BellmanFord(g,v);
	printf("\n");
}
