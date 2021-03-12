//冒泡排序
#include <stdio.h>
void swap(int &x,int &y)		//交换x和y
{	int tmp=x;
	x=y; y=tmp;
}
void BubbleSort(int a[],int n)	//对a[0..n-1]按递增有序进行冒泡排序
{	int i,j;
	bool exchange;
	for (i=0;i<n-1;i++)		//进行n-1趟排序
	{	exchange=false;		//本趟排序前置exchange为false
		for (j=n-1;j>i;j--)	//无序区元素比较,找出最小元素
			if (a[j]<a[j-1])		//当相邻元素反序时
			{	swap(a[j],a[j-1]);	//a[j]与a[j-1]进行交换
				exchange=true;//本趟排序发生交换置exchange为true
			}
		if (exchange==false)	//本趟未发生交换时结束算法
			return;
	}
}
void disp(int a[],int n)		//输出a中所有元素
{	int i;
	for (i=0;i<n;i++)
		printf("%d ",a[i]);
	printf("\n");
}
void main()
{	int n=10;
	int a[]={2,5,1,7,10,6,9,4,3,8};
	printf("排序前:"); disp(a,n);
	BubbleSort(a,n);
	printf("排序后:"); disp(a,n);
}
