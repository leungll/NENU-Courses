#include <stdio.h>
#include <string.h>
#include <queue>
#include <vector>
using namespace std;
#define INF 99999	//定义∞
#define MAXN 21
//问题表示
int n=4;
int c[MAXN][MAXN]={{0}, {0,9,2,7,8},{0,6,4,3,7},{0,5,8,1,8},{0,7,6,9,4} };	//下标0的元素不用
//求解结果表示
int x[MAXN];					//临时解
int cost=0;						//临时解的成本
int bestx[MAXN];				//最优解
int mincost=INF;				//最优解的成本
bool worker[MAXN];				//worker[j]表示任务j是否已经分配人员
void dfs(int i)					//为第i个人员分配任务
{
	if (i>n)					//到达叶子结点
	{
		if (cost<mincost)		//比较求最优解
		{
			mincost=cost;
			for (int j=1;j<=n;j++)
				bestx[j]=x[j];
		}
	}
	else
	{
		for (int j=1;j<=n;j++)			//为人员i试探任务j:1到n
			if (!worker[j])				//若任务j还没有分配
			{
				worker[j]=true;
				x[i]=j;					//任务j分配给人员i
				cost+=c[i][j];
				dfs(i+1);				//为人员i+1分配任务
				worker[j]=false;		//回退
				x[j]=0;
				cost-=c[i][j];
			}
	}
}
void main()
{
	memset(worker,0,sizeof(worker));	//worker初始化为false
	dfs(1);								//从人员1开始
	printf("最优方案:\n");
	for (int k=1;k<=n;k++)
		printf("   第%d个人安排任务%d\n",k,bestx[k]);
	printf("   总成本=%d\n",mincost);
}






