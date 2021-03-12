//冒泡排序算法
#include <stdio.h>
void disp(int a[],int n)			//输出a中所有元素
{	int i;
	for (i=0;i<n;i++)
		printf("%d ",a[i]);
	printf("\n");
}
void BubbleSort(int a[],int n,int i)
{	int j,tmp;
	bool exchange;
	if (i==n-1) return;			//满足递归出口条件
	else
	{	exchange=false;			//置exchange为false
		for (j=n-1;j>i;j--)		//将a[i..n-1]中最小元素放在a[i]处
			if (a[j]<a[j-1])		//当相邻元素反序时
			{	tmp=a[j];			//a[j]与a[j-1]进行交换,3次元素移动将最小元素前移
				a[j]=a[j-1]; a[j-1]=tmp;
				exchange=true;	//发生交换置exchange为true
			}
		if (exchange==false)		//未发生交换时直接返回
			return;
		else						//发生交换时继续递归调用
			BubbleSort(a,n,i+1);
	}
}
void main()
{	int n=10;
	int a[]={2,5,1,7,10,6,9,4,3,8};
	printf("排序前:"); disp(a,n);
	BubbleSort(a,n,0);
	printf("排序后:"); disp(a,n);
}
