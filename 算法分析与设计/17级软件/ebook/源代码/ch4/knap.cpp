//求解0/1背包问题
#include <stdio.h>
#include <vector>
using namespace std;
vector<vector<int> > ps;				//存放幂集
void PSet(int n)						//求1～n的幂集ps
{	vector<vector<int> > ps1;			//子幂集
	vector<vector<int> >::iterator it;	//幂集迭代器
	vector<int> s,s1;
	ps.push_back(s);					//添加{}空集合元素
	for (int i=1;i<=n;i++)				//循环添加1～n
	{	ps1=ps;						//ps1存放上一步得到的幂集
		for (it=ps1.begin();it!=ps1.end();++it)
			(*it).push_back(i);		//在ps1的每个集合元素末尾添加i
		for (it=ps1.begin();it!=ps1.end();++it)
			ps.push_back(*it);			//将ps1的每个集合元素添加到ps中
	}
}
void Knap(int w[],int v[],int W)	//求所有的方案和最佳方案
{
	int count=0;						//方案编号
	int sumw,sumv;						//当前方案的总重量和总价值
	int maxi,maxsumw=0,maxsumv=0;		//最优方案的编号、总重量和总价值
	vector<vector<int> >::iterator it;	//幂集迭代器
	vector<int>::iterator sit;			//幂集集合元素迭代器
	printf("  序号\t选中物品\t总重量\t总价值\t能否装入\n");
	for (it=ps.begin();it!=ps.end();++it)	//扫描ps中每一个集合元素
	{
		printf("  %d\t",count+1);
		sumw=sumv=0;
		printf("{");
		for (sit=(*it).begin();sit!=(*it).end();++sit)
		{	printf("%d ",*sit);
			sumw+=w[*sit-1];
			sumv+=v[*sit-1];
		}
		printf("}\t\t%d\t%d  ",sumw,sumv);
		if (sumw<=W)
		{	printf("能\n");
			if (sumv>maxsumv)		//比较求最优方案
			{	maxsumw=sumw;
				maxsumv=sumv;
				maxi=count;
			}
		}
		else printf("否\n");
		count++;
	}
	printf("最佳方案为: ");
	printf("选中物品");
	printf("{ ");
	for (sit=ps[maxi].begin();sit!=ps[maxi].end();++sit)
		printf("%d ",*sit);
	printf("},");
	printf("总重量:%d,总价值:%d\n",maxsumw,maxsumv);
}
void main()
{	int n=4,W=6;
	int w[]={5,3,2,1};
	int v[]={4,4,3,1};
	PSet(n);
	printf("0/1背包的求解方案\n",n);
	Knap(w,v,W);
}
