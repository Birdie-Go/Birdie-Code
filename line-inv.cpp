#include<bits/stdc++.h>
using namespace std;
typedef long long LL;

const int maxn=6e6+10;
const LL mod=998244353ll;
LL inv[maxn],ans[maxn];

int main()
{
	ans[1]=1ll;inv[1]=1ll;
    for (int i=2;i<maxn;i++) {
        inv[i]=(mod-mod/i)*inv[mod%i]%mod;
        ans[i]=(ans[i-1]+inv[i]*inv[i]%mod)%mod;
    }

    int T;scanf("%lld",&T);
	while (T--) {
		int n;scanf("%lld",&n);
		printf("%lld\n",3ll*ans[n]*inv[n]%mod);
	}

    return 0;
}