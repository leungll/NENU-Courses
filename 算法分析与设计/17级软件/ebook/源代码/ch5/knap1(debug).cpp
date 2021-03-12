//采用剪枝求解0/1背包问题的算法
#include <stdio.h>
#define MAXN 20					//最多物品数
//问题表示
int n=4;						//4种物品
int W=6;						//限制重量为6
int w[]={0,5,3,2,1};			//存放4个物品重量,不用下标0元素
int v[]={0,4,4,3,1};			//存放4个物品价值,不用下标0元素
//求解结果表示
int x[MAXN];					//存放最终解
int maxv; 						//存放最优解的总价值
int maxw;						//存放最优解的总重量
void dfs(int i,int tw,int tv,int op[]) //考虑第i个物品
{
	printf("  i=%d,dfs(%d,%d)\n",i,tw,tv);
	if (i>n)					//找到一个叶子结点
	{	if (tw==W && tv>maxv) 	//找到一个满足条件的更优解,保存它
		{	maxv=tv;
			maxw=tw;
			for (int j=1;j<=n;j++)
				x[j]=op[j];
		}
	}
	else						//尚未找完所有物品
	{	if (tw+w[i]<=W)			//左孩子结点剪枝：满足条件时才放入第i个物品
		{
			//printf("  选择物品i=%d,dfs(%d,%d)\n",i,tw+w[i],tv+v[i]);
			op[i]=1;			//选取第i个物品
			dfs(i+1,tw+w[i],tv+v[i],op);
		}
		op[i]=0;				//不选取第i个物品,回溯
		//printf("  不选择物品i=%d,dfs(%d,%d)\n",i,tw,tv);
		dfs(i+1,tw,tv,op);
	}
}
void dispasolution()	//输出最优解
{	int i;
	printf("最佳装填方案是:\n");
	for (i=1;i<=n;i++)
		if (x[i]==1)
			printf("  选取第%d个物品\n",i);
	printf("总重量=%d,总价值=%d\n",maxw,maxv);
}
void main()
{
	int op[MAXN];				//存放临时解
	dfs(1,0,0,op);
	dispasolution();
}
