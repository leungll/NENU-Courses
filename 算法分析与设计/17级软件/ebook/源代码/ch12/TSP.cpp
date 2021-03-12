#include "Graph.cpp"					//包含图的基本运算算法
#include <vector>
#include <string.h>
using namespace std;
//问题表示
MGraph g;								//图的邻接矩阵
//求解过程表示
MGraph tree;							//存放最小生成树
int visited[MAXV];
vector<int> path;						//存放TSP路径
void Prim(int v)						//产生最小生成树tree
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
		tree.edges[closest[k]][k]=mincost;//构建最小生成树的一条无向边
		tree.edges[k][closest[k]]=mincost;
		lowcost[k]=0;					//标记k已经加入U
		for (j=0;j<g.n;j++)			//修改数组lowcost和closest
			if (g.edges[k][j]!=0 && g.edges[k][j]<lowcost[j])
			{
				lowcost[j]=g.edges[k][j];
				closest[j]=k;
			}
	}
}
void DFS(int v)						//DFS算法
{	path.push_back(v);					//被访问顶点添加到path中
	visited[v]=1;						//置已访问标记
	for (int w=0;w<tree.n;w++)			//找顶点v的所有相邻点
		if (tree.edges[v][w]!=0 && tree.edges[v][w]!=INF && visited[w]==0)
			DFS(w);					//找顶点v的未访问过的相邻点w
}
void TSP(int v)						//TSP算法
{	tree.n=g.n;
	memset(tree.edges,INF,sizeof(tree.edges));
	Prim(v);
	memset(visited,0,sizeof(visited));
	DFS(v);
}
void ApproxTSP()						//输出TSP问题的近似解
{	vector<int> minpath;
	int minpathlen=INF;
	printf("求解结果\n");
	for (int v=0;v<g.n;v++)
	{	path.clear();
		TSP(v);
		printf("  从顶点%d出发查找:\n\t路径: ",v);
		int pathlen=0;
		for (int i=0;i<path.size();i++)
		{	printf("%d→",path[i]);
			if (i!=path.size()-1)
				pathlen+=g.edges[path[i]][path[i+1]];
		}
		printf("→%d",v);
		pathlen+=g.edges[path[path.size()-1]][v];
		printf(", 长度=%d\n",pathlen);
		if (pathlen>INF)
			printf("\t该路径不存在\n");
		else if (pathlen<minpathlen)
		{	minpathlen=pathlen;
			minpath=path;
		}
	}
	printf("  最优近似解\n\t路径: ");
	for (int i=0;i<minpath.size();i++)
		printf("%d→",minpath[i]);
	printf("→%d",minpath[0]);
	printf(", 长度=%d\n",minpathlen);
}
void main()
{	int A[][MAXV]={					//一个带权无向图
		{0,1,5,2,INF}, {1,0,INF,6,3},
		{5,INF,0,4,3}, {2,6,4,0,2}, {INF,3,3,2,0}};
	int n=5,e=8;
	CreateMat(g,A,n,e);				//创建图的邻接矩阵g
	ApproxTSP();
}
