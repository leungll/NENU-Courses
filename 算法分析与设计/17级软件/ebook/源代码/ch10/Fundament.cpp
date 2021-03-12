//向量的基本运算算法
//#pragma warning( disable:4786) 
#include <algorithm>
#include <vector>
using namespace std;
#include <stdio.h>
#include <math.h>
#define INF 32767			//∞
#define MAXN 20
int sign(double x)			//返回数值x的符号
{
	if (x>0) return 1;
	else if (x<0) return -1;
	else return 0;
}
double sqr(double x)		//求x的平方
{
	return x*x;
}
//--这是VC++6.0著名的bug，可以安装补丁，这里采用增加以下代码修正
class Point;
bool operator ==(Point &p1,Point &p2);	//重载==运算符
Point operator +(Point &p1,Point &p2);	//重载+运算符
Point operator -(Point &p1,Point &p2);	//重载-运算符
double Dot(Point p1,Point p2);			//两个向量的点积
double Length(Point &p);	//求向量长度
int Angle(Point p0,Point p1,Point p2);	//求两线段p0p1和p0p2的夹角
double Det(Point p1,Point p2);			//两个向量的叉积
int Direction(Point p0,Point p1,Point p2);	//判断两线段p0p1和p0p2的方向
double Distance(Point p1,Point p2);		//求两个点的距离
double DistPtoSegment(Point p0,Point p1,Point p2);	//求p0到p1p2线段的距离

bool InRectAngle(Point p0,Point p1,Point p2);		//判断点p0是否在p1和p2表示的矩形内
bool OnSegment(Point p0,Point p1,Point p2);			//判断点p0是否在p1p2线段上
bool Parallel(Point p1,Point p2,Point p3,Point p4);	//判断p1p2和p3p4线段是否平行
bool SegIntersect(Point p1,Point p2,Point p3,Point p4);	//判断p1p2和p3p4两线段是否相交
bool PointInPolygon(Point p0,vector<Point> a);	//判断点p0是否在点集a所形成的多边形内

double triangleArea(Point p1,Point p2,Point p3);	//求三角形面积
double polyArea(vector<Point> p);	//求多边形面积

//
class Point					//点类
{
public:
	double x;				//行坐标
	double y; 				//列坐标
	Point() {}						//默认构造函数
	Point(double x1,double y1)		//重载构造函数
	{	x=x1;
		y=y1;
	}
	void disp()
	{	printf("(%g,%g) ",x,y); }
	friend bool operator ==(Point &p1,Point &p2);		//重载==运算符
	friend Point operator +(Point &p1,Point &p2);		//重载+运算符
	friend Point operator -(Point &p1,Point &p2);		//重载-运算符
	friend double Dot(Point p1,Point p2);				//两个向量的点积
	friend double Length(Point &p);						//求向量长度
	friend int Angle(Point p0,Point p1,Point p2);		//求两线段p0p1和p0p2的夹角
	friend double Det(Point p1,Point p2);				//两个向量的叉积
	friend int Direction(Point p0,Point p1,Point p2);	//判断两线段p0p1和p0p2的方向
	friend double Distance(Point p1,Point p2);			//求两个点的距离
	friend double DistPtoSegment(Point p0,Point p1,Point p2);	//求p0到p1p2线段的距离

	friend bool InRectAngle(Point p0,Point p1,Point p2);		//判断点p0是否在p1和p2表示的矩形内
	friend bool OnSegment(Point p0,Point p1,Point p2);			//判断点p0是否在p1p2线段上
	friend bool Parallel(Point p1,Point p2,Point p3,Point p4);	//判断p1p2和p3p4线段是否平行
	friend bool SegIntersect(Point p1,Point p2,Point p3,Point p4);//判断p1p2和p3p4两线段是否相交
	friend bool PointInPolygon(Point p0,vector<Point> a);	//判断点p0是否在点集a所形成的多边形内

	friend double triangleArea(Point p1,Point p2,Point p3);	//求三角形面积
	friend double polyArea(vector<Point> p);	//求多边形面积
};
//--以下是友元实现代码-----
bool operator ==(Point &p1,Point &p2)	//重载==运算符
{
	return p1.x==p2.x && p1.y==p2.y;
}
Point operator +(Point &p1,Point &p2)	//重载+运算符
{
	return Point(p1.x+p2.x,p1.y+p2.y);
}
Point operator -(Point &p1,Point &p2)	//重载-运算符
{
	return Point(p1.x-p2.x,p1.y-p2.y);
}
double Dot(Point p1,Point p2)			//两个向量的点积
{
	return p1.x*p2.x+p1.y*p2.y;
}
double Length(Point &p)					//求向量长度
{
	return sqrt(Dot(p,p));
}
int Angle(Point p0,Point p1,Point p2)	//求两线段p0p1和p0p2的夹角
{
	double d=Dot((p1-p0),(p2-p0));
	if (d==0)
		return 0;		//两线段p1p0和p2p0夹角为直角
	else if (d>0)
		return 1;		//两线段p1p0和p2p0的夹角为钝角
	else
		return -1;		//两线段p1p0和p2p0的夹角为锐角
}
double Det(Point p1,Point p2)			//两个向量的叉积
{
	return p1.x*p2.y-p1.y*p2.x;
}
int Direction(Point p0,Point p1,Point p2)	//判断两线段p0p1和p0p2的方向
{
	double d=Det((p1-p0),(p2-p0));
	if (d==0)
		return 0;		//3点共线
	else if (d>0)
		return 1;		//p0p2在p0p1的顺时针方向上
	else
		return -1;		//p0p2在p0p1的逆时针方向上
}
double Distance(Point p1,Point p2)		//两个点之间的距离
{
	return sqrt((p1.x-p2.x)*(p1.x-p2.x)+(p1.y-p2.y)*(p1.y-p2.y));
}
double DistPtoSegment(Point p0,Point p1,Point p2)	//求p0到p1p2线段的距离
{
	Point v1=p2-p1,v2=p1-p2,v3=p0-p1,v4=p0-p2;
	if (p1==p2)
		return Length(p0-p1);
	if (Dot(v1,v3)<0)
		return Length(v3);
	else if (Dot(v2,v4)<0)
		return Length(v4);
	else
		return fabs(Det(v1,v3))/Length(v1);
}


