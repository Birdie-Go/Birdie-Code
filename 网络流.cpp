#include <bits/stdc++.h>
using namespace std;

const int maxn=1000+10,maxm=10,maxp=100+10,INF=1e9;
int cur;
int x[maxm],y[maxm],val[maxm],dep[maxp],lter[2*maxp],cmap[maxp],head[2*maxp];
int sta[maxn][maxn];
struct adj
{
    int obj,next,flow,rev;
}e[2*maxn];
vector <int> kin[maxn];

bool bfs(int k,int t)
{
	memset(dep,0,sizeof(dep));
	int star=1,tail=1;cmap[star]=k;dep[k]=1;
	while (star<=tail)
	{
		int now=cmap[star];
		for (int i=head[now];i!=-1;i=e[i].next)
		{
			int to=e[i].obj,flow=e[i].flow;
			if (flow==0 || dep[to]!=0) continue;
			tail++;
			dep[to]=dep[now]+1;
			cmap[tail]=to;
		}
		star++;
	}
	return (dep[t]!=0);
}

int dfs(int k,int t,int maxf)
{
	if (k==t || !maxf) return maxf;
	int v=0;
	for (int &i=lter[k];i!=-1;i=e[i].next)
	{
		int to=e[i].obj,flow=e[i].flow;
		if (dep[to]<=dep[k] || flow==0) continue;
		int now=dfs(to,t,min(maxf,flow));
		e[i].flow-=now;
		e[e[i].rev].flow+=now;
		v+=now;
		maxf-=now;
		if (!maxf) break;
	}
	return v;
}

int dinic(int k,int t)
{
	int now=0;
	while (bfs(k,t)) {memcpy(lter,head,sizeof(head));now+=dfs(k,t,INF);}
	return now;
}

void addedge(int x,int y,int flow)
{
	cur++;
	e[cur].obj=y;
	e[cur].flow=flow;
	e[cur].next=head[x];
	e[cur].rev=cur+1;
	head[x]=cur;
	cur++;
	e[cur].obj=x;
	e[cur].flow=0;
	e[cur].next=head[y];
	e[cur].rev=cur-1;
	head[y]=cur;
}

int check(int n,int m,int num,int Len)
{
    for (int i=1;i<=n;i++) for (int j=1;j<=m;j++) sta[i][j]=0;
    for (int i=0;i<=(1<<num);i++) kin[i].clear();
    for (int i=0;i<=(1<<num)+num+1;i++) head[i]=-1;
    cur=0;

    for (int i=1;i<=n;i++)
    for (int j=1;j<=m;j++)
    {
        for (int k=1;k<=num;k++)
            if (abs(x[k]-i)+abs(y[k]-j)<=Len) sta[i][j]+=(1<<(k-1));
        kin[sta[i][j]].push_back((i-1)*m+j);
        if (sta[i][j]==0) return 0;
    }

    for (int i=1;i<(1<<num);i++)
    {
        addedge(0,i,kin[i].size());
        for (int j=1;j<=num;j++)
            if ((i&(1<<(j-1)))>0) addedge(i,(1<<num)+j-1,INF);
    }
    for (int i=1;i<=num;i++) addedge((1<<num)+i-1,(1<<num)+num,val[i]);

    int now=dinic(0,(1<<num)+num);
    return (now==n*m);
}

int main()
{
    freopen("main.in","r",stdin);
    freopen("main.out","w",stdout);

    int T;scanf("%d",&T);
    while (T--)
    {
        int n,m,k;scanf("%d%d%d",&n,&m,&k);
        for (int i=1;i<=k;i++) scanf("%d%d%d",&x[i],&y[i],&val[i]);

        int L=-1,R=n*m;
        while (L+1<R)
        {
            int mid=(L+R)/2;
            if (check(n,m,k,mid)) R=mid;else L=mid;
        }
        if (check(n,m,k,R)) printf("%d\n",R);else printf("-1\n");
    }
    
    return 0;
}