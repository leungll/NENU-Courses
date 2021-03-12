//求解区间覆盖问题的算法
#include <stdio.h>
#define MaxSize 10
#include "QuickSort.cpp"		//包含快速排序算法
int minSegment(int x[],int n,int k,int y[])	//求x的最大覆盖区间集合y
{	int i,m=0,tmp;			//m为y的下标，从0开始
	QuickSort(x,0,n-1);		//调用快速排序算法对x序列递增排序
	tmp=x[0];					//区间的起始位置
	y[0]=x[0];
	for(i=1;i<n;i++)
		if(x[i]-tmp>k)		//如果x[i]与tmp的距离大于k
		{	tmp=x[i];			//开始下一个以x[i]为起点的覆盖区间
			m++; y[m]=x[i];
		}
	return m+1;
}
void disp(int x[],int n)		//输出x中的元素
{	int i;
	for (i=0;i<n;i++)
		printf("%d ",x[i]);
	printf("\n");
}
void main()
{	int x[]={2,4,1,6,-2,5,3};
	int y[MaxSize];
	int n=7,k=3,m;
	printf("排序前:"); disp(x,n);
	QuickSort(x,0,n-1);
	printf("排序后:"); disp(x,n);
	m=minSegment(x,n,k,y);
	printf("求解结果:\n");
	printf("选取的区间为%d个\n",m);
	printf("选取的区间:"); disp(y,m);
}
