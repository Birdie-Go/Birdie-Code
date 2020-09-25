#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

const int maxn=1e7+5,P=998244353,P1=3,P2=332748118;
int lena,lenb,n=1,lim,r[maxn];
LL a[maxn],b[maxn];

LL rpow(LL x,LL y) {
	LL res=1;
	while (y) {
		if (y&1) res=(res*x)%P;
		x=(x*x)%P;
		y>>=1;
	}
	return res%P;
}

inline int read() {
    int x=0,f=1;
    char ch=getchar();
    while (ch<'0'||ch>'9') {
        if(ch=='-')f=-1;
        ch=getchar();
    }
    while (ch>='0'&&ch<='9') {
        x=x*10+ch-'0';
        ch=getchar();
    }
    return x*f;
}

void NTT(LL *A,int tp) {
    for (int i=0;i<n;i++) if(i<r[i]) swap(A[i],A[r[i]]);
    for (int i=1;i<n;i<<=1) {
        LL W=rpow(tp?P1:P2,(P-1)/(i<<1));
        for (int j=i<<1,k=0;k<n;k+=j) {
            LL w=1;
            for (int l=0;l<i;l++,w=(w*W)%P) {
                int x=A[k+l],y=w*A[k+i+l]%P;
                A[k+l]=(x+y)%P;
                A[k+i+l]=(x-y+P)%P;
            }
       }
    }
}

int main() {
    freopen("main.in","r",stdin);
    freopen("main.out","w",stdout);

    lena=read();lenb=read();
    while (n<=lena+lenb) n<<=1,lim++;
    for (int i=0;i<=lena;i++) a[i]=(read()+P)%P;
    for (int i=0;i<=lenb;i++) b[i]=(read()+P)%P;
    for (int i=0;i<n;i++) r[i]=(r[i>>1]>>1)|((i&1)<<(lim-1));

    NTT(a,1);NTT(b,1);
    for (int i=0;i<=n;i++) a[i]=(a[i]*b[i])%P;
    NTT(a,0);
    LL inv=rpow(n,P-2);
    for (int i=0;i<=lena+lenb;i++) printf("%d ",(a[i]*inv)%P);
} 