#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;
#define MAXN 20						//最多集装箱个数
//问题表示
int w[]={0,5,2,6,4,3};				//各集装箱重量,不用下标0的元素
int	n=5,W=10;
//求解结果表示
int maxw;							//存放最优解的总重量
int x[MAXN];						//存放最优解向量

void solve()						//求解最优装载问题
{
	memset(x,0,sizeof(x));			//初始化解向量
	sort(w+1,w+n+1);				//w[1..n]递增排序
	maxw=0;
	int restw=W;						//剩余重量
	for (int i=1;i<=n &&  w[i]<=restw;i++)
	{
		x[i]=1;						//选择集装箱i
		restw-=w[i];				//减少剩余重量
		maxw+=w[i];					//累计装载总重量
	}
}
void main()
{
	solve();
	printf("最优方案\n");
	for (int i=1;i<=n;i++)
		if (x[i]==1)
			printf("  选取重量为%d的集装箱\n",w[i]);
	printf("总重量=%d\n",maxw);
}
