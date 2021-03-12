#include <stdio.h>
#include <string.h>
#define MAXN 20						//最多集装箱个数
//问题表示
int w[]={0,10,40,40};				//各集装箱重量,不用下标0的元素
int	n=3;
int c1=50,c2=50;
int maxw=0;							//存放第一艘轮船最优解的总重量
int x[MAXN];						//存放第一艘轮船最优解向量
void dfs(int tw,int rw,int op[],int i) //求第一艘轮船的最优解
{
	if (i>n)						//找到一个叶子结点
	{
		if (tw<=c1 && tw>maxw)
		{
			maxw=tw;				//找到一个满足条件的更优解,保存它
			for (int j=1;j<=n;j++)	//复制最优解
				x[j]=op[j];
		}
	}
	else						//尚未找完所有集装箱
	{	op[i]=1;				//选取第i个集装箱
		if (tw+w[i]<=c1)		//左孩子结点剪枝：装载满足条件的集装箱
			dfs(tw+w[i],rw-w[i],op,i+1);
		op[i]=0;				//不选取第i个集装箱,回溯
		if (tw+rw>c1)			//右孩子结点剪枝
			dfs(tw,rw-w[i],op,i+1);
	}
}
void dispasolution(int n)		//输出一个解
{
	for (int j=1;j<=n;j++)
		if (x[j]==1)
			printf("\t将第%d个集装箱装上第一艘轮船\n",j);
		else
			printf("\t将第%d个集装箱装上第二艘轮船\n",j);

}
bool solve()			//求解复杂装载问题
{
	int sum=0;			//累计第一艘轮船装完后剩余的集装箱重量
	for (int j=1;j<=n;j++)
		if (x[j]==0)
			sum+=w[j];
	if (sum<=c2)			//第二艘轮船可以装完
		return true;
	else				//第二艘轮船不能装完
		return false;
}

void main()
{
	int op[MAXN];				//存放临时解
	memset(op,0,sizeof(op));
	int rw=0;
	for (int i=1;i<=n;i++)
		rw+=w[i];
	dfs(0,rw,op,1);				//求第一艘轮船的最优解
	printf("求解结果\n");
	if (solve())				//输出结果
	{
		printf("    最优方案\n");
		dispasolution(n);
	}
	else
		printf("    没有合适的装载方案\n");
}
