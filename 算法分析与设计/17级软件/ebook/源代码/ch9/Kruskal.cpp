//克鲁斯卡尔算法求最小生成树
#include "Graph.cpp"
#include <algorithm>
using namespace std;
#define MaxSize 100
//----并查集基本运算--------
typedef struct node
{	int data;			//结点对应顶点编号
	int rank;			//结点对应秩
	int parent;		//结点对应双亲下标
} UFSTree;			//并查集树的结点类型
void MAKE_SET(UFSTree t[],int n)	//初始化并查集树
{ 	for (int i=0;i<n;i++)			//顶点编号为0～(n-1)
	{	t[i].rank=0;				//秩初始化为0
		t[i].parent=i;				//双亲初始化指向自已
	}
}
int FIND_SET(UFSTree t[],int x)			//在x所在子树中查找集合编号
{	if (x!=t[x].parent)					//若双亲不是自已
		return(FIND_SET(t,t[x].parent));	//递归在双亲中找x
	else
		return(x);						//若双亲是自已,返回x
}
void UNION(UFSTree t[],int x,int y)		//将x和y所在的子树合并
{	x=FIND_SET(t,x);
	y=FIND_SET(t,y);
	if (t[x].rank>t[y].rank)			//x结点的秩大于y结点的秩
		t[y].parent=x;				//将x结点作为y的双亲结点
	else								//y结点的秩大于等于x结点的秩
	{ 	t[x].parent=y;				//将y结点作为x的双亲结点
		if (t[x].rank==t[y].rank)		//x和y结点的秩相同
			t[y].rank++;				//y结点的秩增1
	}
}
struct Edge
{
	int u;		//边的起始顶点
	int v;		//边的终止顶点
	int w;		//边的权值
	bool operator<(const Edge &e) const
	{
		return w<e.w;			//用于按w递增排序
	}
};

void Kruskal(MGraph g)			//Kruskal算法
{
	int i,j,k,u1,v1,sn1,sn2;
	UFSTree t[MaxSize];
	Edge E[MaxSize];
	k=0;
	for (i=0;i<g.n;i++)			//由g下三角部分产生的边集E
		for (j=0;j<i;j++)
			if (g.edges[i][j]!=0 && g.edges[i][j]!=INF)
			{	E[k].u=i;E[k].v=j;E[k].w=g.edges[i][j];
				k++;
			}
	sort(E,E+k);				//按w递增排序
	MAKE_SET(t,g.n);			//初始化并查集树t
	k=1;						//k表示当前构造生成树的第几条边,初值为1
	j=0;						//E中边的下标,初值为0
	while (k<g.n)				//生成的边数小于n时循环
	{	u1=E[j].u;
		v1=E[j].v;				//取一条边的头尾顶点编号u1和v2
		sn1=FIND_SET(t,u1);
		sn2=FIND_SET(t,v1);		//分别得到两个顶点所属的集合编号
		if (sn1!=sn2)			//添加该边不会构成回路,将其作为最小生成树的一条边输出
		{	printf("  (%d,%d):%d\n",u1,v1,E[j].w);
			k++;				//生成边数增1
			UNION(t,u1,v1);		//将u1和v1两个顶点合并
		}
		j++;					//扫描下一条边
	}
}
void main()
{
	MGraph g;
	int A[][MAXV]={				//一个带权无向图
		{0,  6,  INF,INF,INF,1,  INF},
		{6,  0,  4,  INF,INF,INF,3},
		{INF,4,  0,  2,  INF,INF,INF},
		{INF,INF,2,  0,  6,  INF,5},
		{INF,INF,INF,6,  0,  8,  7},
		{1,  INF,INF,INF,8,  0,  INF},
		{INF,3,  INF,5,  7,  INF,0}};
	int n=7,e=9;
	CreateMat(g,A,n,e);		//创建图的邻接矩阵存储结构g
	printf("图的邻接矩阵:\n");
	DispMat(g);				//输出邻接矩阵g
	printf("Kruskal算法结果:\n");
	Kruskal(g);
}
