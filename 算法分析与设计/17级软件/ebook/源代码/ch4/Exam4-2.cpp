//Àý4.2
#include <stdio.h>
void main()
{	int n,a,b;
	for (a=0;a<=9;a++)
		for (b=0;b<=9;b++) 
		{	n=1000*a+100*b+10+2;
			if ((n-7)%7==0 && (n-8)%8==0 && (n-9)%9==0)
			{	printf("n=%d\n",n);
				break;
			}
		}
}
