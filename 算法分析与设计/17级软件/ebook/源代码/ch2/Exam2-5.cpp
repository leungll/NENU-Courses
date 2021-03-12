//Àý2.5
#include <stdio.h>
int fmax(int a[],int i)
{	if (i==1)
		return a[0];
	else
		return(fmax(a,i-1),a[i-1]);
}
void main()
{
	int a[]={1,2,3,4,5};
	printf("fmax=%d\n",fmax(a,5));
}