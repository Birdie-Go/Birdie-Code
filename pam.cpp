#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

const int maxn=1e5+10;

struct Palindromic_Tree {
    int next[maxn][26]; 
    int fail[maxn];
    int cnt[maxn];
    int num[maxn];
    int len[maxn];
    int S[maxn];
    int last;
    int n;
    int p;
 
    int newnode(int l) {
        for(int i=0;i<26;++i) next[p][i]=0;
        cnt[p]=0;
        num[p]=0;
        len[p]=l;
        return p++;
    }
 
    void Init() {
        p=0;
        newnode( 0);
        newnode(-1);
        last=0;
        n=0;
        S[n]=-1;
        fail[0]=1;
    }
 
    int get_fail(int x) {
        while (S[n-len[x]-1]!=S[n]) x=fail[x];
        return x;
    }
 
    void add(int c) {
        S[++n]=c;
        int cur=get_fail(last) ;
        if (!next[cur][c]) 
        {
            int now=newnode(len[cur]+2) ;
            fail[now]=next[get_fail(fail[cur])][c] ;
            next[cur][c]=now ;
            num[now]=num[fail[now]]+1;
        }
        last=next[cur][c];
        cnt[last]++;
    }

    //本质不同的回文串数量
    LL count() {
        LL res=p*1ll;
        for(int i=p-1;i>=0;--i) cnt[fail[i]]+=cnt[i];
        return (res-2);
    }
}pam1,pam2;

char ch[maxn];
int a[maxn],b[maxn];

int main() {
    scanf("%s",ch);
    int L=strlen(ch-'a');
    for (int i=0;i<L;i++) pam1.add(ch[i]),a[i]=pam1.len[pam1.last];
    reverse(ch,ch+L);
    for (int i=0;i<L;i++) pam2.add(ch[i]),b[i]=pam2.len[pam2.last];
    int ans=0;
    for (int i=0;i<L-1;i++) ans=max(ans,a[i]+b[i+1]);
    printf("%d\n",ans);

    return 0;
}