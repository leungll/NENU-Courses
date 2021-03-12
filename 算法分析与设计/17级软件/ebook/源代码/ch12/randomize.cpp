#include <stdio.h>
#include <stdlib.h>				//包含产生随机数的库函数
#include <time.h>
void randa(int x[],int n,int a,int b)	//产生n个[a,b]的随机数
{	int i;
	for (i=0;i<n;i++)
		x[i]=rand()%(b-a+1)+a;
}
void main()
{
	int i,n=10,x[10];
	int b=30,a=10;
	srand((unsigned)time(NULL));		//随机种子
	for (i=0;i<n;i++)
		randa(x,n,a,b);
	for (i=0;i<n;i++)
		printf("%d  ",x[i]);
	printf("\n");
}