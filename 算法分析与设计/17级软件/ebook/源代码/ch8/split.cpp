#include <stdio.h>
#define MAXN 500
int dp[MAXN][MAXN];			//动态规划数组
void Split(int n,int k)		//求解算法
{
	for (int i=1;i<=n;i++)
		for(int j=1;j<=k;j++)
		{
			if (i==1 || j==1)
				dp[i][j]=1;
			else if (i<j)
				dp[i][j]=dp[i][i];
			else if (i==j)
				dp[i][j]=dp[i][j-1]+1;
			else
				dp[i][j]=dp[i][j-1]+dp[i-j][j];
		}
}
void main()
{
	int n=5,k=5;
	Split(n,k);
	printf("(%d,%d)=%d\n",n,k,dp[n][k]);	//输出:7
}
