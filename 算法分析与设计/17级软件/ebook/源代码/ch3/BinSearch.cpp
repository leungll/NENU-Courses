//递归和非递归折半查找算法
#include <stdio.h>
int BinSearch(int a[],int low,int high,int k) //拆半查找算法
{	int mid;
	if (low<=high)				//当前区间存在元素时
	{	mid=(low+high)/2;		//求查找区间的中间位置
		if (a[mid]==k)			//找到后返回其物理下标mid
			return mid;
		if (a[mid]>k)			//当a[mid]>k时,在a[low..mid-1]中递归查找
			return BinSearch(a,low,mid-1,k);
		else					//当a[mid]<k时,在a[mid+1..high]中递归查找
			return BinSearch(a,mid+1,high,k);
	}
	else	return -1;			//若当前查找区间没有元素时返回-1
}
int BinSearch1(int a[],int n,int k)	//非递归拆半查找算法
{	int low=0,high=n-1,mid;
	while (low<=high)			//当前区间存在元素时循环
	{	mid=(low+high)/2;		//求查找区间的中间位置
		if (a[mid]==k)			//找到后返回其物理下标mid
			return mid;
		if (a[mid]>k)			//继续在a[low..mid-1]中查找
			high=mid-1;
		else					//a[mid]<k
			low=mid+1;			//继续在a[mid+1..high]中查找
	}
	return -1;					//若当前查找区间没有元素时返回-1
}
void main()
{	int n=10,i;
	int k=6;
	int a[]={1,2,3,4,5,6,7,8,9,10};
	i=BinSearch(a,0,n-1,k);
	if (i>=0)	printf("a[%d]=%d\n",i,k);
	else printf("未找到%d元素\n",k);
}
