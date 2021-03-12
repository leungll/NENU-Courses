#include <stdio.h>
#include <stdlib.h>				//包含产生随机数的库函数
#include <time.h>
int randa(int a,int b)			//产生一个[a,b]的随机数
{
	return rand()%(b-a+1)+a;
}
double rand01()					//产生一个[0,1]的随机数
{
	return randa(0,100)*1.0/100;
}
double solve()						//求π的蒙特卡罗算法
{
	int n=10000;
	int m=0;
	double x,y;
	for (int i=1;i<=n;i++)
	{
		x=rand01();
		y=rand01();
		if (x*x+y*y<=1.0)
			m++;
	}
	return 4.0*m/n;
}
void main()
{
	srand((unsigned)time(NULL));	//随机种子
	printf("PI=%g\n",solve());		//输出π
}

