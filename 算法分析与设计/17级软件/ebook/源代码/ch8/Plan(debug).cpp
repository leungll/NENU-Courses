#include <stdio.h>
#define MAXM 10				//最多商店数
#define MAXN 10				//最多投入的人数
//问题表示
int m=3,n=5;				//商店数为m,总人数为n
int v[MAXM][MAXN]={{0,0,0,0,0,0},{0,3,7,9,12,13},
	{0,5,10,11,11,11},{0,4,6,11,12,12}}; //不计v[0]行
//求解结果表示
int dp[MAXM][MAXN];
int pnum[MAXM][MAXN];

void Plan()							//求最优方案dp
{
	int maxf,maxj;
	for (int j=0;j<=n;j++)			//置边界条件
		dp[m+1][j]=0;
	for (int i=m;i>=1;i--)			//从商店3到1进行处理
	{
		for (int s=1;s<=n;s++)		//将各人数分配给第k个商店
		{
			maxf=0;
			maxj=0;
			for (j=0;j<=s;j++)		//商店i～商店m共分配s个人
			{
				printf("s=%d,j=%d\n",s,j);
				printf("  v[%d][%d]+dp[%d][%d]=%d\n",i,j,i+1,s-j,v[i][j]+dp[i+1][s-j]);
				if ((v[i][j]+dp[i+1][s-j])>=maxf)
				{
					maxf=v[i][j]+dp[i+1][s-j];
					maxj=j;
				}
			}
			dp[i][s]=maxf;			//dp[i][s]表示考虑商店i..m分配总人数s的最优赢利
			pnum[i][s]=maxj;		//pnum[i][s]表示dp[i][s]对应商店i的分配人数

			printf("dp[%d][%d]=v[%d][%d]+",i,s,i,maxj);
			printf("dp[%d][%d]=%d+%d=%d  ",i+1,s-maxj,v[i][maxj],dp[i+1][s-maxj],dp[i][s]);
			printf("pnum[%d][%d]=%d\n",i,s,pnum[i][s]);
		}
	}
}
void dispPlan()					//输出最优分配方案
{
	int k,r,s;
	s=pnum[1][n];
	printf("s=%d\n",s);
	r=n-s;						//r为余下的人数
	printf("最优资源分配方案如下:\n");

	for (k=1;k<=m;k++)
	{
		printf("  %c商店分配%d人\n",'A'+k-1,s);
		s=pnum[k+1][r];			//求下一个阶段分配的人数
		r=r-s;					//余下人数递减
	}
	printf("该分配方案的总赢利为%d万元\n",dp[1][n]);
}
void main()
{
	Plan();
	printf("求解结果\n");

	printf("dp:\n");
	for (int i=1;i<=m;i++)
	{
		for (int j=1;j<=n;j++)
			printf("%2d ",dp[i][j]);
		printf("\n");
	}
	printf("pnum:\n");
	for (i=1;i<=m;i++)
	{
		for (int j=1;j<=n;j++)
			printf("%2d ",pnum[i][j]);
		printf("\n");
	}
	dispPlan();
}
