//求解最大连续子序列和问题-解法3
#include <stdio.h>
int maxSubSum3(int a[],int n)		//求a的最大连续子序列和
{	int i,maxSum=0,thisSum=0;
	for (i=0;i<n;i++)
	{	thisSum+=a[i];
		if (thisSum<0)		//若当前子序列和为负数，则重新开始下一个子序列
			thisSum=0;
		if (maxSum<thisSum)	//比较求最大连续子序列和
			maxSum=thisSum;
	}
	return maxSum;
}
void main()
{
	int a[]={-2,11,-4,13,-5,-2};
	int n=sizeof(a)/sizeof(a[0]);
	int b[]={-6,2,4,-7,5,3,2,-1,6,-9,10,-2};
	int m=sizeof(b)/sizeof(b[0]);
	printf("a序列的最大连续子序列的和:%ld\n",maxSubSum3(a,n));	//输出:20
	printf("b序列的最大连续子序列的和:%ld\n",maxSubSum3(b,m));	//输出:16
}
