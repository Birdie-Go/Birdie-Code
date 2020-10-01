#include <bits/stdc++.h>
using namespace std;

const int maxn=1e5+10;
char a[maxn],b[maxn];
int nex[maxn];

void make_next(int m)
{
    nex[0]=0;
    int k=0;
    for (int i=1;i<m;i++)
    {
        while (k>0 && b[i]!=b[k]) k=nex[k-1];
        if (b[i]==b[k]) ++k;
        nex[i]=k;
    }
}

int check(int n,int m)
{
    if (m>n) return 0;
    make_next(m);
    int k=0,ans=0;
    for (int i=0;i<n;i++)
    {
        while (k>0 && a[i]!=b[k]) k=nex[k-1];
        if (a[i]==b[k]) ++k;
        if (k==m) {k=nex[k-1];ans++;}
    }
    return ans;
}

int main()
{
    freopen("main.in","r",stdin);
    freopen("main.out","w",stdout);

	//where b appear in a
    scanf("%s",a);scanf("%s",b);
    int n=strlen(a),m=strlen(b);
    printf("%d\n",check(n,m));

    return 0;
}