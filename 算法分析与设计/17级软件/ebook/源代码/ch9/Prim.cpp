//普里姆算法求最小生成树
#include "Graph.cpp"
void Prim(MGraph g,int v)
{	int lowcost[MAXV];
	int mincost;
	int closest[MAXV],i,j,k;
	for (j=0;j<g.n;j++)				//给初始化lowcost和closest数组
	{	lowcost[j]=g.edges[v][j];
		closest[j]=v;
	}
	for (i=1;i<g.n;i++)				//找出(n-1)个顶点
	{	mincost=INF;
		for (j=0;j<g.n;j++)			//在(V-U)中找出离U最近的顶点k
			if (lowcost[j]!=0 && lowcost[j]<mincost)
			{	mincost=lowcost[j];
				k=j;					//k记录最近顶点的编号
			}
		printf(" 边(%d,%d)权为:%d\n",closest[k],k,mincost);
		lowcost[k]=0;					//标记k已经加入U
		for (j=0;j<g.n;j++)				//修改数组lowcost和closest
			if (g.edges[k][j]!=0 && g.edges[k][j]<lowcost[j])
			{
				lowcost[j]=g.edges[k][j];
				closest[j]=k;
			}
	}
}
void main()
{
	MGraph g;
	int A[][MAXV]={			//一个带权无向图
		{0,  6,  INF,INF,INF,1,  INF},
		{6,  0,  4,  INF,INF,INF,3},
		{INF,4,  0,  2,  INF,INF,INF},
		{INF,INF,2,  0,  6,  INF,5},
		{INF,INF,INF,6,  0,  8,  7},
		{1,  INF,INF,INF,8,  0,  INF},
		{INF,3,  INF,5,  7,  INF,0}};
	int n=7,e=9;
	CreateMat(g,A,n,e);		//创建图的邻接矩阵g
	printf("图的邻接矩阵:\n");
	DispMat(g);				//输出邻接矩阵g
	printf("Prim算法结果:\n");
	Prim(g,0);
}
