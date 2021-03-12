#include <stdio.h>
int BinSearch(int a[],int n,int x,int &i,int &j) 
{
	int mid,low,high;
	low=0; high=n-1;
	while(low<=high)		//当前区间含有一个或者以上的元素时
	{
		mid=(high+low)/2;
		if(x==a[mid])		//找到为x的元素a[mid]
		{
			i=j=mid;
			return mid; 
		}
		
		if(x<a[mid])
			high=mid-1;
		else
			low=mid+1;
	}
	i=high; j=low;			//对应失败结点为a[high..low](有low>high)
	return -1;
}
int BinSearch1(int a[],int n,int x)
{
	int mid,low=0,high=n-1;
	while (low<high)		//区间存在一个以上的元素
	{
		mid=(low+high)/2;
		if (x<=a[mid])
			high=mid;
		else
			low=mid+1;
	}
	if (low>high)			//区间为空，没有找到x
		return -1;
	else if(a[low]!=x)		//区间不空，一个元素不为x
		return -1;
	else					//区间不空，一个元素恰好为x
		return low;
}
int BinSearch2(int a[],int n,int x)
{
	int mid,low=0,high=n-1;
	while (low<high)		//区间存在一个以上的元素
	{
		mid=(low+high+1)/2;
		if (x>=a[mid])
			low=mid;
		else
			high=mid-1;
	}
	printf("low=%d,high=%d\n",low,high);
	if (low>high) return -1;
	else if(a[low]!=x)
		return -1;
	else
		return low;
}
int main() 
{
	int i,j,ret;
	int x=2 ;
	int a[]={1,2,2,4,5,5};
	int n=sizeof(a)/sizeof(a[0]);
	ret=BinSearch2(a,n,x);
	printf("ret=%d\n",ret);
	return 0;
} 