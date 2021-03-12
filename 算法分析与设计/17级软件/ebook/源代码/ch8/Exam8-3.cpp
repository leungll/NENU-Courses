#include <stdio.h>
#include <string.h>
#define max(x,y) ((x)>(y)?(x):(y))
#define MAXN  101
#define MAXV 1001
//问题表示
int N,C;
int P[MAXN];        //价格
int V[MAXN];        //评价分数
//求解结果表示
int dp[MAXV];		//dp
void solve()
{
	for (int i=1; i<=N; i++)
		for(int j=C; j>=P[i]; j--)
			dp[j]=max(dp[j],dp[j-P[i]]+V[i]);
}
int main()
{
	while (scanf("%d%d",&C,&N)!=EOF)
    {
        memset(dp,0,sizeof(dp));
        for(int i=1; i<=N;i++)
			scanf("%d%d",&P[i],&V[i]);
		solve();
		printf("%d\n",dp[C]);
    }
	return 0;
}

