#include <stdio.h>
#define MAXV 1010
#define INF 0xffffff					//定义∞
int n,m;
int Dist[MAXV][MAXV],Cost[MAXV][MAXV];
int s,t;
void Dijkstra(int s)					//狄克斯特拉算法
{	int dist[MAXV];
    	int cost[MAXV];
    	int S[MAXV];
    	int mindist,mincost,u;
    	int i,j;
    	for(i=1;i<=n;i++)				//dist、cost、S初始化
    	{	dist[i]=Dist[s][i];
        	cost[i]=Cost[s][i];
        	S[i]=0;
    	}
    	dist[s]=cost[s]=0;
    	S[s]=1;
    	for(i=0;i<m;i++)
    	{	mindist=INF;
      	for(j=1;j<=n;j++)			//求V-S中的最小距离mindist
        		if (S[j]==0 && mindist>dist[j])
            		mindist=dist[j];
        	if (mindist==INF) break;		//找不到连通的顶点
      	mincost=INF; u=-1;
      	for(j=1;j<=n;j++)			//求尚未考虑的、距离最小的顶点u
        	{	if (S[j]==0 && mindist==dist[j] && mincost>cost[j])
            	{	mincost=cost[j];		//在dist为最小的顶点中找最小cost的顶点u
                	u=j;
            	}
        	}
        	S[u]=1;					//将顶点u加入S集合
        	for (j=1;j<=n;j++)			//考虑顶点u,求s到每个顶点j的最短路径长度和花费
        	{	int d=mindist+Dist[u][j];	//d记录经过顶点u的路径长度
            	int c=cost[u]+Cost[u][j];	//c记录经过顶点u的花费
            	if(S[j]==0 && d<dist[j])
            	{	dist[j]=d;
                	cost[j]=c;
            	}
            	else if(S[j]==0 && d==dist[j] && c<cost[j])
                	cost[j]=c;			//有多条长度相同的最短路径
        	}
        	if(S[t]==1)					//已经求出s到t的最短路径
        	{	printf("%d %d\n",dist[t],cost[t]);
            	return;
        	}
    	} 
}
int main()
{	int a,b,d,p;
    	int i,j;
   	while(scanf("%d%d",&n,&m)!=EOF)
    	{	if(m==0 && n==0)
            	break;
        	for(i=1;i<=n;i++)
        	{	for(j=1;j<=n;j++)
            	{	Dist[i][j]=INF;
                	Cost[i][j]=INF;
            	}
        	}
        	for(i=0;i<m;i++)
        	{	scanf("%d%d%d%d\n",&a,&b,&d,&p);
            	if(Dist[a][b] > d)
            	{	Dist[a][b]=Dist[b][a]=d;	//无向图的边是对称的
                	Cost[a][b]=Cost[b][a]=p;
            	}
        	}
        	scanf("%d%d",&s,&t);
        	Dijkstra(s);
    	}
    	return 0;
}
