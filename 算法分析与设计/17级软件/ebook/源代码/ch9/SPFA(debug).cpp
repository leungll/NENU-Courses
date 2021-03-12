//SPFA算法－求单源最短路径
#include "Graph.cpp"		//包含图的基本运算算法
#include <queue>
#include <vector>
using namespace std;
//问题表示
int s;
ALGraph *G;
//求解结果表示
int dist[MAXV];
int path[MAXV];
int visited[MAXV];

void Disppath()					//输出从顶点s出发的所有最短路径
{
	vector<int> apath;			//存放逆一条路径
	for (int i=0;i<G->n;i++)
	{
		if (i==s) continue;
		if (path[i]==-1)
			printf("  从顶点%d到%d的没有路径\n",s,i);
		else
		{
			apath.clear();
			int j=i;
			apath.push_back(j);
			while (j!=s && j!=-1)
			{
				j=path[j];
				apath.push_back(j);
			}
			printf("  从顶点%d到%d的最短路径长度: %2d, 路径: ",s,i,dist[i]);
			for (int k=apath.size()-1;k>=0;k--)
				printf("%d ",apath[k]);
			printf("\n");
		}
	}
}
void disp(queue<int> qu)
{
	printf("qu\t");
	while (!qu.empty())
	{
		printf("%4d",qu.front());
		qu.pop();
	}
	printf("\n");
	printf("i\t");
	for (int i=0;i<G->n;i++)
		printf("%4d",i);
	printf("\nvisited:");
	for (int k=0;k<G->n;k++)
		printf("%4d",visited[k]);
	printf("\ndist\t");
	for (int j=0;j<G->n;j++)
		if (dist[j]==INF)
			printf("%4s","∞");
		else
			printf("%4d",dist[j]);
	printf("\n");
}

void SPFA()				//求单源点s到其他各顶点的最短距离
{
	ArcNode *p;
	int v,w;
	queue<int> qu,qu1;					//定义一个队列qu
	for (int i=0;i<G->n;i++)		//初始化顶点s到i的距离
	{
		dist[i]=INF;
		visited[i]=0;
		path[i]=-1;
	}
    dist[s]=0;						//将源点的dist设为0
    visited[s]=1;					//设置源点s的访问标记
	qu.push(s);						//源点s进队
	qu1=qu;
	disp(qu1);
    while (!qu.empty())						//队不空循环
	{
		v=qu.front(); qu.pop();				//出队顶点v
		visited[v]=0;						//释放对v的标记，可以重新进队
		p=G->adjlist[v].firstarc;
		while (p!=NULL)						//处理顶点v的每个相邻点w
		{
			w=p->adjvex;
			if (dist[w]>dist[v]+p->weight)	//如果不满足三角形性质
			{
				dist[w]=dist[v]+p->weight;   //松弛dist[i]
				path[w]=v;
			}
			if (visited[w]==0)			//顶点w没有访问
			{
				qu.push(w);				//将顶点w进队
				visited[w]=1;
			}
			p=p->nextarc;
		}
		printf("出队%d,相邻点进队\n",v);
		qu1=qu;
		disp(qu1);
    }
}
void main()
{
	int n=4,e=4;
	int A[][MAXV]={
		{0,2,4,INF},
		{INF,INF,1,INF},
		{INF,INF,0,3},
		{INF,INF,INF,0}};
	CreateAdj(G,A,n,e);		//创建图的邻接表G
	printf("邻接表G\n"); DispAdj(G);
	s=0;
	SPFA();
	printf("求解结果\n");
	Disppath();
}
