#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

const int Maxn=1e6+10;
struct Suffix_Automata {
    LL ans=0;//different substring numbers
    LL Lans=0;////different substring lengths
	int maxlen[Maxn],link[Maxn],sz[Maxn],Size,Last;
    //map <int,int> trans[Maxn];if bigger than 26,use map
    int trans[Maxn][30];
	Suffix_Automata() {Size=Last=1;}

	inline void Extend(int id) {
		int cur=(++Size),p;
		maxlen[cur]=maxlen[Last]+1;
		for (p=Last;p && !trans[p][id];p=link[p]) trans[p][id]=cur;
		if (!p) link[cur]=1;
		else {
			int q=trans[p][id];
			if (maxlen[q]==maxlen[p]+1) link[cur]=q;
			else {
				int clone=(++Size);
				maxlen[clone]=maxlen[p]+1;
                memcpy(trans[clone],trans[q],sizeof(trans[clone]));
				link[clone]=link[q];
				for (;p && trans[p][id]==q;p=link[p]) trans[p][id]=clone;
				link[cur]=link[q]=clone;
			}
		}
        ans+=(LL)maxlen[cur]-(LL)maxlen[link[cur]];
        Lans+=(LL)((maxlen[cur]*(maxlen[cur]+1))/2-(maxlen[link[cur]]*(maxlen[link[cur]]+1))/2);
		Last=cur;
        sz[cur]=1;
	}

    inline void search(char *s,int p,int x,int k) {
        if (sum[x]<k) {puts("-1");exit(0);}
        for (int i=0;i<26;i++)
            if (trans[x][i]) {
                if (k<=sum[trans[x][i]]) {
                    s[p]=i+'a';
                    if (k<=sz[trans[x][i]]) {
                        s[p+1]=0;
                        printf("%s\n",s+1);
                        exit(0);
                    }
                    else search(s,p+1,trans[x][i],k-sz[trans[x][i]]);
                }
                else k-=sum[trans[x][i]];
            }
    }

    //get the k th substring
    //b=0 means "aaa" and "aaa" count 1
    //b=1 means "aaa" and "aaa" count 2
    int t[Maxn],a[Maxn],sum[Maxn];
    inline void getstr(char *s,int b,int k) {
        for (int i=1;i<=Size;i++) t[maxlen[i]]++;
        for (int i=1;i<=Size;i++) t[i]+=t[i-1];
        for (int i=1;i<=Size;i++) a[t[maxlen[i]]--]=i;
        for (int i=Size;i;i--) sz[link[a[i]]]+=sz[a[i]];
        for (int i=1;i<=Size;i++) sum[i]=sz[i]=(b?sz[i]:1);
        sz[1]=sum[1]=0;
        
        for (int i=Size;i;i--)
            for (int j=0;j<26;j++)
                sum[a[i]]+=sum[trans[a[i]][j]];
        search(s,1,1,k);
    }
}T;

char ch[Maxn];

int main() {
    scanf("%s",ch+1);
    int L=strlen(ch+1),b,k;
    scanf("%d%d",&b,&k);
    for (int i=1;i<=L;i++) T.Extend(ch[i]-'a');
    T.getstr(ch,b,k);
}