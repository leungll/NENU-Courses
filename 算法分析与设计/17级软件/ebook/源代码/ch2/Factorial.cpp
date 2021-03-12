//求n!的递归和非递归算法
#include <stdio.h>
#include <stack>
using namespace std;

int fun(int n)				//求n!的递归算法
{	if (n==1)				//语句1
		return(1);			//语句2
	else					//语句3
		return(fun(n-1)*n);	//语句4
}

int fun1(int n)				//求n!的非递归算法
{
	int f=1,i;
	for (i=2;i<=n;i++)
		f=f*i;
	return(f);
}
typedef struct
{	int n;				//保存n值
	int f;				//保存f(n)值
	int tag;			//标识是否求出f(n)值,1:未求出,0:已求出
} NodeType;				//栈元素类型

int fun2(int n)			//n!的递归算法转换的非递归算法
{
	NodeType e,e1,e2;
	stack<NodeType> st;
	e.n=n;
	e.tag=1;
	st.push(e);							//初值进栈
	while (!st.empty())					//栈不空时循环
	{
		if (st.top().tag==1)			//未计算出栈顶元素的f值
		{
			if (st.top().n==1)			//(1)式
			{
				st.top().f=1;
				st.top().tag=0;
			}
			else						//(2)式分解过程
			{
				e1.n=st.top().n-1;
				e1.tag=1;
				st.push(e1);			//子任务(n-1)!进栈
			}
		}
		else 							//st.top().tag=0即已计算出f值
		{
			e2=st.top();
			st.pop();					//退栈e2
			st.top().f=st.top().n*e2.f;	//(2)式求值过程
			st.top().tag=0;				//表示栈顶元素的f值已求出
		}
		if (st.size()==1 && st.top().tag==0) //栈中只有一个已求出f的元素时退出循环
			break;
	}
	return(st.top().f);
}
void main()
{
	int n=6;
	printf(" fun的结果:fun(%d) =%d\n",n,fun(n));
	printf("fun1的结果:fun1(%d)=%d\n",n,fun1(n));
	printf("fun2的结果:fun2(%d)=%d\n",n,fun2(n));
}