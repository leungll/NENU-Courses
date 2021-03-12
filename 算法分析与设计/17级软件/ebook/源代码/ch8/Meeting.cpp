#include <stdio.h>
#include <string.h>
#include <vector>
#include <algorithm>
using namespace std;
#define max(x,y) ((x)>(y)?(x):(y))
#define MAX 101
//问题表示
struct NodeType
{
	int b;							//开始时间
	int e;							//结束时间
	int length;						//订单的执行时间
    bool operator < (const NodeType t) const
    {	//用于排序的运算符重载函数
		return e<t.e;				//按结束时间递增排序
    }
};
int n=11;							//订单个数
NodeType A[MAX]={{1,4},{3,5},{0,6},{5,7},{3,8},{5,9},{6,10},{8,11},{8,12},{2,13},{12,15}};	//存放订单
//求解结果表示
int dp[MAX];					//动态规划数组
int pre[MAX];					//pre[i]存放前驱订单编号

void solve()					//求dp和pre
{
	memset(dp,0,sizeof(dp));	//dp数组初始化
	stable_sort(A,A+n);			//采用稳定的排序算法
	dp[0]=A[0].length;
	pre[0]=-1;
	for (int i=1;i<n;i++)
	{
		int low=0, high=i-1;
		while(low<=high)		//在A[0..i-1]中查找结束时间早于A[i]开始时间的最晚订单A[low-1]
		{
			int mid=(low+high)/2;
			if(A[mid].e<=A[i].b)
				low=mid+1;
			else
				high=mid-1;
		}
		if (low==0)				//特殊情况
		{
			if(dp[i-1]>=A[i].length)
			{
				dp[i]=dp[i-1];
				pre[i]=-2;		//不选中订单i
			}
			else
			{
				dp[i]=A[i].length;
				pre[i]=-1;		//没有前驱订单
			}
		}
		else					//A[i]前面最晚有兼容订单A[low-1]
		{
			if (dp[i-1]>=dp[low-1]+A[i].length)
			{
				dp[i]=dp[i-1];
				pre[i]=-2;		//不选中订单i
			}
			else
			{
				dp[i]=dp[low-1]+A[i].length;
				pre[i]=low-1;	//选中订单i
			}
		}
	}
}
void Dispasolution()			//输出一个选择的订单方案
{	vector<int> res;
	int i=n-1;					//从n-1开始

	while (true)
	{
		if (i==-1)				//A[i]没有前驱订单
			break;
		if (pre[i]==-2)			//不选择A[i]
			i--;
		else					//选择A[i]
		{
			res.push_back(i);
			i=pre[i];
		}
	}
	vector<int>::reverse_iterator it;
	printf("    选择的订单: ");
	for (it=res.rbegin();it!=res.rend();++it)
		printf("%d[%d, %d] ",*it,A[*it].b,A[*it].e);
	printf("\n");
	printf("    兼容订单的总时间: %d\n",dp[n-1]);
}
int main()
{
	for (int i=0; i<n; i++)		//求订单的长度
		A[i].length=A[i].e-A[i].b;
	solve();
	printf("求解结果\n");
	Dispasolution();
    return 0;
}
