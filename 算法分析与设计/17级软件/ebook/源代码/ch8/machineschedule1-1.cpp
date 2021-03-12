#include <stdio.h>
#include <string.h>
#define INF 0x3f3f3f3f						//最大整数∞
#define MAXN 51								//最多的作业数
#define MAXA MAXN*20
#define MAXB MAXN*20
#define max(x,y) ((x)>(y)?(x):(y))
#define min(x,y) ((x)<(y)?(x):(y))
//问题表示
int n=6;									//作业数
int a[]={2,5,7,10,5,2};
int b[]={3,8,4,11,3,4};
//求解结构表示
int maxA,maxB;
int ans=INF;
int dp[2][MAXA][MAXB];						//滚动数组
void solve()								//求解算法
{
	int k,A,B,m,c=0;
	for (A=0;A<=maxA;A++)
		for (B=0;B<=maxB;B++)
		{
			dp[1][A][B]=0;
			dp[0][A][B]=1;					//k=0一定有解
		}
	for(k=1;k<=n;k++)
	{
		c=1-c;
		memset(dp[c],0,sizeof(dp[c]));		//初始化dp[c]为0
		for(A=0;A<=maxA;A++)
			for(int B=0;B<=maxB;B++)
			{
				if (A-a[k-1]>=0)			//在机器A上运行
					dp[c][A][B]=dp[1-c][A-a[k-1]][B];
				if (B-b[k-1]>=0)			//在机器B上运行
					dp[c][A][B]=(dp[c][A][B]
						|| dp[1-c][A][B-b[k-1]]);
			}
	}
	for(A=0;A<=maxA;A++)
		for(int B=0;B<=maxB;B++)
			if (dp[c][A][B])
				{
					m=max(A,B);
					if (m<ans)
						ans=m;
				}
} 
int main()
{
	int i;
	maxA=0; maxB=0;
	for (i=0;i<n;i++)
	{ 
		maxA+=a[i];
		maxB+=b[i];
	}
	solve();
	printf("%d\n",ans);
	return 0;
}
