//不带头结点的单链表的基本运算算法
#include <stdio.h>
#include <malloc.h>
typedef int ElemType;
typedef struct Node
{	ElemType data;
	struct Node *next;
} LinkNode;					//单链表结点类型

void CreateList(LinkNode *&L,ElemType a[],int n)	//由a[0..n-1]创建单链表L
{
	LinkNode *p, *r;
	L=(LinkNode *)malloc(sizeof(LinkNode));
	L->data=a[0];
	r=L;					//r指向当前尾结点
	for (int i=1;i<n;i++)
	{
		p=(LinkNode *)malloc(sizeof(LinkNode));
		p->data=a[i];
		r->next=p;
		r=p;
	}
	r->next=NULL;			//尾结点next域置为空
}
void DispList(LinkNode *L)	//输出单链表L
{
	LinkNode *p=L;
	while (p!=NULL)
	{
		printf("%d ",p->data);
		p=p->next;
	}
	printf("\n");
}
void Release(LinkNode *&L)	//销毁单链表L:对应例2.6的算法
{
	if (L!=NULL)
	{
		Release(L->next);
		free(L);
	}
}
