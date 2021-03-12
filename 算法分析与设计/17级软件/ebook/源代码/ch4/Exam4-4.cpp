//例4.4
#include <stdio.h>
#define max(x,y) ((x)>(y)?(x):(y))
#define max3(x,y,z) max(max(x,y),(z))	//求三个整数中的最大者
void solve(int a[],int n)
{	int i,j,k,len,ma,maxlen=0;
	for (i=0;i<n;i++)
		for (j=i+1;j<n;j++)
			for (k=j+1;k<n;k++)
			{	len=a[i]+a[j]+a[k];
				ma=max3(a[i],a[j],a[k]);
				if (ma<len-ma)		//a[i]、a[j]、a[k]能组成一个三角形
				{	if (len>maxlen)	//比较求最长的周长
						maxlen=len;
				}
			}
	if (maxlen>0)
		printf("最长三角形的周长=%d\n",maxlen);
	else
		printf("0\n");
}
void main()
{	int a[]={4,5,8,20};
	int n=4;
	solve(a,n);
}
