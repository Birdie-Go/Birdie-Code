#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

int check(int a,int b,int c,int d,int e,int f)
{
    int g=(a+b+c-d)/2,h=(-a+b+c+d)/2;
    int k=(a-b+c+d)/2,l=(a+b-c+d)/2;
    if (g==e && h==f) printf("%d %d",k,l);
    else if (k==e && l==f) printf("%d %d",g,h);
    else return 0;
    return 1;
}

int main()
{
    freopen("main.in","r",stdin);
    freopen("main.out","w",stdout);

    int a,b,c,d,e,f;
    scanf("%d%d%d%d%d%d",&a,&b,&c,&d,&e,&f);
    if (check(a,b,c,d,e,f)) return 0;
    else if (check(a,b,e,f,c,d)) return 0;
    else if (check(c,d,e,f,a,b)) return 0;

    return 0;
}