//求解最近点对问题的算法
#include "Fundament.cpp"
#define min(x,y) ((x)<(y)?(x):(y))
//以下为求最近点对的两个算法和主函数
double ClosestPoints(vector<Point> a,int leftindex,int rightindex)
//蛮力法求a[leftindex..rightindex]中的最近点对距离
{
	int i,j;
	double d,mindist=INF;
    for (i=leftindex;i<=rightindex;i++)
        for (j=i+1;j<=rightindex;j++)
        {
			d=Distance(a[i],a[j]);
			if (d<mindist)
				mindist=d;
		}
	return mindist;
}
void display(vector<Point> a,int leftindex,int rightindex)	//输出a中的部分元素，用于调试
{
	int i;
	for (i=leftindex;i<=rightindex;i++)
		a[i].disp();
	printf("\n");
}
//分治递归求点对距离
bool pointxcmp(Point &p1,Point &p2)		//用于点按x坐标递增排序
{
	return p1.x<p2.x;
}
bool pointycmp(Point &p1,Point &p2)		//用于点按y坐标递增排序
{
	return p1.y<p2.y;
}
double ClosestPoints11(vector<Point> &a,vector<Point> b,int leftindex,int rightindex)
//递归求a[leftindex..rightindex]中最近点对的距离
{
	vector<Point> leftb,rightb,b1;
	int i,j,midindex;
	double d1,d2,d3=INF,d;
	if ((rightindex-leftindex+1)<=3)		//少于4个点,直接用蛮力法求解
	{
		d=ClosestPoints(a,leftindex,rightindex);
		return d;
	}
    midindex=(leftindex+rightindex)/2;	//求中间位置
	for (i=0;i<b.size();i++)			//将b中点集分为左右两部分
		if (b[i].x<a[midindex].x)
			leftb.push_back(b[i]);
		else
			rightb.push_back(b[i]);
    d1=ClosestPoints11(a,leftb,leftindex,midindex);
	d2=ClosestPoints11(a,rightb,midindex+1,rightindex);
	d=min(d1,d2);	//当前最小距离d=MIN(d1,d2)
    //求中间部分点对的最小距离
	for (i=0;i<b.size();i++)	//将b中间宽度为2*d的带状区域内的子集复制到b1中
		if (fabs(b[i].x-a[midindex].x)<=d)
			b1.push_back(b[i]);
	double tmpd3;
	for (i=0;i<b1.size();i++)	//求b1中最近点对
		for (j=i+1;j<b1.size();j++)
		{
			if (b1[j].y-b1[i].y>=d) break;
			tmpd3=Distance(b1[i],b1[j]);
			if (tmpd3<d3)
				d3=tmpd3;
		}
	d=min(d,d3);
	return d;
}
double ClosestPoints1(vector<Point> &a,int leftindex,int rightindex)
//求a[leftindex..rightindex]中最近点对的距离
{
	int i;
	vector<Point> b;
	vector<Point>::iterator it;
	printf("排序前:\n");
	for (it=a.begin();it!=a.end();it++)
		(*it).disp();
	printf("\n");
    sort(a.begin(),a.end(),pointxcmp);	//按x坐标从小到大排序
	printf("按x坐标排序后:\n");
	for (it=a.begin();it!=a.end();it++)
		(*it).disp();
	printf("\n");

	for (i=0;i<a.size();i++)			//将a中点集复制到b中
		b.push_back(a[i]);

    sort(b.begin(),b.end(),pointycmp);	//按y坐标从小到大排序
	printf("按y坐标排序后:\n");
	for (it=b.begin();it!=b.end();it++)
		(*it).disp();
	printf("\n");
	return ClosestPoints11(a,b,0,a.size()-1);
}
//求最近点对的主函数
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
	double mindist=ClosestPoints1(a,0,a.size()-1);
	printf("最近距离=%g\n",mindist);
}