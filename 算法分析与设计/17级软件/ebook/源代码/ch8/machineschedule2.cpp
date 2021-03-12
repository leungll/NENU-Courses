#include <stdio.h>
#include <string.h>
#define INF 0x3f3f3f3f						//最大整数∞
#define MAXN 51								//最多的作业数
#define MAXA MAXN*20
#define max(x,y) ((x)>(y)?(x):(y))
#define min(x,y) ((x)<(y)?(x):(y))
//问题表示
int n=6;									//作业数
int a[]={2,5,7,10,5,2};
int b[]={3,8,4,11,3,4};
//求解结构表示
int maxA;
int ans=INF;
int dp[MAXN][MAXA];	
void solve()								//求解算法
{
	int k,A,m;
	memset(dp,0,sizeof(dp));				//初始化为0
	for (k=1;k<=n;k++)
	{
		for (A=0;A<=maxA;A++)
		{
			if (A<a[k-1])					//这个时间只能在机器B上运行
				dp[k][A]=dp[k-1][A]+b[k-1];
			else							//否则取机器A或者机器B上运行的最少时间
				dp[k][A]=min(dp[k-1][A-a[k-1]],dp[k-1][A]+b[k-1]); 
		}
	}
	for (A=0;A<=maxA;A++)
	{
		m=max(dp[n][A],A);					//机器A与B所花时间较大值
		ans=min(ans,m);
	}
} 
int main()
{
	int i;
	maxA=0;
	for (i=0;i<n;i++)
		maxA+=a[i];
	solve();
	printf("%d\n",ans);
	return 0;
}
