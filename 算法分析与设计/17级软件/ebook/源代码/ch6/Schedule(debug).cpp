#include <stdio.h>
#include <string.h>
#include <queue>
using namespace std;
#define max(x,y) ((x)>(y)?(x):(y))
#define INF 0x3f3f3f3f			//定义∞
#define MAX 21
//问题表示
int n=4;							//作业数
int a[MAX]={0,5,12,4,8};			//M1上的执行时间,不用下标0的元素
int b[MAX]={0,6,2,14,7};			//M2上的执行时间,不用下标0的元素

//int a[MAX]={0,5,10,9,7};			//M1上的执行时间,不用下标0的元素
//int b[MAX]={0,7,5, 9,8};			//M2上的执行时间,不用下标0的元素

//求解结果表示
int bestf=INF;						//存放最优调度时间
int bestx[MAX];						//存放当前作业最佳调度
int total=1;						//结点个数累计

struct NodeType					//队列结点类型
{
	int no;						//结点编号
	int x[MAX];					//x[i]表示第i步分配作业编号
	int y[MAX];					//y[i]=1表示编号为i的作业已经分配
	int i;						//步骤编号
	int f1;						//已经分配作业M1的执行时间
	int f2;						//已经分配作业M2的执行时间
	int lb;						//下界
	bool operator<(const NodeType &s) const	//重载<关系函数
	{
		return lb>s.lb;			//lb越小越优先出队
	}
};
void disp(NodeType node)
{
	printf("结点%d,e.i=%d,e.f1=%d,e.f2=%d,e.lb=%d, x: [",  node.no,node.i,node.f1,node.f2,node.lb);
	for (int i=1;i<n;i++)
		printf("%d,",node.x[i]);
	printf("%d]\n",node.x[n]);
}
void bound(NodeType &e)				//求结点e的限界值	
{
	int sum=0;
	for (int i=1;i<=n;i++)				//扫描所有作业
		if (e.y[i]==0) sum+=b[i];		//仅累计e.x中还没有分配的作业的b时间
	e.lb=e.f1+sum;
}
void bfs()								//求解流水作业调度问题
{
	NodeType e,e1;
	priority_queue<NodeType> qu;
	memset(e.x,0,sizeof(e.x));			//初始化根结点的x
	memset(e.y,0,sizeof(e.y));			//初始化根结点的y
	e.i=0;								//根结点
	e.f1=0;
	e.f2=0;
	bound(e);
	e.no=total++;
	qu.push(e);							//根结点进队列
	while (!qu.empty())
	{
		e=qu.top(); qu.pop();			//出队结点e
		printf("出队"); disp(e);
		if (e.i==n)						//达到叶子结点
		{
			if (e.f2<bestf)				//比较求最优解
			{
				bestf=e.f2;
				for (int j1=1;j1<=n;j1++)
					bestx[j1]=e.x[j1];
				printf("一个解:");disp(e);
			}
		}
		e1.i=e.i+1;							//扩展分配下一个步骤的作业，对应结点e1
		for (int j=1;j<=n;j++)				//考虑所有的n个作业
		{
			if (e.y[j]==1) continue;		//作业j是否已分配,若已分配，跳过
			for (int i1=1;i1<=n;i1++)		//复制e.x得到e1.x
				e1.x[i1]=e.x[i1];
			for (int i2=1;i2<=n;i2++)		//复制e.y得到e1.y
				e1.y[i2]=e.y[i2];
			e1.x[e1.i]=j;					//为第i步分配作业j
			e1.y[j]=1;						//表示作业j已经分配
			e1.f1=e.f1+a[j];				//求f1=f1+a[j]
			e1.f2=max(e.f2,e1.f1)+b[j];		//求f[i+1]=max(f2[i],f1)+b[j]
			bound(e1);
			if (e1.f2<=bestf)				//剪枝,剪去不可能得到更优解的结点
			{
				e1.no=total++;				//结点编号增加1
				printf("   进队(j=%d):",j); disp(e1);
				qu.push(e1);
			}
			else
			{
				printf("   不进队(j=%d):",j); disp(e1);
			}
		}
	}
}
void main()
{
	bfs();
	printf("最优方案:\n");
	for (int k=1;k<=n;k++)
		printf("   第%d步执行作业%d\n",k,bestx[k]);
	printf("   总时间=%d\n",bestf);
}






