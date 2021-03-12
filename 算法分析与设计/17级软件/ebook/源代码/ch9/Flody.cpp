//弗洛伊德算法－求多源最短路径
#include "Graph.cpp"
void disp(int A[][MAXV],int path[][MAXV],int n,int k)	//调试用
{
	int i,j;
	printf("A(%d)\t\t\t\t\t\tpath(%d)\n",k,k);
	for (i=0;i<n;i++)
	{
		for (j=0;j<n;j++)
			if (A[i][j]!=INF)
				printf("%4d",A[i][j]);
			else
				printf("%4s","∞");
		printf("\t");
		for (j=0;j<n;j++)
			printf("%4d",path[i][j]);
		printf("\n");
	}
}
void Dispath(MGraph g,int A[][MAXV],int path[][MAXV])
//输出所有的最短路径和长度
{	int i,j,k,s;
	int apath[MAXV],d;		//存放一条最短路径中间顶点(反向)及其顶点个数
	for (i=0;i<g.n;i++)
		for (j=0;j<g.n;j++)
		{	if (A[i][j]!=INF && i!=j)			//若顶点i和j之间存在路径
			{	printf("  从%d到%d的路径为:",i,j);
				k=path[i][j];
				d=0; apath[d]=j;				//路径上添加终点
				while (k!=-1 && k!=i)			//路径上添加中间点
				{	d++; apath[d]=k;
					k=path[i][k];
				}
				d++; apath[d]=i;				//路径上添加起点
				printf("%d",apath[d]);			//输出起点
				for (s=d-1;s>=0;s--)			//输出路径上的中间顶点
					printf(",%d",apath[s]);
				printf("\t路径长度为:%d\n",A[i][j]);
			}
		}
}
void Floyd(MGraph g)
{	int A[MAXV][MAXV],path[MAXV][MAXV];
	int i,j,k;
	for (i=0;i<g.n;i++)
		for (j=0;j<g.n;j++) 
		{	A[i][j]=g.edges[i][j];
			if (i!=j && g.edges[i][j]<INF)
				path[i][j]=i;	//顶点i到j有边时
			else
				path[i][j]=-1;	//顶点i到j没有边时
		}
	for (k=0;k<g.n;k++)
	{
		for (i=0;i<g.n;i++)
			for (j=0;j<g.n;j++)
				if (A[i][j]>A[i][k]+A[k][j])
				{	A[i][j]=A[i][k]+A[k][j];
					path[i][j]=path[k][j];	//修改最短路径
				}
		disp(A,path,g.n,k);			//输出调试信息
	}
	Dispath(g,A,path);				//输出最短路径
}
void main()
{
	int n=4,e=8;
	MGraph g;
	int A[4][MAXV]={
		{0,  5,INF,7},
		{INF,0,  4,2},
		{3,  3,  0,2},
		{INF,INF,1,0}};
	CreateMat(g,A,n,e);		//创建图的邻接矩阵存储结构g
	printf("图的邻接矩阵:\n");
	DispMat(g);				//输出邻接矩阵g
	printf("各顶点的最短路径:\n");
	Floyd(g);
	printf("\n");
}