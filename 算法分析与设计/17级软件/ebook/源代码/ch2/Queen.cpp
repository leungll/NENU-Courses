//求解n皇后问题
#include <stdio.h>
#include <stdlib.h>
#define N 20					//最多皇后个数
int q[N];						//存放各皇后所在的列号,即(i,q[i])为一个皇后位置
int count=0;					//累计解个数
void dispasolution(int n)		//输出n皇后问题的一个解
{
	printf("    第%d个解：",++count);
	for (int i=1;i<=n;i++)
		printf("(%d,%d) ",i,q[i]);
	printf("\n");
}
bool place(int i,int j)			//测试(i,j)位置能否摆放皇后
{
	if (i==1) return true;		//第一个皇后总是可以放置
	int k=1;
	while (k<i)					//k=1～i-1是已放置了皇后的行
	{	if ((q[k]==j) || (abs(q[k]-j)==abs(i-k)))
			return false;
		k++;
	}
	return true;
}
void queen(int i,int n)			//放置1～i的皇后
{	if (i>n) 
		dispasolution(n);		//所有皇后放置结束
	else
	{
		for (int j=1;j<=n;j++)		//在第i行上试探每一个列j
			if (place(i,j))			//在第i行上找到一个合适位置(i,j)
			{	q[i]=j;
				queen(i+1,n);
			}
	}
}
void main()
{	int n;					//n为存放实际皇后个数
	printf(" 皇后问题(n<20) n=");
	scanf("%d",&n);
	if (n>20)
		printf("n值太大,不能求解\n");
	else
	{	printf("%d皇后问题求解如下：\n",n);
		queen(1,n);					//放置1～i的皇后
	}
}
