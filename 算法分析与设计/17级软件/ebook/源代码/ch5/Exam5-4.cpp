//例5.4算法
#include <stdio.h>
#define N 9
void fun(char op[],int sum,int prevadd,int a[],int i)
{
	if (i==N)						//扫描完所有位置
	{
		if (sum==100)				//找到一个解
		{
			printf("  %d",a[0]);	//输出解
			for (int j=1;j<N;j++)
			{
				if (op[j]!=' ')
					printf("%c",op[j]);
				printf("%d",a[j]);
			}
			printf("=100\n");
		}
		return;
	}
	op[i]='+';						//位置i插入'+'
	sum+=a[i];						//计算结果
	fun(op,sum,a[i],a,i+1);			//继续处理下一个位置
	sum-=a[i];						//回溯

	op[i]='-';						//位置i插入'-'
	sum-=a[i];						//计算结果
	fun(op,sum,-a[i],a,i+1);		//继续处理下一个位置
	sum+=a[i];						//回溯

	op[i]=' ';						//位置i插入' '
	sum-=prevadd;					//先减去前面的元素值
	int tmp;						//计算新元素值
	if (prevadd>0)
		tmp=prevadd*10+a[i];		//如prevadd=5,a[i]=6,结果为56
	else
		tmp=prevadd*10-a[i];		//如prevadd=-5,a[i]=6,结果为-56
	sum+=tmp;						//计算合并结果
	fun(op,sum,tmp,a,i+1);			//继续处理下一个位置
	sum-=tmp;						//回溯sum
	sum+=prevadd;
}
void main()
{
	int a[N];
	char op[N];					//op[i]表示在位置i插入运算符
	for (int i=0;i<N;i++)		//为a赋值为1,2，...,9
		a[i]=i+1;
	printf("求解结果\n");
	fun(op,a[0],a[0],a,1);		//插入位置i从1开始
}