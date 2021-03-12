#include <stdio.h>
#define max(x,y) ((x)>(y)?(x):(y))
//问题表示
//int n=6;									//作业数
//int a[]={2,5,7,10,5,2};
//int b[]={3,8,4,11,3,4};

int n=3;											//任务数
int a[]={1,2,3};
int b[]={4,3,1};

//int a[]={1,3,2};
//int b[]={4,1,3};

//int a[]={2,1,3};
//int b[]={3,4,1};

//int a[]={2,3,1};
//int b[]={3,1,4};

//int a[]={3,1,2};
//int b[]={1,4,3};

//int a[]={3,2,1};
//int b[]={1,3,4};

//求解结构表示
int ans;
void solve()							//求解算法
{
	int k,sumA=0,sumB=0;
	for (k=1; k<=n; k++) 
	{
		sumA+=a[k-1];					//若在机器A中处理
		sumB+=b[k-1];					//若在机器B中处理
		if (sumA>sumB)
			sumA-=a[k-1];				//改为在机器B中处理
		else
			sumB-=b[k-1];				//改为在机器A中处理
	}
	ans=max(sumA,sumB);
} 
int main()
{
	solve();
	printf("%d\n",ans);
	return 0;
}
