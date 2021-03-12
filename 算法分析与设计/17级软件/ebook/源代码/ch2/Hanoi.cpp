//Hanoi问题的递归和非递归算法
#include <stdio.h>
#include <stack>
using namespace std;

void Hanoi(int n,char x,char y,char z)		//递归算法
{
	if (n==1)
		printf("\t将第%d个盘片从%c移动到%c\n",n,x,z);
	else
	{
		Hanoi(n-1,x,z,y);
		printf("\t将第%d个盘片从%c移动到%c\n",n,x,z);
		Hanoi(n-1,y,x,z);
	}
}

typedef struct
{	int n;			//保存n值
	char x,y,z;		//保存f(n)值
	int tag;		//标识是否求出f(n)值,1:未求出,0:已求出
} NodeType;			//栈元素类型

void Hanoi1(int n,char x,char y,char z)	//非递归算法
{
	NodeType e,e1,e2,e3;
	stack<NodeType> st;
	e.n=n;
	e.x=x; e.y=y; e.z=z;
	e.tag=1;
	st.push(e);					//初值进栈
	while (!st.empty())				//栈不空循环
	{
		if (st.top().tag==1)	//当不能直接操作时
		{
			e=st.top();
			st.pop();			//退栈hanoi(n,x,y,z)
			e1.n=e.n-1;
			e1.x=e.y; e1.y=e.x; e1.z=e.z;
			if (e1.n==1)		//只有一个盘片时直接操作
				e1.tag=0;
			else				//否则需要继续分解
				e1.tag=1;
			st.push(e1);		//子任务3：Hanoi(n-1,y,x,z)进栈
			e2.n=e.n;
			e2.x=e.x; e2.z=e.z;
			e2.tag=0;
			st.push(e2);		//子任务2：move(n,x,z)进栈
			e3.n=e.n-1;
			e3.x=e.x; e3.y=e.z; e3.z=e.y;
			if (e3.n==1)		//只有一个盘片时直接操作
				e3.tag=0;
			else				//否则需要继续分解
				e3.tag=1;
			st.push(e3);		//子任务1：Hanoi(n-1,x,z,y)进栈
		}
		else if	(st.top().tag==0)		//当可以直接操作时
		{
			printf("\t将第%d个盘片从%c移动到%c\n",st.top().n,st.top().x,st.top().z);
			st.pop();				//移动盘片后退栈
		}
	}
}
void main()
{
	int n=3;
	printf("n=%d时Hanoi(递归)的步骤如下:\n",n);
	Hanoi(3,'x','y','z');
	printf("n=%d时Hanoi(非递归)的步骤如下:\n",n);
	Hanoi1(3,'x','y','z');
}