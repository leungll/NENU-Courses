#include<stdio.h>
#include<string>
using namespace std;
#define min(x,y) ((x)<(y)?(x):(y))
#define MAX 201
#define min(x,y) ((x)<(y)?(x):(y))
//问题表示
string a="sfdqxbw";
string b="gfdgw";
//求解结果表示
int dp[MAX][MAX];
void solve()					//求dp
{
	int i,j;
	for (i=1;i<=a.length();i++) 
		dp[i][0]=i;			//把a的i个字符全部删除转换为b
	for (j=1; j<=b.length(); j++)
		dp[0][j]=j;			//在a中插入b的全部字符转换为b
	for (i=1; i<=a.length(); i++)
       	for (j=1; j<=b.length(); j++)
		{
			if (a[i-1]==b[j-1])
				dp[i][j]=dp[i-1][j-1];
			else
				dp[i][j]=min(min(dp[i-1][j],dp[i][j-1]),dp[i-1][j-1])+1;
		}
}
void main()
{
	solve();
	printf("求解结果\n");
	printf("    最少的字符操作次数: %d\n",dp[a.length()][b.length()]);
}
