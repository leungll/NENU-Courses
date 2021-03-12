//例4.8的算法
#include "Graph.cpp"	//包含图的基本运算算法
#include <queue>
#include <vector>
using namespace std;
void Findpath(int pre[],int v,vector<int> &path)	//用pre产生逆路径path
{
	int d=v;
	while (d!=-1)
	{
		path.push_back(d);
		d=pre[d];
	}
}
void ShortPath(ALGraph *G,int u,int v,vector<int> &path)
//求图G中从顶点u到顶点v的最短（逆）路径path
{
	ArcNode *p;
	int w;
	queue<int> qu;						//定义一个队列qu
	int pre[MAXV];						//表示前驱关系
	int visited[MAXV];					//定义存放顶点的访问标志的数组
	memset(visited,0,sizeof(visited));	//访问标志数组初始化
	qu.push(u);							//顶点u进队
	visited[u]=1;
	pre[u]=-1;
	while (!qu.empty())			//队不空时循环
	{
		w=qu.front(); qu.pop();	//出队顶点w
		if (w==v)				//找到v时输出路径之逆并退出
		{
			Findpath(pre,v,path);
			return;
		}
		p=G->adjlist[w].firstarc;	//找w的第一个邻接点
		while (p!=NULL)
		{
			if (visited[p->adjvex]==0)
			{
				visited[p->adjvex]=1;		//访问w的邻接点
				qu.push(p->adjvex);			//将w的邻接点进队
				pre[p->adjvex]=w;			//设置p->adjvex顶点的前驱为w
			}
			p=p->nextarc;			//找w的下一个邻接点
		}
	}
}
void Disppath(vector<int> path)		//正向输出路径path
{
	vector<int>::reverse_iterator it;
	for (it=path.rbegin();it!=path.rend();++it)
		printf("%d ",*it);
	printf("\n");
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
	int u=0,v=2;
	CreateAdj(G,A,n,e);		//创建图的邻接表存储结构G
	vector<int> path;
	printf("求解结果\n");
	for (int i=0;i<n;i++)
		for (int j=0;j<n;j++)
			if (i!=j)
			{
				path.clear();
				ShortPath(G,i,j,path);
				if (path.size()>0)
				{
					printf("  从顶点%d到%d的最短路径: ",i,j);
					Disppath(path);
				}
			}
	DestroyAdj(G);			//销毁邻接表G
}
