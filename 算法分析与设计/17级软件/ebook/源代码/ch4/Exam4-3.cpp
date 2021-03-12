//Àý4.3
#include <stdio.h>
void fun()
{	int a,b,c,d,e,m,n,s;
	for (a=1;a<=9;a++)
		for (b=0;b<=9;b++)
			for (c=0;c<=9;c++)
				for (d=0;d<=9;d++)
					for (e=0;e<=9;e++)
						if (a==b || a==c || a==d || a==e || b==c || b==d 
								 || b==e || c==d || c==e || d==e) 
							continue;
						else
						{	m=a*1000+b*100+c*10+d;
							n=a*1000+b*100+e*10+d;
							s=e*10000+d*1000+c*100+a*10+d;
							if (m+n==s)
								printf("±ø:%d ÅÚ:%d Âí:%d ×ä:%d ³µ:%d\n",
									a,b,c,d,e);
						}
}
void main()
{
	fun();
}
