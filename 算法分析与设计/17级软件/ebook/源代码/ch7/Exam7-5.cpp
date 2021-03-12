#pragma warning(disable:4786)
#include <iostream>
#include <queue>
#include <vector>
#include <string>
#include <map>
using namespace std; 
#define MAX 101
//问题表示
int n;					//叶结点个数
string str;				//字符串
//求解结果表示
struct HTreeNode		//哈夫曼树结点类型
{
	char data;			//字符
	int weight;			//权值
	int parent;			//双亲的位置
	int lchild;			//左孩子的位置
	int rchild;			//右孩子的位置
};
HTreeNode ht[MAX];				//哈夫曼树
map<char,string> htcode;			//哈夫曼编码

struct NodeType				//优先队列结点类型
{
	int no;					//对应哈夫曼树A中的位置
	char data;				//字符
	int  weight;			//权值
	bool operator<(const NodeType &s) const
	{						//用于创建小根堆
		return s.weight<weight;
	}
};
void Init()							//初始化哈夫曼树
{
	int i;
	map<char,int> mp;
	for (i=0;i<str.length();i++)	//累计str中各个字符的出现次数
		mp[str[i]]++;
	n=mp.size();
	map<char,int>::iterator it;
	i=0;
	for (it=mp.begin();it!=mp.end();++it)	//设置叶结点的data和weight
	{
		ht[i].data=it->first;
		ht[i].weight=it->second;
		i++;
	}
	for (int j=0;j<2*n-1;j++)	//设置所有结点的指针域
		ht[j].lchild=ht[j].rchild=ht[j].parent=-1;

}
void CreateHTree()				//构造哈夫曼树
{
	NodeType e,e1,e2;
	priority_queue<NodeType> qu;
	for (int i=0;i<n;i++)		//将n个结点进队qu
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
		while (f!=-1)
		{
			if (ht[f].lchild==curno)	//curno为双亲f的左孩子
				code='0'+code;
			else					//curno为双亲f的右孩子
				code='1'+code;
			curno=f; f=ht[curno].parent;
		}
		htcode[ht[i].data]=code;		
	}
}
void DispHCode()					//输出哈夫曼编码
{
	map<char,string>::iterator it;
	for (it=htcode.begin();it!=htcode.end();++it)
		cout << "\t" << it->first << ": " << it->second <<	endl;
}
void EnCode(string str,string &enstr)			//编码字符串str得到enstr
{
	for (int i=0;i<str.length();i++)
		enstr = enstr+htcode[str[i]];
}
void DeCode(string enstr,string &destr)			//解码字符串enstr得到destr
{
	int r=2*n-2,p;								//哈夫曼树的根结点为ht[2*n-2]结点
	int i=0;
	while (i<enstr.length())
	{
		p=r;
		while (true)
		{
			if (enstr[i]=='0')
				p=ht[p].lchild;
			else
				p=ht[p].rchild;
			if (ht[p].lchild==-1 && ht[p].rchild==-1)	//p为叶结点
				break;							//找到对应的字符
			i++;
		}
		destr=destr+ht[p].data;					//在解码字符串中添加ht[p].data
		i++;
	}
}
void main()
{
	str="The following code computes the intersection of two arrays.";
	Init();
	CreateHTree();
	CreateHCode();
	cout << "哈夫曼编码:" << endl;
	DispHCode();
	string enstr="";
	EnCode(str,enstr);
	cout << "编码结果:" << endl;
	cout << enstr << endl;
	string destr="";
	DeCode(enstr,destr);
	cout << "解码结果:" << endl;
	cout << destr << endl;
}
