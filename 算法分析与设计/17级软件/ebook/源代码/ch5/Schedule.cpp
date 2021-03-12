#include <stdio.h>
#include <string.h>
#define INF 0x3f3f3f3f					//最大整数∞
#define MAX 1001						//最多的作业数
#define max(x,y) ((x)>(y)?(x):(y))
//问题表示
int n=4;								//作业数
int a[MAX]={0,5,12,4,8};				//M1上的执行时间,不用下标0的元素
int b[MAX]={0,6,2,14,7};				//M2上的执行时间,不用下标0的元素
//求解结果表示
int bestf;							//存放最优调度时间
int f1;								//M1的执行时间
int f2[MAX];							//M2的执行时间
int x[MAX];							//当前调度方案
int bestx[MAX];						//存放当前作业最佳调度
void swap(int &x,int &y)				//交换x和y
{	int tmp=x;
	x=y; y=tmp;
}
void disparr(int x[])					//输出一个数组的元素
{	for (int i=1;i<=n;i++)
		printf("%d ",x[i]);
}
void dfs(int i)						//从第i层开始搜索
{	if (i>n)							//到达叶结点,产生一种调度方案
    {	if (f2[n]<bestf)				//找到更优解
		{	bestf=f2[n];
			printf("   一个解: bestf=%d",bestf);
			printf(", 调度方案: "); disparr(x);
			printf(", f2: "); disparr(f2);
			printf("\n");
			for(int j=1; j<=n; j++)		//复制解向量
				bestx[j] = x[j];  
		}
	}
	else
	{	for(int j=i; j<=n; j++)			//没有到达叶结点,考虑i到n的作业
		{	f1 += a[x[j]];				//在第i层选择执行作业x[j],在M1上执行完的时间
			f2[i]=max(f1,f2[i-1])+b[x[j]];
			if (f2[i]<bestf)			//剪枝:仅仅扩展当前总时间小于bestf的结点
			{	swap(x[i],x[j]);
				dfs(i+1);
				swap(x[i],x[j]);
			}
			f1 -= a[x[j]];	//回溯，即撤销第i层对作业x[j]的选择,以便再选择其他作业
		}
	}
}
int main()
{	f1=0;
	bestf=INF;
	memset(f2,0,sizeof(f2));
	for(int k=1; k<=n; k++)  	//设置初始调度为作业1,2,…,n的顺序
		x[k]=k;
	printf("求解过程:\n");
	dfs(1);					//从作业1开始搜索
	printf("求解结果:\n");
	printf("    最少时间: %d",bestf);
	printf(", 最优调度方案: ");
	disparr(bestx); printf("\n");
	return 0;
}
