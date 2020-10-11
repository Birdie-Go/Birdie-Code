#include <bits/stdc++.h>
using namespace std;

const int maxn=1e6+5;
char s[maxn*2],str[maxn*2];
int Len[maxn*2],len;

void getstr() {
    int k=0;
    str[k++]='@';
    for (int i=0;i<len;i++) {
        str[k++]='#';
        str[k++]=s[i];
    }
    str[k++]='#';
    len=k;
    str[k]=0;
}

int manacher() {
    int mx=0,id;
    int maxx=0;
    for (int i=1;i<len;i++) {
        if (mx>i) Len[i]=min(mx-i,Len[2*id-i]);
            else Len[i]=1;
        while (str[i+Len[i]]==str[i-Len[i]]) Len[i]++;
        if (Len[i]+i>mx) {
            mx=Len[i]+i;
            id=i;
            maxx=max(maxx,Len[i]);
        }
    }
    return maxx-1;
}

int main() {
    scanf("%s",s);
    len=strlen(s);
    getstr();
    printf("%d\n",manacher());
    return 0;
}