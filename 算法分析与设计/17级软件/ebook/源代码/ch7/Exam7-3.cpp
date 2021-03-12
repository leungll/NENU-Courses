#include <stdio.h>
#include <algorithm>
using namespace std;
#define MAX 40001
//问题表示
int n;
struct NodeType  
{	int b;   					//区间首部
    	int e;   					//区间尾部
	bool operator<(const NodeType &s) const
	{	if (e==s.e)
			return b<s.b;
		return e<s.e;			//按e递增排序
	}
} A[MAX];
//求解结果表示
int ans;
void solve()
{	int t,i;
	for (i=0; i<n; i++)
		if (A[i].b>A[i].e)			//交换首尾部,使首部小于尾部   
		{	t=A[i].b;
			A[i].b=A[i].e;
			A[i].e=t;
		}
	sort(A,A+n);					//排序
	int preend=A[0].e;
	ans=1;
	for(i=1; i<n; i++)
	{	if (A[i].b>preend)			//A[j]与前一个求解不相交
		{	ans++;
			preend=A[i].e;
		}
	}
	ans=n-ans;
}
int main()  
{	while(scanf("%d",&n)!=EOF)		//尽管题目中只有一个测试用例，但实际可以有多个
	{	for(int i=0; i<n; i++)
			scanf("%d%d",&A[i].b,&A[i].e);
		solve();
		printf("%d\n",ans); 
	}
    	return 0;
}
