#include <stdio.h>
#include <string.h>
#define MAX 51
//问题表示
struct Action
{
	int b;					//活动起始时间
	int e;					//活动结束时间
};
int n=4;
Action A[]={{0,0},{1,3},{2,5},{4,8},{6,10}};	//下标0不用
//求解结果表示
int x[MAX];					//解向量
int bestx[MAX];				//最优解向量
int laste=0;				//一个方案中最后兼容活动的结束时间
int sum=0;					//一个方案中所有兼容活动个数
int maxsum=0;				//最优方案中所有兼容活动个数
void swap(int &x,int &y)	//交换x、y
{	int tmp=x;
	x=y; y=tmp;
}
void dispasolution()					//输出一个解
{
	printf("最优调度方案\n");
	int laste=0;
	for (int j=1;j<=n;j++)
	{
		if (A[bestx[j]].b>=laste)		//选取活动bestx[j]
		{
			printf("    选取活动%d: [%d,%d)\n",bestx[j],A[bestx[j]].b,A[bestx[j]].e);
			laste=A[bestx[j]].e;
		}
	}
	printf("  安排活动的个数=%d\n",maxsum);
}
void dfs(int i)							//搜索活动问题最优解
{
	if (i>n)							//到达叶结点,产生一种调度方案
    {
		if (sum>maxsum)
		{
			maxsum=sum;
			for (int k=1;k<=n;k++)
				bestx[k]=x[k];
		}
	}
	else
	{
		for(int j=i; j<=n; j++)				//没有到达叶结点,考虑i到n的活动
		{	//第i层结点选择活动x[j]
			int sum1=sum;					//保存sum，laste以便回溯
			int laste1=laste;
			if (A[x[j]].b>=laste)			//活动x[j]与前面兼容
			{
				sum++;						//兼容活动个数增1
				laste=A[x[j]].e;			//修改本方案的最后兼容时间
			}
			swap(x[i],x[j]);				//排序树问题递归框架:交换x[i],x[j]
			dfs(i+1);						//排序树问题递归框架:进入下一层
			swap(x[i],x[j]);				//排序树问题递归框架:交换x[i],x[j]
			sum=sum1;						//回溯
			laste=laste1;					//即撤销第i层结点对活动x[j]的选择,以便再选择其他活动
		}
	}
}
void main()
{
	for (int i=1;i<=n;i++)
		x[i]=i;
	dfs(1);								//i从1开始搜索
	dispasolution();					//输出结果
}



