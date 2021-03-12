#include <iostream>
#include <string.h>
#include <string>
using namespace std;
#define max(x,y) ((x)>(y)?(x):(y))
#define MAXN 258
//问题表示
string str;
int solve1()
{
	int curlength=0,ans=0;
	char curch=str[0];
	for (int i=0;i<str.length();i++)
	{
		if (str[i]>='0' && str[i]<='9')
			curlength++;
		else
			curlength=0;
		ans=max(ans,curlength);
	}
	return ans;
}
int main()
{
	cin >> str;
	printf("%d\n",solve1());
	return 0;
}
