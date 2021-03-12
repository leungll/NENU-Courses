//求解最近点对问题的算法(调试版本)
#include "Fundament.cpp"
//以下为求最近点对的两个算法和主函数
double ClosestPoints(vector<Point> a,int leftindex,int rightindex,int &minindex1,int &minindex2)
//穷举法求a[leftindex..rightindex]中的最近点对
{
	int i,j;
	double d,mindist =INF;
    for (i=leftindex;i<=rightindex;i++)
        for (j=i+1;j<=rightindex;j++)
        {
			d=Distance(a[i],a[j]);
			if (d<mindist)
			{
				mindist=d;
				minindex1=i;
				minindex2=j;
			}
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
double ClosestPoints11(vector<Point> &a,vector<Point> b,int leftindex,int rightindex,int &minindex1,int &minindex2)
//递归求a[leftindex..rightindex]中的最近点对
{
	vector<Point> leftb,rightb,b1;
	int i,j,midindex;
	int leftminindex1,leftminindex2;		//左边的最近点对
	int rightminindex1,rightminindex2;		//右边的最近点对
	double d1,d2,d3,d;
	if ((rightindex-leftindex+1)<=3)		//少于4个点,直接用穷举法求解
	{
		d=ClosestPoints(a,leftindex,rightindex,minindex1,minindex2);
		printf("  点数少于4:求出最近距离=%g: ",d); a[minindex1].disp(); a[minindex2].disp(); printf("\n");
		return d;
	}
    midindex=(leftindex+rightindex)/2;	//求中间位置
	printf("midindex=%d ",midindex); a[midindex].disp(); printf("\n");
	for (i=0;i<b.size();i++)			//将b中点集分为左右两部分
		if (b[i].x<a[midindex].x)
			leftb.push_back(b[i]);
		else
			rightb.push_back(b[i]);
	printf("Left:"); display(a,leftindex,midindex);
    d1=ClosestPoints11(a,leftb,leftindex,midindex,leftminindex1,leftminindex2);
	printf("  d1=%g ",d1); a[leftminindex1].disp(); a[leftminindex2].disp(); printf("\n");

	printf("Right:"); display(a,midindex+1,rightindex);
	d2=ClosestPoints11(a,rightb,midindex+1,rightindex,rightminindex1,rightminindex2);
	printf("  d2=%g ",d2); a[rightminindex1].disp();a[rightminindex2].disp();printf("\n");

	d=INF;		//当前最小距离d=MIN(d1,d2)
    if (d1<d2)
    {
        minindex1=leftminindex1;
        minindex2=leftminindex2;
        d=d1;
    }
    else
	{
        minindex1=rightminindex1;
        minindex2=rightminindex2;
        d=d2;
    }
	printf("  左右部分求出d=%g\n",d);
    //求中间部分点对的最小距离
	for (i=0;i<b.size();i++)	//将b中间宽度为2*d的带状区域内的子集复制到b1中
		if (fabs(b[i].x-a[midindex].x)<=d)
			b1.push_back(b[i]);
	printf("  中间部分点集:"); display(b1,0,b1.size()-1);
	d3=INF;
	double tmpd3;
	int midminindex1,midminindex2;
	for (i=0;i<b1.size();i++)	//求b1中最近点对
		for (j=i+1;j<b1.size();j++)
		{
			if (b1[j].y-b1[i].y>=d) break;
			tmpd3=Distance(b1[i],b1[j]);
			printf("  Mid：");b1[i].disp(); b1[j].disp(); printf("tmpd3=%g\n",tmpd3);
			if (tmpd3<d3)
			{
				midminindex1=i;
				midminindex2=j;
				d3=tmpd3;
			}
		}
	printf("中间部分结果:d3=%g,对应的点对:",d3); b1[midminindex1].disp(); b1[midminindex2].disp(); printf("\n");
	if (d<d3)
	{
		printf("合并结果：d=%g ",d); a[minindex1].disp(); a[minindex2].disp(); printf("\n");
	}
	else
	{
		d=d3;
		printf("合并结果m：d=%g ",d); b1[midminindex1].disp(); b1[midminindex2].disp(); printf("\n");
	}
	return d;
}
double ClosestPoints1(vector<Point> &a,int leftindex,int rightindex,int &minindex1,int &minindex2)
//求a[leftindex..rightindex]中的最近点对
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
	return ClosestPoints11(a,b,0,a.size()-1,minindex1,minindex2);
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
	int index1,index2;
	double mindist=ClosestPoints1(a,0,a.size()-1,index1,index2);
}