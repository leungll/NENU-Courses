//动态规划求解TSP问题
#include "Graph.cpp"
#pragma warning(disable:4786)
#include <stdio.h>
#include <vector>
#include <set>
using namespace std;
#define min(x,y) ((x)<(y)?(x):(y))
typedef set< int > SET;						//采用set<int>表示顶点集合
//问题表示
int s=0;									//指定起点为0
MGraph g;									//图的邻接矩阵
void dispset(SET V)
{
	SET::iterator it;
	printf("{");
	for (it=V.begin();it!=V.end();++it)
		printf("%d ",*it);
	printf("}");
}

int f(SET V,int i)							//求TSP所有解的路径长度
{
	int minpathlen=INF;						//最短路径长度
	if (V.size()==0)						//当V为空时
	{
		printf("计算f({ },%d)\n",i);
		printf("求出f({ },%d),递归出口pathlen=%d\n",i,g.edges[0][i]);
		return g.edges[0][i];
	}
	else									//当V为不空时
	{
		SET::iterator it;
		printf("计算f("); dispset(V); printf(",%d)\n",i);
		for (it=V.begin();it!=V.end();++it)	//扫描集合V中的顶点j
		{
			SET tmpV=V;
			int j=*it;
			tmpV.erase(j);					//tmpV=V-{j}
			int pathlen1=f(tmpV,j);
			int pathlen=pathlen1+g.edges[j][i];
			printf("    f("); dispset(tmpV); printf(",%d )",j); printf(",pathlen1=%d\n",pathlen1);
			minpathlen=min(minpathlen,pathlen);
		}
		printf("求出f("); dispset(V); printf(",%d),minpathlen=%d\n",i,minpathlen);
		return minpathlen;
	}
}
void main()
{
	int A[][MAXV]={						//一个带权有向图
		{0,8,5,36},{6,0,8,5},{8,9,0,5},{7,7,8,0}};
	int n=4,e=12;
	CreateMat(g,A,n,e);					//创建图的邻接矩阵g
	SET V;
	for (int i=1;i<g.n;i++)				//插入1,2,3顶点
		V.insert(i);
	printf("TSP路径长度=%d\n",f(V,s));	//输出23
}
