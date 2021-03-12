#include <iostream>
#include <string.h>
#include <string>
using namespace std;
#define max(x,y) ((x)>(y)?(x):(y))
#define MAXN 258
//问题表示
string str;
int solve()
{
	int dp[MAXN];
	memset(dp,0,sizeof(dp));
	if (str[0]>='0' && str[0]<='9')		//str[0]为数字
		dp[0]=1;
	for (int i=1;i<str.length();i++)
		if (str[i]>='0' && str[i]<='9')	//str[i]为数字
			dp[i]=dp[i-1]+1;
		else
			dp[i]=0;
	int ans=0;
	for (int j=0;j<str.length();j++)
		ans=max(ans,dp[j]);
	return ans;
}
int main()
{
	cin >> str;
	printf("%d\n",solve());
	return 0;
}
