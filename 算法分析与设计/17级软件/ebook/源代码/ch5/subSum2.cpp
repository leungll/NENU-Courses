//判断子集和问题是否存在解:第二种方法
#include <stdio.h>
#define MAXN 20						//最多整数个数
//问题表示
int n=4,W;
int w[]={0,11,13,24,7};				//存放所有整数,不用下标0的元素
int count;							//全局变量，累计解个数
void dfs(int tw,int rw,int i)		//求解子集和
{
	if (i>n)						//找到一个叶子结点
	{	if (tw==W)					//找到一个满足条件的解,解个数增1
			count++;
	}
	else							//尚未找完所有物品
	{
		if (tw+w[i]<=W)				//左孩子结点剪枝：选取满足条件的整数w[i]
			dfs(tw+w[i],rw-w[i],i+1);	//选取第i个整数
		if (tw+rw>W)				//右孩子结点剪枝：剪除不可能存在解的结点
			dfs(tw,rw-w[i],i+1);			//不选取第i个整数,回溯
	}
}
bool solve()						//判断子集和问题是否存在解
{
	count=0;
	int rw=0;
	for (int j=1;j<=n;j++)			//求所有整数和rw
		rw+=w[j];
	dfs(0,rw,1);					//i从1开始
	if (count>0)
		return true;
	else
		return false;
}
void main()
{
	W=7;
	printf("W=%d时%s\n",W,(solve()?"存在解":"没有解"));
	W=15;
	printf("W=%d时%s\n",W,(solve()?"存在解":"没有解"));
	W=21;
	printf("W=%d时%s\n",W,(solve()?"存在解":"没有解"));
	W=24;
	printf("W=%d时%s\n",W,(solve()?"存在解":"没有解"));
}
