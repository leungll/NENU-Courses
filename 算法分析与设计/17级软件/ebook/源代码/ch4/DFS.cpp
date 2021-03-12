//图的深度遍历算法
#include "Graph.cpp"
#include <string.h>
int visited[MAXV];
void DFS(MGraph g,int v)
{	int w;
	printf("%3d",v);					//输出被访问顶点的编号
	visited[v]=1;						//置已访问标记
	for (w=0;w<g.n;w++)					//找顶点v的所有相邻点
		if (g.edges[v][w]!=0 && g.edges[v][w]!=INF && visited[w]==0)
			DFS(g,w);					//找顶点v的未访问过的相邻点w
}
void DFS(ALGraph *G,int v)
{	ArcNode *p;
	printf("%3d",v);					//输出被访问顶点的编号
	visited[v]=1;						//置已访问标记
	p=G->adjlist[v].firstarc;			//p指向顶点v的第一个邻接点
	while (p!=NULL)
	{	if (visited[p->adjvex]==0)		//若p->adjvex顶点未访问,递归访问它
			DFS(G,p->adjvex);
		p=p->nextarc;					//p指向顶点v的下一个邻接点
	}
}
void main()
{
	MGraph g;
	ALGraph *G;
	int A[][MAXV]={			//一个有向图
		{0,1,0,0,1},
		{0,0,1,1,1},
		{0,0,0,0,0},
		{0,0,1,0,1},
		{0,0,0,0,0}};
	int n=5,e=7;
	CreateMat(g,A,n,e);		//创建图的邻接矩阵存储结构g
	printf("图的邻接矩阵:\n");
	DispMat(g);				//输出邻接矩阵g
	memset(visited,0,sizeof(visited));	//初始化visited数组
	printf("DFS:");
	DFS(g,0);printf("\n");
	CreateAdj(G,A,n,e);		//创建图的邻接表存储结构G
	printf("图的邻接表:\n");
	DispAdj(G);				//输出邻接表G
	memset(visited,0,sizeof(visited));	//初始化visited数组
	printf("DFS:");
	DFS(G,0);printf("\n");
	DestroyAdj(G);
}
