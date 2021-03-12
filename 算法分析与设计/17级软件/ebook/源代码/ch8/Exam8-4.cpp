#include <stdio.h>
#define MAX 51
//问题表示
int n;
//求解结果表示
int dp[3];
int solve1()			//滚动数组解法
{
	dp[0]=1;
	dp[1]=2;
	for (int i=2; i<n; i++)
		dp[i%3]=dp[(i-1)%3]+dp[(i-2)%3];
	return dp[(n-1)%3];
}
/*
int fun(int n)			//递归解法
{
	if (n==1)
		return 1;
	else if (n==2)
		return 2;
	else
		return fun(n-1)+fun(n-2);
}
int solve()				//常规动态规划解法
{
	dp[0]=1;
	dp[1]=2;
	for (int i=2;i<n;i++)
		dp[i]=dp[i-1]+dp[i-2];
	return dp[n-1];
}
*/
void main()
{
	n=10;
	//printf("%d\n",solve());
	printf("%d\n",solve1());	//输出:89
	//printf("%d\n",fun(n));
}
