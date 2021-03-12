//求解最大连续子序列和问题的算法
#include <stdio.h>
#define max(x,y) ((x)>(y)?(x):(y))
#define MAXN 20
//问题表示
int n=6;
int a[]={0,-2,11,-4,13,-5,-2};	//a数组不用下标为0的元素
//求解结果表示
int dp[MAXN];
void maxSubSum()				//求dp数组
{
	dp[0]=0;
	for (int j=1;j<=n;j++)
		dp[j]=max(dp[j-1]+a[j],a[j]);
}
void dispmaxSum()					//输出结果
{
	int maxj=1;
	for (int j=2;j<=n;j++)			//求dp中最大元素dp[maxj]
		if (dp[j]>dp[maxj]) maxj=j;

		
	for (int k=maxj;k>=1;k--)		//找前一个值小于等于0者
		if (dp[k]<=0) break;
	printf("    最大连续子序列和: %d\n",dp[maxj]);
	printf("    所选子序列: ");
	for (int i=k+1;i<=maxj;i++)
		printf("%d ",a[i]);
	printf("\n");
}
void main()
{
	maxSubSum();
	printf("求解结果\n");
	dispmaxSum();
}
