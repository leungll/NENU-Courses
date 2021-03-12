//求解简单装载问题
#include <stdio.h>
bool Loading(int W,int w[],int i)
{	int r;
	r=W-w[i];					//取w[i]后余下的重量
	if (r==0)					//找到后返回true
		return true;
	else if (r>0)				//余下重量大于0
	{	if (i>0)				//还存在没有找过的集装箱时
		{	if (Loading(r,w,i-1))	//在w[0..i-1]中找到解返回true
				return true;
			else				//否则舍弃w[i],在w[0..i-1]中找解
				return Loading(W,w,i-1);
		}
		else					//所有集装箱都找过且仍未找到解返回false
			return false;
	}
	else						//余下重量小于0
	{	if (i>0)				//还存在没有找过的集装箱时,舍弃w[i],在w[0..i-1]中找解
			return Loading(W,w,i-1);
		else					//所有集装箱都找过且仍未找到解返回false
			return false;
	}
}
void main()
{	int w[]={2,9,5,6,3};
	int n=5,W;
	W=4;
	printf("W=%d时%s\n",W,(Loading(W,w,n-1)?"存在解":"没有解"));
	W=10;
	printf("W=%d时%s\n",W,(Loading(W,w,n-1)?"存在解":"没有解"));
	W=12;
	printf("W=%d时%s\n",W,(Loading(W,w,n-1)?"存在解":"没有解"));
	W=21;
	printf("W=%d时%s\n",W,(Loading(W,w,n-1)?"存在解":"没有解"));
}
