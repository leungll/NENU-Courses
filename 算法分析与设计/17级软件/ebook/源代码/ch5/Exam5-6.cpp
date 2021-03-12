//例5.6的算法
#include "Graph.cpp"
#include <vector>
using namespace std;
int visited[MAXV];						//全局变量
void dispapath(vector<int> path)		//输出一条路径
{
	printf("  ");
	for (int i=0;i<path.size();i++)
		printf("%d  ",path[i]);
	printf("\n");
}
void dfs(ALGraph *G,int u,int v,vector<int> path)	//输出u到v的全部路径
{
	ArcNode *p;
	path.push_back(u);				//路径长度d增1，顶点u加入到路径中
	visited[u]=1;					//置已访问标记
	if (u==v && path.size()>=1)		//找到一条路径则输出
		dispapath(path);
	p=G->adjlist[u].firstarc;		//p指向顶点u的第一个相邻点
	while (p!=NULL)
	{	int w=p->adjvex;			//w为顶点u的相邻点
		if (visited[w]==0)			//若w顶点未访问,递归访问它
			dfs(G,w,v,path);
		p=p->nextarc;				//p指向顶点u的下一个相邻点
	}
	visited[u]=0;					//回溯
}
void main()
{
	ALGraph *G;
	int A[][MAXV]={				//《教程》中图4.11的有向图
		{0,1,0,0,1},
		{0,0,1,1,1},
		{0,0,0,0,0},
		{0,0,1,0,1},
		{0,0,0,0,0}};
	int n=5,e=7;
	CreateAdj(G,A,n,e);			//创建图的邻接表存储结构G
	vector<int> path,apath;
	int u=0,v=2;
	printf("从顶点%d到%d的全部路径\n",u,v),
	memset(visited,0,sizeof(visited));
	dfs(G,u,v,path);
	DestroyAdj(G);				//销毁图G
}
