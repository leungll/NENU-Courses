//简单选择排序算法
#include <stdio.h>
void disp(int a[],int n)		//输出a中所有元素
{	int i;
	for (i=0;i<n;i++)
		printf("%d ",a[i]);
	printf("\n");
}
void SelectSort(int a[],int n,int i)
{	int j,k,tmp;
	if (i==n-1) return;			//满足递归出口条件
	else
	{	k=i;					//k记录a[i..n-1]中最小元素的下标
		for (j=i+1;j<n;j++)		//在a[i..n-1]中找最小元素
			if (a[j]<a[k])
				k=j;
		if (k!=i)				//若最小元素不是a[i]
		{	tmp=a[i];			//a[i]和a[k]交换
			a[i]=a[k]; a[k]=tmp;
		}
		SelectSort(a,n,i+1);
	}
}
void main()
{	int n=10;
	int a[]={2,5,1,7,10,6,9,4,3,8};
	printf("排序前:"); disp(a,n);
	SelectSort(a,n,0);
	printf("排序后:"); disp(a,n);
}
