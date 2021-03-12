//例9.2的算法
#include "Graph.cpp"
#include <string.h>
#include <vector>
using namespace std;
int visited[MAXV];
void FindaPath(ALGraph *G,int u,int v,vector<int> apath,vector<int> &path)
{
	int w;
	ArcNode *p;
	visited[u]=1;
	apath.push_back(u);			//顶点u加入到apath路径中
	if (u==v)					//找到一条路径
	{
		path=apath;				//将apath复制到path
		return;					//返回true
	}
	p=G->adjlist[u].firstarc;	//p指向顶点u的第一个相邻点
	while (p!=NULL)
	{
		w=p->adjvex;			//相邻点的编号为w
		if (visited[w]==0)
			FindaPath(G,w,v,apath,path);
		p=p->nextarc;			//p指向顶点u的下一个相邻点
	}
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
	vector<int> path,apath;
	for (int i=0;i<n;i++)
		for (int j=0;j<n;j++)
			if (i!=j)
			{
				memset(visited,0,sizeof(visited));
				path.clear();
				FindaPath(G,i,j,apath,path);
				if (path.size()>0)
				{
					printf("顶点%d到%d的简单路径: ",i,j);
					for (int k=0;k<path.size();k++)
						printf("%d ",path[k]);
					printf("\n");
				}
			}
	DestroyAdj(G);
}
