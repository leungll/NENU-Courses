#include <stdio.h>
double solve(double a[],int n,double x)	//求多项式值的非递归算法
{	int i,j; 
	double p=0.0, p1;
	for (i=n;i>=0;i--)
	{	p1=1.0;
		for (j=1;j<=i;j++)
			p1*=x;
		p+=p1*a[i];
	}
	return p;
}

double Horner(double a[],int n,double x,int i)  //求多项式值的递归算法
{	if (i==0)
		return a[n];
	else
		return x*Horner(a,n,x,i-1)+a[n-i];
}


void main()
{
	double a[]={5,-2,3};
	int n=sizeof(a)/sizeof(a[0])-1;
	double x=0.5;
	printf("x=%g的结果:\n",x);
	printf("  P=%g\n",solve(a,n,x));
	printf("  P=%g\n",Horner(a,n,x,n));
	x=-0.2;
	printf("x=%g的结果:\n",x);
	printf("  P=%g\n",solve(a,n,x));
	printf("  P=%g\n",Horner(a,n,x,n));
}