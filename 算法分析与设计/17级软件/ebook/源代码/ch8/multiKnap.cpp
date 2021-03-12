//求解完全背包问题的算法
#include <stdio.h>
#include <string.h>
#define MAXN 20				//最多物品数
#define MAXW 100			//最大限制重量
#define max(x,y) ((x)>(y)?(x):(y))
//问题表示
int n,W;
int w[MAXN],v[MAXN];
//求解结果表示
int dp[MAXN+1][MAXW+1],fk[MAXN+1][MAXW+1];
int solve()					//求解多重背包问题
{
	int i,j,k;
	for (i=1;i<=n;i++)
	{
		for (j=0;j<=W;j++)
			for (k=0;k*w[i]<=j;k++)
			{
				if (dp[i][j]<dp[i-1][j-k*w[i]]+k*v[i])
				{
					dp[i][j]=dp[i-1][j-k*w[i]]+k*v[i];
					fk[i][j]=k;		//物品i取k件
				}									
			}
	}
	return dp[n][W];
}
void Traceback()				//回推求最优解
{
	int i=n,j=W;
	while (i>=1)
	{
		printf("物品%d共%d件 ",i,fk[i][j]);
		j-=fk[i][j]*w[i];		//剩余重量
		i--;
	}
	printf("\n");
}
int solve1()						//动态规划法求完全背包问题
{	int i,k,j;
	for (i=1;i<=n;i++)
		for (j=0;j<=W;j++)
			if (j<w[i])
				dp[i][j]=dp[i-1][j];
			else
				dp[i][j]=max(dp[i-1][j],dp[i][j-w[i]]+v[i]);
	return dp[n][W];		//返回总价值
}
void main()
{
	w[1]=3; w[2]=4; w[3]=2;
	v[1]=4; v[2]=5; v[3]=3;
	n=3; W=7;
	memset(dp,0,sizeof(dp));
	memset(fk,0,sizeof(fk));
	printf("最优解:\n");
	printf("  总价值=%d\n",solve());
	printf("  方案: ");Traceback();
	printf("解法2\n");
	printf("  总价值=%d\n",solve1());
}