bool InRectAngle(Point p0,Point p1,Point p2)		//判断点p0是否在p1和p2表示的矩形内
{
	return Dot(p1-p0,p2-p0)<=0;
}
bool OnSegment(Point p0,Point p1,Point p2)			//判断点p0是否在p1p2线段上
{
	return Det(p1-p0,p2-p0)==0 && Dot(p1-p0,p2-p0)<=0;
}

bool Parallel(Point p1,Point p2,Point p3,Point p4)	//判断p1p2和p3p4线段是否平行
{
	return Det(p2-p1,p4-p3)==0;
}

double DistPtoSegment1(Point p0,Point p1,Point p2)	//求p0到p1p2线段的距离
{
	if (p1==p2)
		return Length(p0-p1);
	if (Dot(p2-p1,p0-p1)<0)
		return Length(p1-p1);
	else if (Dot(p2-p1,p0-p2)>0)
		return Length(p0-p2);
	else
		return fabs(Det(p2-p1,p0-p1))/Length(p2-p1);
}
bool SegIntersect(Point p1,Point p2,Point p3,Point p4)	//判断p1p2和p3p4两线段是否相交
{
	int d1,d2,d3,d4;
	d1=Direction(p3,p1,p4);		//求p3p1在p3p4的哪个方向上
	d2=Direction(p3,p2,p4);		//求p3p2在p3p4的哪个方向上
	d3=Direction(p1,p3,p2);		//求p1p3在p1p2的哪个方向上
	d4=Direction(p1,p4,p2);		//求p1p4在p1p2的哪个方向上
	if (d1*d2<0 && d3*d4<0)
		return true;
	if (d1==0 && OnSegment(p1,p3,p4))		//若d1为0且p1在p3p4线段上
		return true;
	else if (d2==0 && OnSegment(p2,p3,p4))	//若d2为0且p2在p3p4线段上
		return true;
	else if (d3==0 && OnSegment(p3,p1,p2))	//若d3为0且p3在p1p2线段上
		return true;
	else if (d4==0 && OnSegment(p4,p1,p2))	//若d4为0且p4在p1p2线段上
		return true;
	else
		return false;
}
bool PointInPolygon(Point p0,vector<Point> a)	//判断点p0是否在点集a所形成的多边形内
{	int i,cnt=0;		//cnt累加交点个数
	double x;
	Point p1,p2;
	for (i=0;i<a.size();i++)
	{	p1=a[i]; p2=a[i+1];
		if (OnSegment(p0,p1,p2))
			return true;							//如果点p0在多边形边p1p2上,返回true
		//以下求解y=p0.y与p1p2的交点
		if (p1.y==p2.y) continue;					//如果p1p2是水平线,直接跳过
		//以下两种情况是交点在p1p2延长线上
		if (p0.y<p1.y && p0.y<p2.y) continue;		//p0在p1p2线段下方,直接跳过
		if (p0.y>=p1.y && p0.y>=p2.y) continue;		//p0在p1p2线段上方,直接跳过
		x=(p0.y-p1.y)*(p2.x-p1.x)/(p2.y-p1.y)+p1.x;	//求交点坐标的x值
		if (x>p0.x) cnt++;							//只统计射线的一边
	}
	return (cnt%2==1);
}
double triangleArea(Point p1,Point p2,Point p3)	//求三角形面积
{
	return fabs(Det(p1-p2,p3-p2))/2;
}

double polyArea(vector<Point> p)	//求多边形面积
{
	double ans=0.0;
	for (int i=1;i<p.size()-1;i++)
		ans+=Det(p[i]-p[0],p[i+1]-p[0]);
	return fabs(ans)/2;
}
/*
void main()
{
	vector<Point> a;
	a.push_back(Point(5,0));
	a.push_back(Point(9,3));
	a.push_back(Point(10,7));
	a.push_back(Point(4,9));
	a.push_back(Point(0,6));
	a.push_back(Point(3,5));
	a.push_back(Point(0,2));
	for (int i=1;i<a.size()-1;i++)
		printf("(p[%d]-p[0])×(p[%d]-p[0])/2=%g\n",i,i+1,Det(a[i]-a[0],a[i+1]-a[0])/2);
	printf("Area=%g\n",polyArea(a));
}
*/