//递归求解全排列问题
#include <stdio.h>
#include <vector>
using namespace std;
vector<vector<int> > ps;						//存放全排列
void Insert(vector<int> s,int i,vector<vector<int> > &ps1)
//在每个集合元素中间插入i得到ps1
{	vector<int> s1;
	vector<int>::iterator it;
	for (int j=0;j<i;j++)						//在s(含i-1个整数)的每个位置插入i
	{	s1=s;
		it=s1.begin()+j;						//求出插入位置
		s1.insert(it,i);						//插入整数i
		ps1.push_back(s1);						//添加到ps1中
	}
}
void Perm(int i,int n)					//求1～n的全排列ps
{
	vector<vector<int> >::iterator it;			//全排列迭代器
	if (i<=n)
	{
		vector<vector<int> > ps1;				//临时存放子排列
		for (it=ps.begin();it!=ps.end();++it)
			Insert(*it,i,ps1);			//在每个集合元素中间插入i得到ps1
		ps=ps1;
		Perm(i+1,n);					//继续添加整数i+1
	}
}
void dispps()									//输出全排列ps
{	vector<vector<int> >::reverse_iterator it;	//全排列的反向迭代器
	vector<int>::iterator sit;					//排列集合元素迭代器
	for (it=ps.rbegin();it!=ps.rend();++it)
	{	for (sit=(*it).begin();sit!=(*it).end();++sit)
			printf("%d",*sit);
		printf("  ");
	}
	printf("\n");
}
void main()
{
	int n=3;
	printf("1～%d的全排序如下:\n  ",n);
	vector<int> s;
	s.push_back(1);
	ps.push_back(s);			//初始化ps为{{1}}
	Perm(2,n);
	dispps();
}
