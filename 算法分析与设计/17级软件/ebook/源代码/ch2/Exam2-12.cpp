//Àý2.12
#include <stdio.h>
void digits(int n)
{
	if (n!=0)
	{
		digits(n/10);
		printf("%d",n%10);
	}
}

void main()
{
	int n=123;
	digits(n);
}