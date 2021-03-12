//求解凸包问题-礼品包裹算法
#include "Fundament.cpp"	//包含Point基本运算算法
//----礼品包裹算法
bool cmp(Point aj,Point ai,Point ak)
{
	int d=Direction(aj,ai,ak);
	if (d==0)		//共线时,若ajai更长则返回true
		return Distance(aj,ak)<Distance(aj,ai);
	else if (d>0)	//ajai在ajak的顺时针方向上,返回true
		return true;
	else			//否则返回false
		return false;
}
void Package(vector<Point> a,vector<int> &ch)	//礼品包裹算法
{
	int i,j,k,tmp;
	j=0;
	for (i=1;i<a.size();i++)
		if (a[i].x<a[j].x || (a[i].x==a[j].x && a[i].y<a[j].y))
			j=i;			//找最左边最低点j
	tmp=j;					//tmp保存起点
	while (true)
	{
		k=-1;
		ch.push_back(j);	//顶点aj作为凸包上的一个点
		for (i=0;i<a.size();i++)
			if (i!=j && (k==-1 || cmp(a[j],a[i],a[k])))
				k=i;		//从aj出发找角度最小的点ai
		if (k==tmp) break;	//找出起点时结束
		j=k;
	}
}
void main()
{
	vector<Point> a;
	a.push_back(Point(4,10));
	a.push_back(Point(3,7));
	a.push_back(Point(9,7));
	a.push_back(Point(3,4));
	a.push_back(Point(5,6));
	a.push_back(Point(5,4));
	a.push_back(Point(6,3));
	a.push_back(Point(8,1));
	a.push_back(Point(3,0));
	a.push_back(Point(1,6));
	Point st[MAXN];
	vector<int> ch;
	Package(a,ch);
	printf("求解结果\n");
	printf("   凸包的顶点: ");
	for (vector<int>::iterator it=ch.begin();it!=ch.end();it++)
		printf("%d ",*it);
	printf("\n");
}
