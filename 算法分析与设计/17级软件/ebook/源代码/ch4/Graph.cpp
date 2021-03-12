//图的基本运算算法
#include <stdio.h>
#include <malloc.h>
#define MAXV 50					//最大顶点个数
#define MAXL 20
#define INF 0x3f3f3f3f			//表示∞
//邻接矩阵的类型定义如下：
typedef struct
{	int no;						//顶点编号
	char data[MAXL];			//顶点其他信息
} VertexType;					//顶点类型
typedef struct
{	int edges[MAXV][MAXV];		//邻接矩阵的边数组
	int n,e;					//顶点数，边数
	VertexType vexs[MAXV];		//存放顶点信息
} MGraph;						//完整的图邻接矩阵类型
//图的邻接表存储类型的定义如下：
typedef struct ANode
{	int adjvex;					//该边的终点编号
	int weight;					//该边的权值
	struct ANode *nextarc;		//指向下一条边的指针
} ArcNode;						//边结点类型
typedef struct Vnode
{	char data[MAXL];			//顶点其他信息
	ArcNode *firstarc;			//指向第一条边
} VNode;						//邻接表头结点类型
typedef VNode AdjList[MAXV];	//AdjList是邻接表类型
typedef struct 
{	AdjList adjlist;			//邻接表
	int n,e;					//图中顶点数n和边数e
} ALGraph;						//完整的图邻接表类型

void CreateMat(MGraph &g,int A[][MAXV],int n,int e)	//建立图的邻接矩阵
{	int i,j;
	g.n=n; g.e=e;
	for (i=0;i<n;i++)
		for (j=0;j<n;j++)
			g.edges[i][j]=A[i][j];
}
void DispMat(MGraph g)			//输出图的邻接矩阵
{	int i,j;
	printf("  n=%d,e=%d\n",g.n,g.e);
	for (i=0;i<g.n;i++)
	{	for (j=0;j<g.n;j++)
			if (g.edges[i][j]==INF)
				printf("%4s","∞");
			else
				printf("%4d",g.edges[i][j]);
		printf("\n");
	}
}
void CreateAdj(ALGraph *&G,int A[][MAXV],int n,int e)	//建立图的邻接表
{	int i,j;
	ArcNode *p;
	G=(ALGraph *)malloc(sizeof(ALGraph));
	G->n=n; G->e=e;
	for (i=0;i<n;i++)
		G->adjlist[i].firstarc=NULL;
	for (i=0;i<n;i++)
		for (j=0;j<n;j++)
			if (A[i][j]!=0 && A[i][j]!=INF)
			{	p=(ArcNode *)malloc(sizeof(ArcNode));
				p->adjvex=j;
				p->weight=A[i][j];
				p->nextarc=G->adjlist[i].firstarc;
				G->adjlist[i].firstarc=p;
			}
}
void DispAdj(ALGraph *G)		//输出图的邻接表
{	int i;
	ArcNode *p;
	printf("n=%d,e=%d\n",G->n,G->e);
	for (i=0;i<G->n;i++)
	{	printf("[%3d]:",i);
		p=G->adjlist[i].firstarc;
		while (p!=NULL)
		{	printf("→(%d,%d)",p->adjvex,p->weight);
			p=p->nextarc;
		}
		printf("→∧\n");
	}
}
void DestroyAdj(ALGraph *&G)	//销毁图的邻接表
{	int i;
	ArcNode *pre,*p;
	for (i=0;i<G->n;i++)
	{	pre=G->adjlist[i].firstarc;
		while (pre!=NULL)
		{	p=pre->nextarc;
			free(pre);
			pre=p;
		}
	}
	free(G);
}
