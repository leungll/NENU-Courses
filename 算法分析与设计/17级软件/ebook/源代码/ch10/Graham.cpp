//求解凸包问题-Graham扫描算法
#include "Fundament.cpp"
Point p0;		//起点,全局变量
void swap(Point &x,Point &y)		//交换x和y两个点
{
	Point tmp=x;
	x=y; y=x;
}
bool cmp(Point &a,Point &b)			//排序比较函数
{
	if (Direction(p0,a,b)>0)
		return true;
	else
		return false;
}
int Graham(vector<Point> &a,Point ch[])		//求凸包的Graham算法
{
    int top=-1,i,k=0;
	Point tmp; 
	for (i=1;i<a.size();i++)	//找最下且偏左的点a[k]
		if ((a[i].y<a[k].y) || (a[i].y==a[k].y && a[i].x<a[k].x))
			k=i;
    swap(a[0],a[k]);			//通过交换将a[k]点指定为起点a[0] 
	p0=a[0];					//将起点a[0]放入p0中
    sort(a.begin()+1,a.end(),cmp);	//按极角从小到大排序
	top++;ch[0]=a[0];			//前3个点先进栈 
	top++;ch[1]=a[1]; 
	top++;ch[2]=a[2];
	for (i=3;i<a.size();i++)	//判断与其余所有点的关系
	{ 
		while (top>=0 && (Direction(ch[top-1],a[i],ch[top])>0 || 
			Direction(ch[top-1],a[i],ch[top])==0 && Distance(ch[top-1],a[i])>Distance(ch[top-1],ch[top])))
		{
			top--;				//存在右拐关系,栈顶元素出栈
		}
		top++; ch[top]=a[i];	//当前点与栈内所有点满足向左关系,因此进栈
	}
    return top+1;				//返回栈中元素个数
}
//Graham算法的主函数
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
	Point st[MAXN];					//用作栈
	int n;
	n=Graham(a,st);
	printf("求解结果\n");
	printf("   凸包的顶点: ");
	for (int i=0;i<n;i++)			//栈中所有元素为凸包
		st[i].disp();
	printf("\n");
}