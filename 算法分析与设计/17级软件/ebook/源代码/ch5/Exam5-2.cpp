//例5.2的算法
#include <stdio.h>
#include <string.h>
void fun()
{	bool dig[10];
	int a,b,c,d,e,m,n,s;
	memset(dig,0,sizeof(dig));;	//置初值0表示所有数字均没有使用
	for (a=1;a<=9;a++)
	{	dig[a]=1;					//试探兵取值a
		for (b=0;b<=9;b++)
			if (!dig[b])
			{	dig[b]=1;				//试探炮取值b
				for (c=0;c<=9;c++)
					if (!dig[c])
					{	dig[c]=1;			//试探马取值c
						for (d=0;d<=9;d++)
							if (!dig[d])
							{	dig[d]=1;		//试探卒取值d
								for (e=0;e<=9;e++)
									if (!dig[e]) 
									{	dig[e]=1;		//试探车取值e
										m=a*1000+b*100+c*10+d;
										n=a*1000+b*100+e*10+d;
										s=e*10000+d*1000+c*100+a*10+d;
										if (m+n==s)
											printf("兵:%d 炮:%d 马:%d 卒:%d 车:%d\n",a,b,c,d,e);
										dig[e]=0;		//回溯车的取值
									}
									dig[d]=0;	//回溯卒的取值
							}
							dig[c]=0;		//回溯马的取值
					}
					dig[b]=0;		//回溯炮的取值
			}
			dig[a]=0;	//回溯兵的取值
	}
}
void main()
{
	fun();
}
