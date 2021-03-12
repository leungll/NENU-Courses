#include <stdio.h>
#include <string>
using namespace std;
#define MAXM 51
#define MAXN 51
#define max(x,y) ((x)>(y)?(x):(y))
//问题表示
string s="abcde";
string t="abgde";
//求解结果表示
int dp[MAXM][MAXN];
int Maxlength(string s,string t)	//求s和t的最长公共连续子串的长度
{	int ans=0;
	int i,j;
	int n=s.length();
	int m=t.length();
	memset(dp,0,sizeof(dp));		//初始化数组dp
	for(i=0; i<n; i++)				//初始化dp第一列
		if(s[i]==t[0])
			dp[i][0]=1;
    for(j=0; j<m; j++)				//初始化dp第一行
		if(s[0]==t[j])
			dp[0][j]=1;
	for(i=1; i<n; i++)				//利用状态转移方程求dp的其他元素
		for(j=1; j<m; j++)
		{	if (s[i]==t[j])
				dp[i][j]=dp[i-1][j-1]+1;
			ans=max(ans,dp[i][j]);
		}
	return ans;
}
void main()
{
	printf("求解结果\n");
	printf("   最长的公共连续子串: %d\n",Maxlength(s,t));	//输出：2
}
