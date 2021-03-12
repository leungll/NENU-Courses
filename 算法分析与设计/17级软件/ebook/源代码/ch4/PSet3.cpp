//递归求解幂集问题
#include <stdio.h>
#include <vector>
using namespace std;
vector<vector<int> > ps;			//存放幂集
void Inserti(int i)					//向幂集ps中每个集合元素添加i并插入到ps中
{
	vector<vector<int> > ps1;			//子幂集
	vector<vector<int> >::iterator it;	//幂集迭代器
	ps1=ps;								//ps1存放原来的幂集
	for (it=ps1.begin();it!=ps1.end();++it)
		(*it).push_back(i);			//在ps1的每个集合元素末尾添加i
	for (it=ps1.begin();it!=ps1.end();++it)
		ps.push_back(*it);			//将ps1的每个集合元素添加到ps中
}
void PSet(int i,int n)				//求1～n的幂集ps
{
	if (i<=n)
	{
		Inserti(i);					//将i插入到现有子集中产生新子集
		PSet(i+1,n);				//递归调用
	}
}
void dispps()							//输出幂集ps
{	vector<vector<int> >::iterator it;	//幂集迭代器
	vector<int>::iterator sit;			//幂集集合元素迭代器
	for (it=ps.begin();it!=ps.end();++it)
	{	printf("{ ");
		for (sit=(*it).begin();sit!=(*it).end();++sit)
			printf("%d ",*sit);
		printf("} ");
	}
	printf("\n");
}
void main()
{
	int n=3;
	vector<int> s;
	ps.push_back(s);
	PSet(1,n);			//求1～n的幂集ps
	printf("1～%d的幂集:\n  ",n);
	dispps();			//输出幂集ps
}
