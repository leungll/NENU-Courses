#include <stdio.h>
#include <string.h>
#define MAX 101
//问题表示
int n=8,m=3;
int relation[][2]={{1,2},{2,3},{4,8}};		//朋友关系

//并查集的基本运算算法
typedef struct node
{	int data;							//结点对应顶点编号
	int rank;							//结点对应秩
	int parent;							//结点对应双亲下标
} UFSTree;								//并查集树的结点类型
void MAKE_SET(UFSTree t[],int n)		//初始化并查集树
{ 	for (int i=1;i<=n;i++)				//顶点编号为0～(n-1)
	{	t[i].rank=0;					//秩初始化为0
		t[i].parent=i;					//双亲初始化指向自已
	}
}
int FIND_SET(UFSTree t[],int x)			//在x所在子树中查找集合编号
{	if (x!=t[x].parent)					//若双亲不是自已
		return(FIND_SET(t,t[x].parent));	//递归在双亲中找x
	else
		return(x);						//若双亲是自已,返回x
}
void UNION(UFSTree t[],int x,int y)		//将x和y所在的子树合并
{	x=FIND_SET(t,x);
	y=FIND_SET(t,y);
	if (t[x].rank>t[y].rank)			//x结点的秩大于y结点的秩
		t[y].parent=x;				//将x结点作为y的双亲结点
	else								//y结点的秩大于等于x结点的秩
	{ 	t[x].parent=y;				//将y结点作为x的双亲结点
		if (t[x].rank==t[y].rank)		//x和y结点的秩相同
			t[y].rank++;				//y结点的秩增1
	}
}
int solve()						//求朋友圈个数
{
	int sum=0,i;
	UFSTree t[MAX];
	MAKE_SET(t,n);
	for (i=0;i<m;i++)
		UNION(t,relation[i][0],relation[i][1]);
	for(i=1;i<=n;i++)
		if (FIND_SET(t,i)==i && t[i].rank!=0)
			sum++;				//若顶点i的根为i并且其rank!=0,对应一个朋友圈
	return sum;
}
void main()
{
	printf("%d\n",solve());		//输出朋友圈个数
}
