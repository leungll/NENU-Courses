#include <stdio.h>
#define MAX 51
int dp[MAX];
int count=1;
int Fib1(int n)
{
	dp[1]=dp[2]=1;
	printf("(%d)计算出Fib1(1)=1\n",count++);
	printf("(%d)计算出Fib1(2)=1\n",count++);
	for (int i=3;i<=n;i++)
	{
		dp[i]=dp[i-1]+dp[i-2];
		printf("(%d)计算出Fib1(%d)=%d\n",count++,i,dp[i]);
	}
	return dp[n];
}
		
void main()
{
	Fib1(5);
}