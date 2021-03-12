//求解最长公共子序列问题的算法
#include <iostream>
#include <string.h>
#include <vector>
#include <string>
using namespace std;
#define max(x,y) ((x)>(y)?(x):(y))
#define MAX 51							//序列中最多的字符个数
//问题表示
int m,n;
string a,b;
//求解结果表示
int dp[MAX][MAX];						//动态规划数组
vector<char> subs;						//存放LCS
void LCSlength()						//求dp
{
	int i,j;
	for (i=0;i<=m;i++)					//将dp[i][0]置为0,边界条件
		dp[i][0]=0;
	for (j=0;j<=n;j++)					//将dp[0][j]置为0,边界条件
		dp[0][j]=0;
	for (i=1;i<=m;i++)
		for (j=1;j<=n;j++)				//两重for循环处理a、b的所有字符
		{	if (a[i-1]==b[j-1])			//情况(1)
				dp[i][j]=dp[i-1][j-1]+1;
			else						//情况(2)
				dp[i][j]=max(dp[i][j-1],dp[i-1][j]);

		}
}
void Buildsubs()					//由dp构造从subs
{
	printf("求LCS\n");
	int k=dp[m][n];					//k为a和b的最长公共子序列长度
	int i=m;
	int j=n;
	while (k>0)						//在subs中放入最长公共子序列(反向)
		if (dp[i][j]==dp[i-1][j])
			i--;
		else if (dp[i][j]==dp[i][j-1])
			j--;
		else
		{
			printf("i=%d,j=%d,添加元素a[i-1]=%c\n",i,j,a[i-1]);
			subs.push_back(a[i-1]);	//subs中添加a[i-1]
			i--; j--; k--;
		}
}
void main()
{
	a="abcbdb";
	b="acbbabdbb";
	m=a.length();			//m为a的长度
	n=b.length();			//n为b的长度
	LCSlength();			//求出dp
	printf("输出dp\n");
	for (int i=0;i<=n;i++)
	{
		for (int j=0;j<=n;j++)
			printf("%3d",dp[i][j]);
		printf("\n");
	}
	Buildsubs();			//求出LCS
	cout << "求解结果" << endl;
	cout << "    a: " << a << endl;
	cout << "    b: " << b << endl;
	cout << "    最长公共子序列: ";
	vector<char>::reverse_iterator rit;
	for (rit=subs.rbegin();rit!=subs.rend();++rit)
		cout << *rit;
	cout << endl;
	cout << "    长度: " << dp[m][n] << endl;
}
