//例5.5的算法
#include <stdio.h>
void swap(int &x,int &y)			//交换x、y
{	int tmp=x;
	x=y; y=tmp;
}
void dispasolution(int a[],int n)	//输出一个解
{
	printf("  (");
	for (int i=0;i<n-1;i++)
		printf("%d,",a[i]);
	printf("%d)",a[n-1]);
}
void dfs(int a[],int n,int i)		//求a[0..n-1]的全排列
{
	if (i>=n)							//递归出口
		dispasolution(a,n);
	else
	{	for (int j=i;j<n;j++)
		{	swap(a[i],a[j]);			//交换a[i]与a[j]
			dfs(a,n,i+1);
			swap(a[i],a[j]);			//交换a[i]与a[j]：恢复
		}
	}
}
void main()
{
	int a[]={1,2,3,4};
	int n=sizeof(a)/sizeof(a[0]);
	printf("a的全排列\n");
	dfs(a,n,0);
	printf("\n");
}
