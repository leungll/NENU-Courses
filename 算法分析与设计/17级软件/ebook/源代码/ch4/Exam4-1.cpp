//例4.1
#include <stdio.h>
void main()
{	int m,i,s;
	for (m=2;m<=1000;m++)
	{	s=0;
		for (i=1;i<=m/2;i++)
			if (m%i==0) s+=i;	//i是m的一个因子
		if (m==s)
			printf("%d ",m);
	}
	printf("\n");
}
