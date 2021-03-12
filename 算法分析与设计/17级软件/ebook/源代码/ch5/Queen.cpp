//非递归回溯算法
#include <stdio.h>
#include <stdlib.h>
#define MAXN 20					//最多皇后个数
int q[MAXN];					//存放各皇后所在的列号,为全局变量
int count=0;					//累计解个数
void dispasolution(int n)   	//输出一个解
{
	printf("  第%d个解:",++count);
	for (int i=1;i<=n;i++)
		printf("(%d,%d) ",i,q[i]);
	printf("\n");
}
bool place(int i)				//测试第i行的q[i]列上能否摆放皇后
{
	int j=1;
	if (i==1) return true;
	while (j<i)					//j=1～i-1是已放置了皇后的行
	{	if ((q[j]==q[i]) || (abs(q[j]-q[i])==abs(j-i))) 
			//该皇后是否与以前皇后同列，位置(j,q[j])与(i,q[i])是否同对角线
			return false;
		j++;
	}
	return true;
}
void Queens(int n)						//求解n皇后问题
{
	int i=1;							//i表示当前行,也表示放置第i个皇后
	q[i]=0;								//q[i]是当前列,从0列即开头试探
	while (i>=1)						//重复试探
	{
		q[i]++;
		while (q[i]<=n && !place(i))	//试探一个位置(i,q[i])
			q[i]++;
		if (q[i]<=n)					//为第i个皇后找到了一个合适位置(i,q[i])
		{
			if (i==n)					//若放置了所有皇后,输出一个解
				dispasolution(n);
			else						//皇后没有放置完
			{
				i++;					//转向下一行,即开始下一个皇后的放置
				q[i]=0;					//每次放一个新皇后,都从该行的列头进行试探
			}
		}
		else i--;						//若第i个皇后找不到合适的位置,则回溯到上一个皇后
	}
}

void main()
{	int n;								//n存放实际皇后个数
	scanf("%d",&n);
	printf("%d皇后问题求解如下:\n",n);
	Queens(n);
}
