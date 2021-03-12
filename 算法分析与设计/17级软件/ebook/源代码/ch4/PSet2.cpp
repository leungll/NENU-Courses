//求解幂集问题-解法2
#include <stdio.h>
#include <vector>
using namespace std;
vector<vector<int> > ps;				//存放幂集
void PSet(int n)						//求1～n的幂集ps
{
	vector<vector<int> > ps1;			//子幂集
	vector<vector<int> >::iterator it;	//幂集迭代器
	vector<int> s,s1;
	ps.push_back(s);				//添加{}
	for (int i=1;i<=n;i++)				//循环添加1～n
	{
		ps1=ps;
		for (it=ps1.begin();it!=ps1.end();++it)
			(*it).push_back(i);		//在ps1的每个集合元素末尾添加i
		for (it=ps1.begin();it!=ps1.end();++it)
			ps.push_back(*it);		//将ps1的每个集合元素添加到ps中
	}
}
void dispps()					//输出幂集ps
{
	vector<vector<int> >::iterator it;	//幂集迭代器
	vector<int>::iterator sit;			//幂集集合元素迭代器
	for (it=ps.begin();it!=ps.end();++it)
	{
		printf("{ ");
		for (sit=(*it).begin();sit!=(*it).end();++sit)
			printf("%d ",*sit);
		printf("} ");
	}
	printf("\n");
}
void main()
{	int n=3;
	PSet(n);
	printf("1～%d的幂集:\n  ",n);
	dispps();
}

