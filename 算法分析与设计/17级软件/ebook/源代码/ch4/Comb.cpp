//递归求解组合列问题
#include <stdio.h>
#define MAXK 10
int a[MAXK];					//存放一个组合
int n,k;						//全局变量
void dispacomb()				//输出一个组合
{
	for (int i=0;i<k;i++)
		printf("%3d",a[i]);
	printf("\n");
}
void comb(int n,int k)	//求1..n中k个整数的组合
{
	if (k==0)					//k为0时输出一个组合
		dispacomb();
	else
	{	for (int i=k;i<=n;i++)
		{	a[k-1]=i;			//a[k-1]位置取k～n的整数
			comb(i-1,k-1); 	//a[k-1]组合a[0..i-1]中的k-1个整数产生一个组合
		}
	}
}
void main()
{	
	n=5; k=3;
	printf("1..%d中%d个的整数的所有组合:\n",n,k);
	comb(n,k);
}
