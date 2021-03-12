//不带头结点的单链表的基本运算算法
#include "LinkList.cpp"		//包含不带头结点的单链表的基本运算算法
void Delallx(LinkNode *&L,ElemType x)	//删除L中所有结点值为x的结点
{
	LinkNode *p;
	if (L==NULL) return;
	if (L->data==x)
	{
		p=L;
		L=L->next;
		free(p);			//删除结点值为x的结点
		Delallx(L,x);		//此时L中减少了一个结点
	}
	else Delallx(L->next,x);
}
void main()
{
	LinkNode *L;
	int a[]={1,2,2,3,4,5,2};
	int n=sizeof(a)/sizeof(a[0]);
	CreateList(L,a,n);
	printf("L: "); DispList(L);
	int x=2;
	printf("删除所有值为%d的结点\n",x);
	Delallx(L,x);
	printf("L: "); DispList(L);
	printf("销毁L\n");
	Release(L);
}
