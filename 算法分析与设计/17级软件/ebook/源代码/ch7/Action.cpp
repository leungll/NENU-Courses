#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;
#define MAX 51
//问题表示
struct Action
{	int b;						//活动起始时间
	int e;						//活动结束时间
	bool operator<(const Action &s) const	//重载<关系函数
	{
		return e<=s.e;			//用于按活动结束时间递增排序
	}
};
int n=11;
Action A[]={{0},{1,4},{3,5},{0,6},{5,7},{3,8},{5,9},{6,10},{8,11},{8,12},{2,13},{12,15}};	//下标0不用
//求解结果表示
bool flag[MAX];					//标记选择的活动
int Count=0;					//选取的兼容活动个数
void solve()					//求解最大兼容活动子集
{
	memset(flag,0,sizeof(flag));//初始化为false
	sort(A+1,A+n+1);			//A[1..n]按活动结束时间递增排序
	int preend=0;				//前一个兼容活动的结束时间
	for (int i=1;i<=n;i++)
	{	if (A[i].b>=preend)
		{	flag[i]=true;		//选择A[i]活动
			preend=A[i].e;
		}
	}
}
void main()
{
	solve();
	printf("求解结果\n");
	printf("  选取的活动:");
	for (int i=1;i<=n;i++)
		if (flag[i])
		{
			printf("[%d,%d] ",A[i].b,A[i].e);
			Count++;
		}
	printf("\n  共%d个活动\n",Count);
}
