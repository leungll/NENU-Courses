#include <stdio.h>
#include <string.h>
#include <queue>
#include <vector>
using namespace std;
#define INF 0x3f3f3f3f			//表示∞
#define MAXN 51
//问题表示
int n;							//图顶点个数
int a[MAXN][MAXN];				//图的邻接矩阵
int v;							//源点
//求解结果表示
int dist[MAXN];					//dist[i]源点到顶点i的最短路径长度
int prev[MAXN];					//prev[i]表示源点到顶点j的最短路径长度中顶点j的前驱顶点
struct NodeType					//队列结点类型
{
    int vno;					//顶点编号
	int length;					//路径长度
    bool operator<(const NodeType & node) const
    {
        return length>node.length;	//length越小越优先出队
    }
};
void bfs(int v)						//求解算法
{
	NodeType e,e1;
    priority_queue<NodeType> pqu;	//定义优先队列
	e.vno=v;						//建立源点结点e
	e.length=0;
	pqu.push(e);					//源点结点e进队
    dist[v]=0;
    while(!pqu.empty())				//队列不空循环
    {
		e=pqu.top(); pqu.pop();		//出队列结点e
        for (int j=0; j<n; j++)
		{
            if(a[e.vno][j]<INF && e.length+a[e.vno][j]<dist[j])
            {	//剪枝：e.vno到顶点j有边并且路径长度更短
                dist[j]=e.length+a[e.vno][j];
				prev[j]=e.vno;
				e1.vno=j;			//建立相邻顶点j的结点e1
				e1.length=dist[j];
				pqu.push(e1);		//结点e1进队
            }
		}
    }
}
void addEdge(int i,int j,int w)		//图中添加一条边
{
	a[i][j]=w;
}
void dispapath(int v,int i)			//输出v到i的最短路径
{
	vector<int> path;
	if (v==i) return;
	if (dist[i]==INF)
		printf("	源点%d到顶点%d没有路径\n",v,i);
	else
	{
		int k=prev[i];
		path.push_back(i);		//添加目标顶点
		while (k!=v)			//添加中间顶点
		{
			path.push_back(k);
			k=prev[k];
		}
		path.push_back(v);		//添加源点
		printf("	源点%d到顶点%d的最短路径长度: %d, 路径: ",v,i,dist[i]);
		for (int j=path.size()-1;j>=0;j--)	//反向输出构成正向路径
			printf("%d ",path[j]);
		printf("\n");
	}
}
void dispallpath(int v)			//输出源点v出发的所有最短路径
{
	for (int i=0;i<n;i++)
		dispapath(v,i);
}
void main()
{
	memset(dist,INF,sizeof(dist));	//初始化为∞
	memset(a,INF,sizeof(a));		//初始化为∞
	n=6;							//有向图的顶点个数
	for (int i=0;i<n;i++)			//对角线设置为0
		a[i][i]=0;
	addEdge(0,2,10);				//添加8条边
	addEdge(0,4,30);
	addEdge(0,5,100);
	addEdge(1,2,4);
	addEdge(2,3,50);
	addEdge(3,5,10);
	addEdge(4,3,20);
	addEdge(4,5,60);
	v=0;
	bfs(v);
	printf("求解结果\n");
	dispallpath(v);
}
