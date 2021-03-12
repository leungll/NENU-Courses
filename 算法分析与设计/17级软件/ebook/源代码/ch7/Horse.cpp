#include <stdio.h>
#include <algorithm>
using namespace std;
#define MAX 1001
//问题表示
int n;
int a[MAX];
int b[MAX];
//求解结果表示
int ans;
void solve()					//求解算法
{
	sort(a,a+n);				//对a递增排序
	sort(b,b+n);				//对b递增排序
	ans=0;
	int lefta=0,leftb=0;
	int righta=n-1,rightb=n-1;
	while (lefta<=righta)		//比赛直到结束
	{
		if (a[righta]>b[rightb])	//田忌最快的马比齐威王最快的马快，两者比赛
		{
			ans+=200;
			righta--;
			rightb--;
		}
		else if (a[righta]<b[rightb])	//田忌最快的马比齐威王最快的马慢，选择田忌最慢的马与比齐威王最快的马比赛
		{
			ans-=200;
			lefta++;
			rightb--;
		}
		else						//田忌最快的马与齐威王最快的马的速度相同
		{
			if (a[lefta]>b[leftb])	//田忌最慢的马比齐威王最慢的马快，两者比赛
			{
				ans+=200;
				lefta++;
				leftb++;
			}
			else
			{
				if (a[lefta]<b[rightb])	//否则，用田忌最慢的马与齐威王最快的马比赛
					ans-=200;
				lefta++;
				rightb--;
			}
		}
	}
}
int main()
{
	while (true)
	{
		scanf("%d",&n);
		if (n==0) break;
		for (int i=0;i<n;i++)
			scanf("%d",&a[i]);
		for (int j=0;j<n;j++)
			scanf("%d",&b[j]);
		solve();
		printf("%d\n",ans);
	}
	return 0;
}
