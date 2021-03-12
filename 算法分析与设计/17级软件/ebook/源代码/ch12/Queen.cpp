#include <stdio.h>
#include <stdlib.h>				//包含产生随机数的库函数
#include <time.h>
#define N 20					//最多皇后个数
int q[N];						//存放各皇后所在的列号,即(i,q[i])为一个皇后位置
int num=0;						//累计运行次数
void dispasolution(int n)		//输出n皇后问题的一个解
{
	printf("  第%d次运行找到一个解: ",num);
	for (int i=1;i<=n;i++)
		printf("(%d,%d) ",i,q[i]);
	printf("\n");
}
int randa(int a,int b)	//产生n个[a,b]的随机数
{
	return rand()%(b-a+1)+a;
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
bool queen(int i,int n)			//放置1～i的皇后
{
	int count,j;
	if (i>n)
	{
		dispasolution(n);		//所有皇后放置结束
		return true;
	}
	else
	{
		count=0;				//试探次数累计
		while (count<=n)		//最多试探n次
		{
			j=randa(1,n);			//产生第i行上1到n列的一个随机数j
			count++;
			if (place(i,j))	break;	//在第i行上找到一个合适位置(i,j)
		}
		if (count>n) return false;
		q[i]=j;
		queen(i+1,n);
	}
}
void main()
{
	int n=6;						//n为存放实际皇后个数
	printf("%d皇后问题求解如下：\n",n);
	srand((unsigned)time(NULL));	//随机种子
	while (num<10)
	{
		if (queen(1,n))				//找到一个解退出
			break;
		num++;
		printf("  第%d次运行没有找到解\n",num);
	}
}
