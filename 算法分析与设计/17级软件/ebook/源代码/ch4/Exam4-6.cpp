//例4.6的算法
#include "Graph.cpp"				//包含图的基本运算算法
#include <string.h>
int visited[MAXV];
bool ExistPath(ALGraph *G,int u,int v)	//判断G中从顶点u到v是否存在简单路径
{
	int w;
	ArcNode *p;
	visited[u]=1;					//置已访问标记
	if (u==v)						//找到了一条路径
		return true;
	p=G->adjlist[u].firstarc;		//p指向顶点u的第一个相邻点
	while (p!=NULL)
	{	w=p->adjvex;				//w为顶点u的相邻顶点
		if (visited[w]==0)			//若w顶点未访问,递归访问它
		{
			bool flag=ExistPath(G,w,v);
			if (flag) return true;
		}
		p=p->nextarc;				//p指向顶点u的下一个相邻点
	}
	return false;
}
void main()
{
	ALGraph *G;
	int A[][MAXV]={			//《教程》中图4.11的有向图
		{0,1,0,0,1},
		{0,0,1,1,1},
		{0,0,0,0,0},
		{0,0,1,0,1},
		{0,0,0,0,0}};
	int n=5,e=7;
	CreateAdj(G,A,n,e);		//创建图的邻接表存储结构G
	printf("图的邻接表:\n");
	DispAdj(G);				//输出邻接表G
	for (int i=0;i<n;i++)
		for (int j=0;j<n;j++)
		{
			memset(visited,0,sizeof(visited));
			if (ExistPath(G,i,j) && i!=j)
				printf("顶点%d到顶点%d存在简单路径\n",i,j);
		}
	DestroyAdj(G);
}
