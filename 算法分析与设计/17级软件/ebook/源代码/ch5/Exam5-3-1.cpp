//例5.3的算法1
#include <stdio.h>
#include <string.h>
#define MAXN 100
void dispasolution(int a[],int n,int x[])	//输出一个解
{
	printf("   {");
	for (int i=0;i<n;i++)
		if (x[i]==1)
			printf("%d",a[i]);
	printf("}");
}
void dfs(int a[],int n,int i,int x[])	//回溯算法
{
	if (i>=n)
		dispasolution(a,n,x);
	else
	{
		x[i]=0;
		dfs(a,n,i+1,x);			//不选择a[i]
		x[i]=1;
		dfs(a,n,i+1,x);			//选择a[i]
	}
}
void main()
{
	int a[]={1,2,3};				//s[0..n-1]为给定的字符串,设置为全局变量
	int n=sizeof(a)/sizeof(a[0]);
	int x[MAXN];					//解向量
	memset(x,0,sizeof(x));			//解向量初始化
	printf("求解结果\n");
	dfs(a,n,0,x);
	printf("\n");
}
