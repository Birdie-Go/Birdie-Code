#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

const int maxn=250000+10;
int n;
LL mod,f[maxn],fac[maxn];

LL exgcd(LL a,LL b,LL &x,LL &y)
{
    if (b==0) {x=1ll;y=0ll;return a;}
    LL ans=exgcd(b,a%b,x,y);
    LL tmp=x;
	x=y;y=tmp-a/b*y;
    return ans;
}

LL inver(LL a,LL P)
{
	LL x=0,y=0;
	LL gcd=exgcd(a,P,x,y);
	if(x>0)
	{
        for (LL t=0;;t--)
            if ((x+P/gcd*t)<=0) return x;
            	else x=x+P/gcd*t;
    }
    else
	{
        for (LL t=0;;t++)
            if ((x+P/gcd*t)>0) {x=x+P/gcd*t;return x;}
    }
}

void ready()
{
	fac[0]=1ll;
	for (int i=1;i<=n;i++) fac[i]=fac[i-1]*(LL)i%mod;
}

int main()
{
	scanf("%d%lld",&n,&mod);
	ready();
	
	return 0;
}
