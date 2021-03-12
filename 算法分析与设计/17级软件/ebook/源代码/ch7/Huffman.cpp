#pragma warning(disable:4786)
#include <iostream>
#include <queue>
#include <vector>
#include <string>
#include <map>
using namespace std; 
#define MAX 101
int n;
struct HTreeNode				//哈夫曼树结点类型
{
	char data;					//字符
	int weight;					//权值
	int parent;					//双亲的位置
	int lchild;					//左孩子的位置
	int rchild;					//右孩子的位置
};
HTreeNode ht[MAX];				//哈夫曼树
map<char,string> htcode;			//哈夫曼编码

struct NodeType		//优先队列结点类型
{
	int no;				//对应哈夫曼树ht中的位置
	char data;			//字符
	int  weight;		//权值
	bool operator<(const NodeType &s) const
	{					//用于创建小根堆
		return s.weight<weight;
	}
};
void CreateHTree()						//构造哈夫曼树
{
	NodeType e,e1,e2;
	priority_queue<NodeType> qu;
	for (int k=0;k<2*n-1;k++)	//设置所有结点的指针域
		ht[k].lchild=ht[k].rchild=ht[k].parent=-1;
	for (int i=0;i<n;i++)				//将n个结点进队qu
	{
		e.no=i;
		e.data=ht[i].data;
		e.weight=ht[i].weight;
		qu.push(e);
	}
	for (int j=n;j<2*n-1;j++)			//构造哈夫曼树的n-1个非叶结点
	{
		e1=qu.top();  qu.pop();		//出队权值最小的结点e1
		e2=qu.top();  qu.pop();		//出队权值次小的结点e2
		ht[j].weight=e1.weight+e2.weight; //构造哈夫曼树的非叶结点j	
		ht[j].lchild=e1.no;
		ht[j].rchild=e2.no;
		ht[e1.no].parent=j;			//修改e1.no的双亲为结点j
		ht[e2.no].parent=j;			//修改e2.no的双亲为结点j
		e.no=j;						//构造队列结点e
		e.weight=e1.weight+e2.weight;
		qu.push(e);
	}
}
void CreateHCode()			//构造哈夫曼编码
{
	string code;
	code.reserve(MAX);
	for (int i=0;i<n;i++)	//构造叶结点i的哈夫曼编码
	{
		code="";
		int curno=i;
		int f=ht[curno].parent;
		while (f!=-1)				//循环到根结点
		{
			if (ht[f].lchild==curno)	//curno为双亲f的左孩子
				code='0'+code;
			else					//curno为双亲f的右孩子
				code='1'+code;
			curno=f; f=ht[curno].parent;
		}
		htcode[ht[i].data]=code;	//得到ht[i].data字符的哈夫曼编码
	}
}
void DispHCode()					//输出哈夫曼编码
{
	map<char,string>::iterator it;
	for (it=htcode.begin();it!=htcode.end();++it)
		cout << "    " << it->first << ": " << it->second <<	endl;
}
void DispHTree()					//输出哈夫曼树
{
	for (int i=0;i<2*n-1;i++)
	{
		printf("    data=%c, weight=%d, lchild=%d, rchild=%d, parent=%d\n",
			ht[i].data,ht[i].weight,ht[i].lchild,ht[i].rchild,ht[i].parent);
	}
}
int WPL()				//求WPL
{
	int wps=0;
	for (int i=0;i<n;i++)
		wps+=ht[i].weight*htcode[ht[i].data].size();
	return wps;
}

void main()
{
	n=5;
	ht[0].data='a'; ht[0].weight=4;		//置初值即n个叶子结点
	ht[1].data='b'; ht[1].weight=2;  
	ht[2].data='c'; ht[2].weight=1;  
	ht[3].data='d'; ht[3].weight=7;  
	ht[4].data='e'; ht[4].weight=3;  
	CreateHTree();					//建立哈夫曼树
	printf("构造的哈夫曼树:\n");
	DispHTree();
	CreateHCode();					//求哈夫曼编码
	printf("产生的哈夫曼编码如下:\n");
	DispHCode();					//输出哈夫曼编码
	printf("WPL=%d\n",WPL());
}
