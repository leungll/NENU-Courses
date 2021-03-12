//回溯法求解TSP问题
#include "Graph.cpp"
#pragma warning( disable:4786)
#include <stdio.h>
#include <vector>
#include <set>
using namespace std;
#define min(x,y) ((x)<(y)?(x):(y))
typedef set< int > SET;						//采用set<int>表示顶点集合
//问题表示
int s;										//指定起点
MGraph g;									//图的邻接矩阵
//求解过程表示
int Count=1;								//路径条数累计
vector<int> minpath;						//保存最短路径
int minpathlen=INF;							//保存最短路径长度
void dispasolution(vector<int> path,int pathlen)	//输出一个解
{
	printf("    第%d条路径: ",Count++);
	for (int i=0;i<path.size();i++)
		printf("%2d",path[i]);
	printf(", 路径长度: %d\n",pathlen);
}
void TSP(SET V,int i,vector<int> path,int pathlen)	//回溯法求从顶点s出发的TSP路径和长度
{
	int prev;
	if (path.size()>0)						//path不为空
		prev=path.back();					//prev为路径上的最后一个顶点
	path.push_back(i);						//添加当前顶点i
	pathlen+=g.edges[prev][i];				//累计路径长度
	if (V.size()==0)							//找到一个叶子结点
	{
		if (g.edges[i][s]!=0 && g.edges[i][s]!=INF)	//该顶点i到起点s有边
		{	
			path.push_back(0);					//路径中加入起点0
			pathlen+=g.edges[i][s];				//累计路径长度
			dispasolution(path,pathlen);		//输出一条路径
			if (pathlen<minpathlen)				//比较求最短路径
			{
				minpathlen=pathlen;
				minpath=path;
			}
		}
	}
	else										//对于非叶子结点
	{
		SET::iterator it;
		for (it=V.begin();it!=V.end();it++)
		{
			SET tmpV=V;
			int j=*it;							//选择顶点j
			tmpV.erase(j);						//从V中删除顶点j得到tmpV
			if (pathlen<minpathlen)				//剪枝
				TSP(tmpV,j,path,pathlen);		//递归调用
		}
	}
}
void main()
{
	int A[][MAXV]={						//一个带权有向图
		{0,8,5,36}, {6,0,8,5}, {8,9,0,5}, {7,7,8,0}};
	int n=4,e=12;
	CreateMat(g,A,n,e);		//创建图的邻接矩阵存储结构g
	s=0;					//起始顶点为0
	vector<int> path;
	int pathlen=0;
	SET V;
	for (int i=1;i<g.n;i++)			//插入1,2,3顶
		V.insert(i);
	printf("求解结果\n");
	TSP(V,0,path,pathlen);
	printf("    最短路径: ");		//输出最短路径
	for (int j=0;j<minpath.size();j++)
		printf("%3d",minpath[j]);
	printf("\n    路径长度:   %d\n",minpathlen);
}
