#include <stdio.h>
#define MAX 101
//问题表示
int k;
//求解结果表示
int a[MAX][MAX];						//存放比赛日程表（行列下标为0的元素不用）
void Plan(int k)
{
	int i,j,n,t,temp;
	n=2;								//n从2^1=2开始
	a[1][1]=1; a[1][2]=2;   			//求解2个选手比赛日程,得到左上角元素
	a[2][1]=2; a[2][2]=1;
	for (t=1;t<k;t++)						//迭代处理,依次处理2^2(t=1)…,2^k(t=k-1)个选手
	{
		temp=n;								//temp=2^t
		n=n*2; 								//n=2^(t+1)
		for (i=temp+1;i<=n;i++ )			//填左下角元素
			for (j=1; j<=temp; j++)
				a[i][j]=a[i-temp][j]+temp; 	//左下角元素和左上角元素的对应关系
		for (i=1; i<=temp; i++)				//填右上角元素
			for (j=temp+1; j<=n; j++)
				a[i][j]=a[i+temp][(j+temp)% n];
		for (i=temp+1; i<=n; i++)			//填右下角元素
			for (j=temp+1; j<=n; j++)
				a[i][j]=a[i-temp][j-temp];
    }
}
void main()
{
	k=3;
	int n=1<<k;							//n等于2的k次方即n=2^k
	Plan(k);							//产生n个选手的比赛日程表
	for(int i=1; i<=n; i++)				//输出比赛日程表
	{	for(int j=1; j<=n; j++)
			printf("%4d",a[i][j]);
		printf("\n");
	}
}
