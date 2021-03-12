//贪心法求解TSP问题
#include "Graph.cpp"
#pragma warning( disable:4786) 
#include <vector>
#include <queue>
using namespace std;
void TSP(MGraph g)					//用贪心法求解起点为0的TSP问题
{
	int i,j,k,minj,minedge;
	bool find;
	vector<int> minpath;			//存放路径
	int minpathlen=0;				//存放路径长度
	minpath.push_back(0);			//起点0加入路径
	i=0;							//当前顶点为起点0
	while (minpath.size()!=g.n)		//尚未找所有顶点时循环
	{
		find=false;
		minedge=INF;
		for (j=1;j<g.n;j++)			//从顶点1到n-1循环找距离顶点i最近的顶点minj
		{
			if (g.edges[i][j]!=0 && g.edges[j][j]!=INF)	//当前顶点i到顶点j有边
			{
				k=0;
				while (k<minpath.size() && j!=minpath[k])	//判断路径中是否有顶点j
					k++;
				if (k=minpath.size())		//顶点j不在路径中
				{
					if (g.edges[i][j]<minedge)
					{
						minedge=g.edges[i][j];
						minj=j;
					}
				}

			}
		}
		minpath.push_back(minj);
		minpathlen+=minedge;
		i=minj;
	}
	minpath.push_back(0);			//路径中加入起点
	minpathlen+=g.edges[minj][0];
	printf("路径长度=%d, ",minpathlen);
	printf("路径:");
	printf("%d",minpath[0]);
	for (i=1;i<minpath.size();i++)
		printf("→%d",minpath[i]);
	printf("\n");
}
void main()
{
	MGraph g;
	int A[][MAXV]={						//一个带权有向图
		{0,8,5,36},
		{6,0,8,5},
		{8,9,0,5},
		{7,7,8,0}};
	int n=4,e=12;
	CreateMat(g,A,n,e);					//创建图的邻接矩阵存储结构g
	printf("邻接矩阵:\n"); DispMat(g);	//输出邻接矩阵g
	printf("起点为0的解:\n");TSP(g);
}
