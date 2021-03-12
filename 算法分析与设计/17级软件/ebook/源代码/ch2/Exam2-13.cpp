//Àý2.13
#include <stdio.h>
int Zeronum(int n)
{
	if (n>0 && n<5)
		return 0;
	else
	{
		int k=n/5;
		return k+Zeronum(k);
	}
}
long fun(int n)
{
	long p=1;
	for (int i=2;i<=n;i++)
		p=p*i;
	return p;
}


void main()
{
	int n=11;
	printf("%ld\n",fun(n));
	printf("%d\n",Zeronum(n));
}
