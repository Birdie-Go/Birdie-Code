#include<bits/stdc++.h>
#define pi acos(-1)
using namespace std;
typedef complex<double> E;

const int maxn=2621450;
int n,m,l,r[maxn];
E a[maxn],b[maxn];

void fft(E *a,int f) {
    for (int i=0;i<n;i++) if(i<r[i]) swap(a[i],a[r[i]]);
    for (int i=1;i<n;i<<=1) {
        E wn(cos(pi/i),f*sin(pi/i)); 
        for (int p=i<<1,j=0;j<n;j+=p) {
            E w(1,0);
            for (int k=0;k<i;k++,w*=wn) {
                E x=a[j+k],y=w*a[j+k+i];
                a[j+k]=x+y;a[j+k+i]=x-y;  
            }
        }
    }
}

inline int read() {
    int f=1,x=0;char ch;
    do {ch=getchar();if(ch=='-')f=-1;} while (ch<'0'|| ch>'9');
    do {x=x*10+ch-'0';ch=getchar();} while (ch>='0'&& ch<='9');
    return f*x;
}

int main() {
    freopen("main.in","r",stdin);
    freopen("main.out","w",stdout);

    n=read();m=read();
    for (int i=0;i<=n;i++) a[i]=read();
    for (int i=0;i<=m;i++) b[i]=read();

    m+=n;for (n=1;n<=m;n<<=1) l++;
    for (int i=0;i<n;i++) r[i]=(r[i>>1]>>1)|((i&1)<<(l-1));

    fft(a,1);fft(b,1);
    for (int i=0;i<=n;i++) a[i]=a[i]*b[i];
    fft(a,-1);
    for (int i=0;i<=m;i++) printf("%d ",(int)(a[i].real()/n+0.5));
}