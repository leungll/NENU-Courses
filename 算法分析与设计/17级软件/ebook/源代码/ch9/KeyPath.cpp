//求多段图的关键路径的算法
#include <stdio.h>
#include <string.h>
const int MAXV=20;				//图中最多的顶点数
const int MAXL=10;				//顶点信息的最大字符个数
const int INF=32767;			//用INF表示∞
//采用图的邻接矩阵类型MGraph存放多段图
typedef struct
{	int no;					//顶点编号
	char data[MAXL];			//顶点其他信息
}  VertexType;				//顶点类型
typedef struct 
{	int edges[MAXV][MAXV];		//邻接矩阵的边数组，假设权值为T类型
	int n,e;					//顶点数，边数
	VertexType vexs[MAXV];		//存放顶点信息
} MGraph;						//图邻接矩阵类型
void CreateMGraph(MGraph &g,int a[MAXV][MAXV],char b[MAXV][MAXL],int n)
//通过边数组a、顶点信息数组b和顶点数n来建立图的邻接矩阵g
{	int i,j;
	g.n=n;					//置顶点数
	for (i=0;i<g.n;i++)
	{	strcpy(g.vexs[i].data,b[i]); 
		for (j=0;j<g.n;j++)
			g.edges[i][j]=a[i][j];
	}
}
void DispMGraph(MGraph g)		//输出图的邻接矩阵
{	int i,j;
	for (i=0;i<g.n;i++)
	{	for (j=0;j<g.n;j++)
			if (g.edges[i][j]==INF)
				printf("%4s","∞");
			else
				printf("%4d",g.edges[i][j]);
		printf("\n");
	}
}
void DispKeyPath(MGraph g,int path[])	//输出一条关键路径
{	int i,apath[MAXV],d;			//存放关键路径(逆向)及其顶点个数
	printf("关键路径:");
	i=g.n-1; d=0;
	while (i!=-1)
	{	apath[d]=i; d++;
		i=path[i];
	}
	for (i=d-1;i>0;i--)			//正向输出关键路径
		printf("%s→",g.vexs[apath[i]].data);
	printf("%s\n",g.vexs[apath[i]].data);
}
int LongPath(MGraph g,int path[])	//求关键路径及其长度
{	int n=g.n,i,j,maxdis,maxj;
	int dist[MAXV];				//建立dist数组
	for (i=0;i<n;i++)				//初始化
	{	dist[i]=0;
		path[i]=-1;
	}
	for (i=n-1;i>0;i--)			//依次考虑顶点n-1、…、2、1
	{	printf("考虑顶点i=%d\n",i);
		maxdis=-1;
		for (j=0;j<n;j++)			//求顶点i的最大前驱顶点maxj
			if (g.edges[j][i]!=-1 && g.edges[j][i]!=INF) //存在j到i的边
			{	dist[j]=g.edges[j][i]+dist[i]; 
				printf("有边(%d,%d),长度为%d,",j,i,g.edges[j][i]);
				printf("求得dist[%d]=%d\n",j,dist[j]);
				if (maxdis<dist[j])
				{	maxdis=dist[j];
					maxj=j;
				}
			}
		dist[i]=maxdis;
		path[i]=maxj;
		printf("i=%d求解结果:dist[%d]=%d,path[%d]=%d\n",i,i,maxdis,i,maxj);
	}
	return dist[0];
}
void main()
{	int n=10,keyplength;
	int path[MAXV];
	MGraph g;
	int A[MAXV][MAXV]={		//图9.31的边数组
		{ -1,  6,  4,  5 ,INF,INF,INF,INF,INF,INF},
		{INF, -1, INF,INF, 1 ,INF,INF,INF,INF,INF},
		{INF,INF, -1 ,INF, 1 ,INF,INF,INF,INF,INF},
		{INF,INF,INF,-1 ,INF, 2,  INF,INF,INF,INF},
		{INF,INF,INF,INF, -1 , INF, 9 , 7,INF,INF},
		{INF,INF,INF,INF,INF, -1 ,INF,INF, 0,INF},
		{INF,INF,INF,INF,INF, INF,-1, INF,INF, 2},
		{INF,INF,INF,INF,INF,INF,INF, -1 ,INF, 4 },
		{INF,INF,INF,INF,INF,INF,INF,INF, -1 , 4 },
		{INF,INF,INF,INF,INF,INF,INF,INF,INF, -1 }};
	char B[MAXV][MAXL]={"A","B","C","D","E","D'","F","G","H","I"};//图9.31的顶点信息
	printf("建立图的邻接矩阵\n");
	CreateMGraph(g,A,B,n);;
	printf("图的邻接矩阵:\n"); DispMGraph(g);
	keyplength=LongPath(g,path);	//求关键路径及其长度
	printf("关键路径长度=%d\n",keyplength);
	DispKeyPath(g,path);			//输出一条关键路径
}
