//求解最远点对问题的算法
#include "Fundament.cpp"
//以下为求最远点对的两个算法和主函数
double Mostdistp(vector<Point> a,int &maxindex1,int &maxindex2)
//穷举法求a中的最远点对,用vector存放点集
{
	int i,j;
	double d,maxdist=0.0;
    for (i=0;i<a.size();i++)
        for (j=i+1;j<a.size();j++)
        {
			d=Distance(a[i],a[j]);
			if (d>maxdist)
			{
				maxdist=d;
				maxindex1=i;
				maxindex2=j;
			}
		}
	return maxdist;
}
double Mostdistp1(Point a[],int n,int &maxindex1,int &maxindex2)
//穷举法求a中的最远点对,用数组存放点集
{
	int i,j;
	double d,maxdist=0.0;
    for (i=0;i<n;i++)
        for (j=i+1;j<n;j++)
        {
			d=Distance(a[i],a[j]);
			if (d>maxdist)
			{
				maxdist=d;
				maxindex1=i;
				maxindex2=j;
			}
		}
	return maxdist;
}
double RotatingCalipers1(Point ch[],int m,int &maxindex1,int &maxindex2)
{	//被RotatingCalipers调用
	int i,j;
	double maxdist=0.0,d1,d2;
	ch[m]=ch[0];
	j=1;
	for (i=0;i<m;i++)
	{
		printf("考察点i=%d:",i); ch[i].disp(); printf("\n");
		while (fabs(Det(ch[i]-ch[i+1],ch[j+1]-ch[i+1]))>fabs(Det(ch[i]-ch[i+1],ch[j]-ch[i+1])))
		//while (Cross(ch[i+1],ch[j+1],ch[i])>=Cross(ch[i+1],ch[j],ch[i]))
		{
			printf("j=%d:\t",j);
			printf("(%d,%d,%d):%g\t(%d,%d,%d):%g\n",i,i+1,j+1,fabs(Det(ch[i]-ch[i+1],ch[j+1]-ch[i+1])),i,i+1,j,fabs(Det(ch[i]-ch[i+1],ch[j]-ch[i+1])));
			j=(j+1)%m;		//以面积来判断，因为底边是一样的，如果面积大则说明要离平行线远些
		}
		printf("找到j=%d:",j); ch[j].disp(); printf("\n");
		d1=Distance(ch[i],ch[j]);
		printf("(%g,%g),(%g,%g)=%g\n",ch[i].x,ch[i].y,ch[j].x,ch[j].y,d1);
		if (d1>maxdist)
		{
			maxdist=d1;
			maxindex1=i;
			maxindex2=j;
		}
		d2=Distance(ch[i+1],ch[j]);
		printf("(%g,%g),(%g,%g)=%g\n",ch[i+1].x,ch[i+1].y,ch[j].x,ch[j].y,d2);
		if (d2>maxdist)
		{
			maxdist=d2;
			maxindex1=i+1;
			maxindex2=j;
		}
	}
	return maxdist;
}
//---------Graham算法--------------
Point p0;		//起点,全局变量
bool pointcmp(Point &a,Point &b)
{
	if (Direction(p0,a,b)>0)
		return true;
	else
		return false;
}
int Graham(vector<Point> &a,Point ch[])
{
    int top=-1,i,k;
	Point tmp; 
	k=0;
	for (i=1;i<a.size();i++)	//找最下且偏左的点a[k]
		if ((a[i].y<a[k].y) || (a[i].y==a[k].y && a[i].x<a[k].x))
			k=i;
    tmp=a[0];					//通过交换将a[k]点指定为起点a[0] 
    a[0]=a[k];	a[k]=tmp; 
	p0=a[0];					//将起点a[0]放入p0中
	printf("起点a0:"); p0.disp();
    sort(a.begin(),a.end(),pointcmp);	//按极角从小到大排序
	printf("排序后:\n");
	for (vector<Point>::iterator it=a.begin();it!=a.end();it++)
		(*it).disp();
	printf("\n");
	top++;ch[0]=a[0];			//前三个点先进栈 
	top++;ch[1]=a[1]; 
	top++;ch[2]=a[2];
	a[0].disp(); printf("进栈\n");
	a[1].disp(); printf("进栈\n");
	a[2].disp(); printf("进栈\n");
	for (i=3;i<a.size();i++)	//判断与其余所有点的关系
	{ 
		printf("处理点");a[i].disp(); printf("\n");
		while (top>0 && Direction(ch[top-1],a[i],ch[top])>0)
		{
			ch[top].disp(); printf("存在右拐关系，退栈\n");
			top--;				//存在右拐关系,栈顶元素出栈
		}
		top++; ch[top]=a[i];	//当前点与栈内所有点满足向左关系,因此进栈
		a[i].disp(); printf("进栈\n");
	}
    return top+1;				//返回栈中元素个数
}
//-----------------------------------
void RotatingCalipers(vector<Point> &a)	//旋转卡壳算法
{
	int m,index1,index2;
	Point ch[MAXN];
	m=Graham(a,ch);
	printf("凸包:");
	for (int i=0;i<m;i++)		//输出凸包
		ch[i].disp();
	printf("\n");
	double maxdist=RotatingCalipers1(ch,m,index1,index2);
	//double maxdist=Mostdistp1(ch,m,index1,index2);
	printf("最远点对:(%g,%g)和(%g,%g),最远距离=%g\n",ch[index1].x,ch[index1].y,ch[index2].x,ch[index2].y,maxdist);
}
//求最远点对的主函数
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
	RotatingCalipers(a);
}
