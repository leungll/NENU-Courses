//Àý1.5
#include <stdio.h>
void MaxMin(int a[],int n,int &max,int &min)
{	int i;
	max=min=a[0];
	for (i=1;i<n;i++)
		if (a[i]>max) max=a[i];
		else if (a[i]<min) min=a[i];
}
void main()
{
	int a[]={2,1,5,6,4,3,8,9,7},max,min;
	int n=9;
	MaxMin(a,n,max,min);
	printf("Max=%d,Min=%d\n",max,min);
}
