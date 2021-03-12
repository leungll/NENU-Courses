#include <stdio.h>
#define MAX 100
#define max(x,y) ((x)>(y)?(x):(y))
//问题表示
int a[]={2,1,5,3,6,4,8,9,7};
int n=sizeof(a)/sizeof(a[0]);
//求解结果表示
int ans=0;
int dp[MAX];
void solve(int a[],int n)
{
	int i,j;
	for(i=0;i<n;i++)
	{
		dp[i]=1;
		for(j=0;j<i;j++)
		{
			if (a[i]>a[j])
				dp[i]=max(dp[i],dp[j]+1);
		}
	}
	ans=dp[0];
	for(i=1;i<n;i++)
		ans=max(ans,dp[i]);
}
void main()
{
	solve(a,n);
	for (int i=0;i<n;i++)
		printf("dp[%d]=%d\n",i,dp[i]);
	printf("求解结果\n");
	printf("   最长递增子序列的长度: %d\n",ans);
}
