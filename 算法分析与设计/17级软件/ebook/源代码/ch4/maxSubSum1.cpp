//求解最大连续子序列和问题-解法1
#include <stdio.h>
int maxSubSum1(int a[],int n)		//求a的最大连续子序列和
{	int i,j,k;
	int maxSum=0,thisSum; 
	for (i=0;i<n;i++)				//两重循环穷举所有的连续子序列
	{	for (j=i;j<n;j++)
		{	thisSum=0;
			for (k=i;k<=j;k++)
				thisSum+=a[k];
			if (thisSum>maxSum)	//通过比较求最大连续子序列之和
				maxSum=thisSum;
		}
	}
	return maxSum;
}
void main()
{
	int a[]={-2,11,-4,13,-5,-2};
	int n=sizeof(a)/sizeof(a[0]);
	int b[]={-6,2,4,-7,5,3,2,-1,6,-9,10,-2};
	int m=sizeof(b)/sizeof(b[0]);
	printf("a序列的最大连续子序列的和:%ld\n",maxSubSum1(a,n));
	printf("b序列的最大连续子序列的和:%ld\n",maxSubSum1(b,m));
}
