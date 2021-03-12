//例5.3的算法2
#include <stdio.h>
#include <vector>
using namespace std;
void dispasolution(vector<int> path)		//输出一个解
{
	printf("   {");
	for (int i=0;i<path.size();i++)
			printf("%d",path[i]);
	printf("}");
}
void dfs(int a[],int n,int i,vector<int> path)	//回溯算法求子集path
{
	if (i>=n)
		dispasolution(path);
	else
	{
		dfs(a,n,i+1,path);			//不选择a[i]
		path.push_back(a[i]);
		dfs(a,n,i+1,path);			//选择a[i]
	}
}
void main()
{
	int a[]={1,2,3};				//s[0..n-1]为给定的字符串,设置为全局变量
	int n=sizeof(a)/sizeof(a[0]);
	vector<int> path;
	printf("求解结果\n");
	dfs(a,n,0,path);
	printf("\n");
}
