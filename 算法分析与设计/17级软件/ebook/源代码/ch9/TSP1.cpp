//蛮力法求解TSP问题
#include "Graph.cpp"
#include <stdio.h>
#include <vector>
using namespace std;
//问题表示
int s=0;							//指定起点为0
MGraph g;							//图的邻接矩阵
//求解过程表示
int Count=1;						//路径条数累计
vector<vector<int> > ps;			//存放全排列
void Insert(vector<int> s,int i,vector<vector<int> > &ps1)
//在每个集合元素中间插入i得到ps1
{	vector<int> s1;
	vector<int>::iterator it;
	for (int j=0;j<i;j++)						//在s(含i-1个整数)的每个位置插入i
	{	s1=s;
		it=s1.begin()+j;						//求出插入位置
		s1.insert(it,i);						//插入整数i
		ps1.push_back(s1);						//添加到ps1中
	}
}
void Perm(int n)								//求1～n的所有全排列
{	vector<vector<int> > ps1;					//临时存放子排列
	vector<vector<int> >::iterator it;			//全排列迭代器
	vector<int> s,s1;
	s.push_back(1);
	ps.push_back(s);							//添加{1}集合元素
	for (int i=2;i<=n;i++)						//循环添加1～n
	{	ps1.clear();							//ps1存放插入i的结果
		for (it=ps.begin();it!=ps.end();++it)
			Insert(*it,i,ps1);					//在每个集合元素中间插入i得到ps1
		ps=ps1;
	}
}
void TSP(MGraph g,int s)						//用蛮力法求解TSP问题
{
	vector<int> minpath;						//保存最短路径
	int minpathlen=INF;							//保存最短路径长度
	Perm(g.n-1);								//生成1到n-1的全排列ps
	vector<vector<int> >::reverse_iterator it;	//全排列的反向迭代器
	vector<int> apath;
	int pathlen;
	printf("起点为%d的全部路径\n",s);
	for (it=ps.rbegin();it!=ps.rend();++it)		//遍历ps中的每个排列
	{
		pathlen=0;
		int initv=s;
		apath=(*it);
		for (int i=0;i<(*it).size();i++)		//计算一个排列作为路径的长度
		{
			pathlen+=g.edges[initv][(*it)[i]];
			initv=(*it)[i];
		}
		pathlen+=g.edges[initv][s];
		if (pathlen<INF)						//存在路径时
		{
			printf("   路径%d:",Count++);
			printf("0→");
			for (i=0;i<apath.size();i++)		//输出一条路径
				printf("%d→",apath[i]);
			printf("%d   路径长度: %d\n",0,pathlen);
			if (pathlen<minpathlen)				//比较求最短路径
			{
				minpathlen=pathlen;
				minpath=apath;
			}
		}
	}
	printf("起点为%d的最短路径\n",s);			//输出最短路径	
	printf("   最短路径长度: %d\n",minpathlen); 
	printf("   最短路径: ");
	printf("0→");
	for (int j=0;j<minpath.size();j++)
		printf("%d→",minpath[j]);
	printf("%d\n",0);
}
void main()
{
	int A[][MAXV]={						//一个带权有向图
		{0,8,5,36},	{6,0,8,5},	{8,9,0,5},	{7,7,8,0}};
	int n=4,e=12;
	CreateMat(g,A,n,e);					//创建图的邻接矩阵g
	TSP(g,s);
}
