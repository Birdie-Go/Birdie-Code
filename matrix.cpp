#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

const LL mod=1e9+7ll;

class Matrix {
    public:
    LL a[106][106];
    int n;
 
    Matrix (int ss,int val=0) {
        n=ss;
        for (int i=0;i<n;++i)
            for (int j=0;j<n;++j) {
                a[i][j]=val;
            }
    }
 
    Matrix (const Matrix & b) {
        n=b.n;
        for (int i=0;i<n;++i) {
            for (int j=0;j<n;++j) {
                a[i][j]=b.a[i][j];
            }
        }
    }
 
    Matrix operator * (const Matrix & b) {
        Matrix tmp(this->n);
        for (int i=0;i<n;++i)
            for (int j=0;j<n;++j)
                for (int k=0;k<n;++k)
                    tmp.a[i][j]=(a[i][k]*b.a[k][j]%mod+tmp.a[i][j])%mod;
        return tmp;
    }
 
    void print() {
        for (int i=0;i<n;++i) {
            for (int j=0;j<n;++j) {
                printf("%lld%c",a[i][j],j==n-1?'\n':' ');
            }
        }
    }
};

Matrix qpower (Matrix a, LL b) {
    Matrix tmp(a.n);
    for (int i=0;i<a.n;++i) tmp.a[i][i]=1;
    while (b) {
        if (b&1) tmp=tmp*a;
        a=a*a;
        b>>=1;
    }
    return tmp;
}