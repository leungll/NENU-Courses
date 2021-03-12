#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;
#define MAX 51
//问题表示
struct Cow						//奶牛的类型声明
{
	int no;						//牛编号
	int b;						//活动起始时间
	int e;						//活动结束时间
	bool operator<(const Cow &s) const	//重载<关系函数
	{
		if (e==s.e)				//结束时间相同按开始时间递增排序
			return b<=s.b;
		else					//否则按结束时间递增排序
			return e<=s.e;
	}
};
int n=5;
Cow A[]={{0},{1,1,10},{2,2,4},{3,3,6},{4,5,8},{5,4,7}};	//下标0不用
//求解结果表示
int ans[MAX];							//ans[i]表示第A[i].no头牛的蓄栏编号
void solve()							//求解最大兼容活动子集
{
	sort(A+1,A+n+1);					//A[1..n]按指定方式排序
	memset(ans,0,sizeof(ans));			//初始化为0
	int num=1;							//蓄栏编号
	for (int i=1;i<=n;i++)				//i、j均为排序后的下标
	{
		if (ans[i]==0)					//第i头牛还没有安排蓄栏
		{
			ans[i]=num;					//第i头牛安排蓄栏num
			int preend=A[i].e;			//前一个兼容活动的结束时间
			for (int j=i+1;j<=n;j++)	//查找一个最大兼容活动子集
			{
				if (A[j].b>preend && ans[j]==0)
				{
					ans[j]=num;			//将一个兼容活动子集中所有活动安排在num蓄栏中
					preend=A[j].e;		//更新结束时间
				}
			}
			num++;						//查找下一个最大兼容活动子集,num增1
		}
	}
}
void dispa()
{
	printf("  i   编号  开始时间  结束时间\n");
	for (int i=1;i<=n;i++)
		printf("  %d     %d    [ %d        %d ]\n",i,A[i].no,A[i].b,A[i].e);
}
void dispb()
{
	dispa();
	printf("ans:\n");
	for (int j=1;j<=n;j++)
		printf("    ans[%d]=%d\n",j,ans[j]);
}

void main()
{
	printf("排序前A:\n"); dispa();
	solve();
	printf("排序后A:\n"); dispb();
	printf("求解结果\n");
	for (int i=1;i<=n;i++)
		printf("    牛%d安排的蓄栏: %d\n",A[i].no,ans[i]);
}
