//找第k小元素的算法
#include <stdio.h>
int QuickSelect(int a[],int s,int t,int k)	//在a[s..t]序列中找第k小的元素
{	int i=s,j=t;
	int tmp;
	if (s<t) 					//区间内至少存在2个元素的情况
	{	tmp=a[s];				//用区间的第1个记录作为基准
		while (i!=j)			//从区间两端交替向中间扫描,直至i=j为止
		{	while (j>i && a[j]>=tmp) 
				j--;			//从右向左扫描,找第1个关键字小于tmp的a[j]
			a[i]=a[j];			//将a[j]前移到a[i]的位置
			while (i<j && a[i]<=tmp) 
				i++;			//从左向右扫描,找第1个关键字大于tmp的a[i]
			a[j]=a[i];			//将a[i]后移到a[j]的位置
		}
		a[i]=tmp;
		if (k-1==i) return a[i];
		else if (k-1<i) return QuickSelect(a,s,i-1,k);	//在左区间中递归查找
		else return QuickSelect(a,i+1,t,k);				//在右区间中递归查找
	}
	else if (s==t && s==k-1)	//区间内只有一个元素且为a[k-1]
		return a[k-1];
}
void main()
{	int n=10,k;
	int e;
	int a[]={2,5,1,7,10,6,9,4,3,8};
	for (k=1;k<=n;k++)
	{	e=QuickSelect(a,0,n-1,k);
		printf("第%d小的元素:%d\n",k,e);
	}
}
