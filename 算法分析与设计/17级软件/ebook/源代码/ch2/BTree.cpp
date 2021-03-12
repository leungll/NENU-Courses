//二叉树的基本运算算法+例2.8到例2.11
#include <malloc.h>
#include <stack>
#include <vector>
#include <string>
using namespace std;
typedef int ElemType;
typedef struct node 
{	ElemType data;				//数据元素
	struct node *lchild;		//指向左孩子结点
	struct node *rchild;		//指向右孩子结点
} BTNode;						//二叉链结点类型

BTNode *CreateBTree(ElemType a[],ElemType b[],int n)	//对应例2.8的算法
//由先序序列a[0..n-1]和中序序列b[0..n-1]建立二叉链
{
	int k;
	if (n<=0) return NULL;
	ElemType root=a[0];			//根结点值
	BTNode *bt=(BTNode *)malloc(sizeof(BTNode));
	bt->data=root;
	for (k=0;k<n;k++)			//在b中查找b[k]=root的根结点
		if (b[k]==root)
			break;
	bt->lchild=CreateBTree(a+1,b,k);			//递归创建左子树
	bt->rchild=CreateBTree(a+k+1,b+k+1,n-k-1);	//递归创建右子树
	return bt;
}
void DispBTree(BTNode *bt)				//采用括号表示输出二叉链bt
{
	if (bt!=NULL)
	{	printf("%d",bt->data);
		if (bt->lchild!=NULL || bt->rchild!=NULL)
		{	printf("(");						//有孩子结点时才输出(
			DispBTree(bt->lchild);				//递归处理左子树
			if (bt->rchild!=NULL) printf(",");	//有右孩子结点时才输出,
			DispBTree(bt->rchild);				//递归处理右子树
			printf(")");						//有孩子结点时才输出)
		}
	}
}
void DestroyBTree(BTNode *&bt)		//对应例2.9的算法
//释放以bt为根结点的二叉树
{	if (bt!=NULL)
	{	DestroyBTree(bt->lchild);
		DestroyBTree(bt->rchild);
		free(bt);
	}
}
void CopyBTree(BTNode *bt,BTNode *&bt1)	//对应例2.10的算法
//由二叉树bt复制产生bt1
{
	if (bt==NULL)
		bt1=NULL;
	else
	{
		bt1=(BTNode *)malloc(sizeof(BTNode));
		bt1->data=bt->data;
		CopyBTree(bt->lchild,bt1->lchild);
		CopyBTree(bt->rchild,bt1->rchild);
	}
}
bool Findxpath1(BTNode *bt,int x,vector<int> &path)			//对应例2.11的解法1
//求根结点到x结点的（逆向）路径
{
	if (bt==NULL)					//空树返回false
		return false;
	if (bt->data==x)				//找到值为x的结点
	{
		path.push_back(x);			//结点值加入path中，并返回true
		return true;
	}
	else if (Findxpath1(bt->lchild,x,path) || Findxpath1(bt->rchild,x,path))
	{
		path.push_back(bt->data);	//结点值加入path中，并返回true
		return true;
	}
}
bool Findxpath2(BTNode *bt,int x,vector<int> tmppath,vector<int> &path)	//对应例2.11的解法2
//求根结点到x结点的（正向）路径
{
	if (bt==NULL)							//空树返回false
		return false;
	tmppath.push_back(bt->data);			//当前结点加入path
	if (bt->data==x)						//当前结点值为x，返回true
	{
		path=tmppath;
		return true;
	}
	bool find=Findxpath2(bt->lchild,x,tmppath,path);//在左子树中查找
	if (find)								//左子树中成功找到
		return true;
	else									//左子树中没有找到，在右子树中查找
		return Findxpath2(bt->rchild,x,tmppath,path);
}
