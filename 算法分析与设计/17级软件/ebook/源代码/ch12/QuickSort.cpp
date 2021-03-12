//快速排序算法
#include <stdio.h>
#include <stdlib.h>				//包含产生随机数的库函数
#include <time.h>
void disp(int a[],int n)		//输出a中所有元素
{
	for (int i=0;i<n;i++)
		printf("%d ",a[i]);
	printf("\n");
}
int Partition(int a[],int s,int t)	//划分算法
{
	int i=s,j=t;
	int tmp=a[s];				//用序列的第1个记录作为基准
	while (i!=j)				//从序列两端交替向中间扫描,直至i=j为止
	{
		while (j>i && a[j]>=tmp) 
			j--;				//从右向左扫描,找第1个关键字小于tmp的a[j]
		a[i]=a[j];				//将a[j]前移到a[i]的位置
		while (i<j && a[i]<=tmp) 
			i++;				//从左向右扫描,找第1个关键字大于tmp的a[i]
		a[j]=a[i];				//将a[i]后移到a[j]的位置
	}
	a[i]=tmp;
	return i;
}
int randa(int a,int b)	//产生n个[a,b]的随机数
{
	return rand()%(b-a+1)+a;
}
void swap(int &x,int &y)		//交换x和y
{
	int tmp=x;
	x=y; y=tmp;
}
void QuickSort(int a[],int s,int t)	//对a[s..t]元素序列进行递增排序
{
	if (s<t) 					//序列内至少存在2个元素的情况
	{
		int j=randa(s,t);		//产生[s,t]的随机数j
		swap(a[j],a[s]);		//将a[j]作为基准
		int i=Partition(a,s,t);
		QuickSort(a,s,i-1);		//对左子序列递归排序
		QuickSort(a,i+1,t);		//对右子序列递归排序
	}
}
void main()
{
	int n=10;
	int a[]={2,5,1,7,10,6,9,4,3,8};
	printf("排序前:"); disp(a,n);
	srand((unsigned)time(NULL));		//随机种子
	QuickSort(a,0,n-1);
	printf("排序后:"); disp(a,n);
}
