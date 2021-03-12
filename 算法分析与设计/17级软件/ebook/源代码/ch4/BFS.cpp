//图的广度遍历算法
#include "Graph.cpp"
#include <queue>
#include <string.h>
using namespace std;

void BFS(MGraph g,int v)					//邻接矩阵的DFS算法
{
	queue<int> qu;							//定义一个队列qu
	int visited[MAXV];						//定义存放结点的访问标志的数组
	int w,i;
	memset(visited,0,sizeof(visited));		//访问标志数组初始化

	printf("%3d",v);						//输出被访问顶点的编号
	visited[v]=1;							//置已访问标记
	qu.push(v);								//v进队
	while (!qu.empty())						//队列不空时循环
	{
		w=qu.front(); qu.pop();				//出队顶点w
		for (i=0;i<g.n;i++)					//找与顶点w相邻的顶点
			if (g.edges[w][i]!=0 && g.edges[w][i]!=INF && visited[i]==0)
			{	//若当前邻接顶点i未被访问
				printf("%3d",i);			//访问相邻顶点
				visited[i]=1;				//置该顶点已被访问的标志
				qu.push(i);					//该顶点进队
			}
	}
	printf("\n");
}
void BFS(ALGraph *G,int v)					//邻接表的DFS算法
{
	ArcNode *p;
	queue<int> qu;							//定义一个队列qu
	int visited[MAXV];						//定义存放顶点的访问标志的数组
	int w;
	memset(visited,0,sizeof(visited));		//访问标志数组初始化
	printf("%3d",v);						//输出被访问顶点的编号
	visited[v]=1; 							//置已访问标记
	qu.push(v);								//v进队
	while (!qu.empty())						//队列不空时循环
	{
		w=qu.front(); qu.pop();				//出队顶点w
		p=G->adjlist[w].firstarc;			//找顶点w的第一个邻接点
		while (p!=NULL) 
		{	if (visited[p->adjvex]==0)		//若当前邻接顶点未被访问
			{	printf("%3d",p->adjvex);	//访问相邻顶点
				visited[p->adjvex]=1;		//置该顶点已被访问的标志
				qu.push(p->adjvex);			//该顶点进队
			}
			p=p->nextarc;					//找顶点w的下一个邻接点
		}
	}
	printf("\n");
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
	printf("BFS:");
	BFS(g,0);printf("\n");
	CreateAdj(G,A,n,e);		//创建图的邻接表存储结构G
	printf("图的邻接表:\n");
	DispAdj(G);				//输出邻接表G
	printf("BFS:");
	BFS(G,0);printf("\n");
	DestroyAdj(G);
}
