#include <stdio.h>
#include <queue>
#include <vector>
#include <algorithm>
using namespace std;
#define N 100
//问题表示
int n=7;
int m=3;
struct NodeType
{
	int no;							//作业序号
    int t;							//执行时间
	int mno;						//机器序号
	bool operator<(const NodeType &s) const 
	{	return t>s.t;  }				//按t越小越优先出队
};
struct NodeType A[]={{1,2},{2,14},{3,4},{4,16},{5,6},{6,5},{7,3}};
void solve()							//求解多机调度问题
{
	NodeType e;
	if (n<=m)
	{	printf("为每一个作业分配一台机器\n");
		return;
	}
	sort(A,A+n);
	priority_queue<NodeType> qu;		//小根堆
	for (int i=0;i<m;i++)
	{
		A[i].mno=i+1;
		printf("  给机器%d分配作业%d,执行时间为%2d,占用时间段:[%d,%d]\n",
				A[i].mno,A[i].no,A[i].t,0,A[i].t);
		qu.push(A[i]);
	}
	for (int j=m;j<n;j++)
	{
		e=qu.top(); qu.pop();			//出队e
		printf("  给机器%d分配作业%d,执行时间为%2d,占用时间段:[%d,%d]\n",
				e.mno,A[j].no,A[j].t,e.t,e.t+A[j].t);
		e.t+=A[j].t;
		qu.push(e);						//e进队
	}
}
void main()
{
	printf("多机调度方案:\n");
	solve();
}
