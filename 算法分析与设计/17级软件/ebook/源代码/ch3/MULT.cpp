//求解大整数乘法的算法
#include <stdio.h>
#include <math.h>
#define MAXN 20				//最多的位数
void Left(int A[],int B[],int n)	//取A的左边（高位）n/2位
{	int i;
	for (i=0;i<MAXN;i++)
		B[i]=0;
	for (i=n/2;i<=n;i++)
		B[i-n/2]=A[i];
}
void Right(int A[],int B[],int n)//取A的右边（低位）n/2位
{	int i;
	for (i=0;i<MAXN;i++)
		B[i]=0;
	for (i=0;i<n/2;i++)
		B[i]=A[i];
	B[i]='\0';
}
long Trans2to10(int A[])		//二进制数转换成十进制数
{	int i;
	long s=A[0],x=1;
	for (i=1;i<MAXN;i++)
	{	x=2*x;
		s+=A[i]*x;
	}
	return s;
}
void Trans10to2(int x,int A[])	//将十进数转换成二进制数
{	int i,j=0;
	while (x>0)
	{	A[j]=x%2;	j++;
		x=x/2;
	}
	for (i=j;i<MAXN;i++)
		A[i]=0;
}
void disp(int A[])		//从高位到低位输出二进制数A
{	int i;
	for (i=MAXN-1;i>=0;i--)
		printf("%d",A[i]);
	printf("\n");
}
void MULT(int X[],int Y[],int Z[],int n) //求Z=X*Y
{	int i;
	long e,e1,e2,e3,e4;
	int A[MAXN],B[MAXN],C[MAXN],D[MAXN];
	int m1[MAXN],m2[MAXN],m3[MAXN],m4[MAXN];
	for (i=0;i<MAXN;i++)	//Z初始化为0
		Z[i]=0;
	if (n==1)				//递归出口
	{	if (X[0]==1 && Y[0]==1)	Z[0]=1;
		else Z[0]=0;
	}
	else
	{	Left(X,A,n);		//A取X的左边n/2位
		Right(X,B,n);		//B取X的右边n/2位;
		Left(Y,C,n);		//C取Y的左边n/2位;
		Right(Y,D,n);		//D取Y的右边n/2位;
		MULT(A,C,m1,n/2);	//m1=AC
		MULT(A,D,m2,n/2);	//m2=AD
		MULT(B,C,m3,n/2);	//m3=BC
		MULT(B,D,m4,n/2);	//m4=DB
		e1=Trans2to10(m1);	//将m1转换成十进制数e1
		e2=Trans2to10(m2);	//将m2转换成十进制数e2
		e3=Trans2to10(m3);	//将m3转换成十进制数e3
		e4=Trans2to10(m4);	//将m4转换成十进制数e4
		e=e1*(int)pow(2,n)+(e2+e3)*(int)pow(2,n/2)+e4;
		Trans10to2(e,Z);	//将e转换成二进制数Z
	}
}
void trans(char a[],int n,int A[])	//将字符串a转换为整数数组A
{	int i;
	for (i=0;i<n;i++)
		A[i]=int(a[n-1-i]-'0');
	for (i=n;i<MAXN;i++)
		A[i]=0;
}
void main()
{	long e;
	char a[]="10101100";	//两个参与运算的二进制数
	char b[]="10010011";
	int X[MAXN],Y[MAXN],Z[MAXN];
	int n=8;
	trans(a,n,X);			//将a转换成整数数组X
	trans(b,n,Y);			//将b转换成整数数组Y
	printf("X:"); disp(X);	//输出X
	printf("Y:"); disp(Y);	//输出Y
	printf("Z=X*Y\n");
	MULT(X,Y,Z,n);		//求Z=X*Y
	printf("Z:"); disp(Z);	//输出Z
	e=Trans2to10(Z);		//将Z转换成十进制数e
	printf("Z对应的十进制数:%ld\n",e);
	printf("验证正确性:\n");
	long x,y,z;
	x=Trans2to10(X);		//将X转换成十进制数x
	y=Trans2to10(Y);		//将X转换成十进制数y
	printf("X对应的十进制数x:%ld\n",x);
	printf("Y对应的十进制数y:%ld\n",y);
	printf("z=x*y\n");
	z=x*y;				//求z=x*y
	printf("求解结果z:%d\n",z);
}
