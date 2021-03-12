#include <stdio.h>
#include <string.h>
#define MAXN 20				//图最多的顶点个数
//问题表示
int n,k,m;
int a[MAXN][MAXN];
//求解结果表示
int count=0;				//全局变量，累计解个数
int x[MAXN];				//全局变量，x[i]表示顶点i的着色
bool Same(int i)			//判断顶点i是否与相邻顶点存在相同的着色
{
	for (int j=1;j<=n;j++)
		if (a[i][j]==1 && x[i]==x[j])
			return false;
	return true;
}
void dispasolution()			//输出一种着色方案
{
	printf("第%d个着色方案: ",count);
	for (int j=1;j<=n;j++)
		printf("%d ",x[j]);
	printf("\n");
}
void dfs(int i)					//求解图的m着色问题
{
	if (i>n)					//达到叶子结点
	{
		count++;				//着色方案数增1
		dispasolution();
	}
	else
	{
		for (int j=1;j<=m;j++)	//试探每一种着色
		{
			x[i]=j;
			if (Same(i))		//可以着色j，进入下一个顶点着色
				dfs(i+1);
			x[i]=0;				//回溯
		}
	}
}
int main()
{
	memset(a,0,sizeof(a));		//a初始化
	memset(x,0,sizeof(x));		//x初始化
	int x,y;
	scanf("%d%d%d",&n,&k,&m);	//输入n,k,m
	for (int j=1;j<=k;j++)
	{
		scanf("%d%d",&x,&y);	//输入一条边的两个顶点
		a[x][y]=1;				//无向图的边对称
		a[y][x]=1;
	}
	dfs(1);						//从顶点1开始搜索
	if (count>0)				//输出结果
		printf("%d\n",count);
	else
		printf("-1\n");
	return 0;
}


