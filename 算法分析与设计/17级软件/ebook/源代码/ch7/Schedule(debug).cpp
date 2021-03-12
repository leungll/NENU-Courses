#include <stdio.h>
#include <algorithm> 
using namespace std;
#define max(x,y) ((x)>(y)?(x):(y))
#define N 100
//问题表示
int n=4;
int a[N]={5,12,4,8};				//对应M1的时间
int b[N]={6,2,14,7};				//对应M2的时间
struct NodeType
{
	int no;							//作业序号
    bool group;						//1代表第一组N1,0代表第二组N2
    int time;						//a,b的最小时间
	bool operator<(const NodeType &s) const
	{
		return time<s.time;			//按time递增排序
	}
};
//求解结果表示
int best[N];							//最优调度序列
void display(NodeType c[])
{
	int i;
	printf("c:\n");
	printf("作业号\t");
	for (i=0;i<n;i++)
		printf("%d\t",c[i].no);
	printf("\n");

	printf("M1时间\t");
	for (i=0;i<n;i++)
		printf("%d\t",a[c[i].no]);
	printf("\n");

	printf("M2时间\t");
	for (i=0;i<n;i++)
		printf("%d\t",b[c[i].no]);
	printf("\n");

	printf("组号\t");
	for (i=0;i<n;i++)
		printf("%d\t",c[i].group);
	printf("\n");

	printf("time\t");
	for (i=0;i<n;i++)
		printf("%d\t",c[i].time);
	printf("\n");
}
int solve()								//求解流水作业调度问题
{
	int i,j,k;
	NodeType c[N];
	for(i=0;i<n;i++)					//n个作业中,求出每个作业的最小加工时间 
	{
		c[i].no=i;
		c[i].group=(a[i]<=b[i]);		//a[i]<=b[i]对应第1组N1,a[i]>b[i]对应第0组N2
		c[i].time=a[i]<=b[i]?a[i]:b[i];	//第1组存放a[i],第0组存放b[i]
	}
	printf("排序前的c数组元素\n"); display(c);
	sort(c,c+n);						//c元素按time递增排序
	printf("排序后的c数组元素\n"); display(c);
	j=0; k=n-1;
	for(i=0;i<n;i++)					//扫描c所有元素,产生最优调度方案
	{
		if(c[i].group==1)				//第1组,按time递增排列放在best的前面部分
			best[j++]=c[i].no;
		else							//第0组,按time递减排列放到best的后面部分
			best[k--]=c[i].no;
	}
	int f1=0;						//累计M1上的执行时间
	int f2=0;							//最优调度下的消耗总时间
	for(i=0;i<n;i++)
	{
		f1+=a[best[i]];
		f2=max(f2,f1)+b[best[i]];
    }
	return f2;
}
void main()
{
	printf("求解结果\n");
	printf("    总时间: %d\n",solve());	//输出:33
	printf("    调度方案: ");
	for(int i=0;i<n;i++)
		printf("%d ",best[i]+1);		//输出:3 1 4 2
	printf("\n");
}

