//二路归并排序算法
#include <stdio.h>
#include <malloc.h>
void disp(int a[],int n)			//输出a中所有元素
{	int i;
	for (i=0;i<n;i++)
		printf("%d ",a[i]);
	printf("\n");
}
void Merge(int a[],int low,int mid,int high)
//将a[low..mid]和a[mid+1..high]两个相邻的有序子序列归并为一个有序子序列a[low..high]
{	int *tmpa;
	int i=low,j=mid+1,k=0;		//k是tmpa的下标,i、j分别为两个子表的下标
	tmpa=(int *)malloc((high-low+1)*sizeof(int));  //动态分配空间
	while (i<=mid && j<=high)	//在第1子表和第2子表均未扫描完时循环
		if (a[i]<=a[j])		//将第1子表中的元素放入tmpa中
		{	tmpa[k]=a[i];
			i++;k++; 
		}
		else					//将第2子表中的元素放入tmpa中
		{	tmpa[k]=a[j];
			j++;k++; 
		}
	while (i<=mid)			//将第1子表余下部分复制到tmpa
	{	tmpa[k]=a[i];
		i++;k++; 
	}
	while (j<=high)			//将第2子表余下部分复制到tmpa
	{	tmpa[k]=a[j];
		j++;k++;
	}
	for (k=0,i=low;i<=high;k++,i++) 		//将tmpa复制回a中
		a[i]=tmpa[k];
	free(tmpa);						//释放tmpa所占内存空间
}
void MergePass(int a[],int length,int n)	//一趟二路归并排序
{	int i;
	for (i=0;i+2*length-1<n;i=i+2*length)	//归并length长的两相邻子表
		Merge(a,i,i+length-1,i+2*length-1);
	if (i+length-1<n)					//余下两个子表,后者长度小于length
		Merge(a,i,i+length-1,n-1);		//归并这两个子表
}
void MergeSort(int a[],int n)			//二路归并算法
{	int length;
	for (length=1;length<n;length=2*length)
		MergePass(a,length,n);
}
void main()
{	int n=10;
	int a[]={2,5,1,7,10,6,9,4,3,8};
	printf("排序前:"); disp(a,n);
	MergeSort(a,n);
	printf("排序后:"); disp(a,n);
}
