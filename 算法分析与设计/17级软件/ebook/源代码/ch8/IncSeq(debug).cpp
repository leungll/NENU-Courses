#include <stdio.h>
#define MAX 100
#define max(x,y) ((x)>(y)?(x):(y))
//问题表示
int a[]={2,1,5,3,6,4,8,9,7};
int n=sizeof(a)/sizeof(a[0]);
//求解结果表示
int ans=0;
int dp[MAX];
int Count=1;
void solve(int a[],int n)
{
	int i,j;
	for(i=0;i<n;i++)
	{
		dp[i]=1;
		//printf("(%d) dp[%d]=1\n",Count++,i);
		for(j=0;j<i;j++)
		{
			if (a[i]>a[j])
			{
				int tmp=dp[i];
				dp[i]=max(dp[i],dp[j]+1);
				printf("（%d）a[%d]（%d） > a[%d](%d): ",Count++,i,a[i],j,a[j]);
				printf("dp[%d]=max{dp[%d]（%d），dp[%d]（%d）+1}=%d\n",i,i,tmp,j,dp[j],dp[i]);
			}
		}
	}
	ans=dp[0];
	for(i=1;i<n;i++)
		ans=max(ans,dp[i]);
}
void main()
{
	solve(a,n);
	printf("求解结果\n");
	printf("   最长递增子序列的长度: %d\n",ans);
}
