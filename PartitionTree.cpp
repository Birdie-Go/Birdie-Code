#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

const int maxn=1e5+10;
class Tree {
public:
    Tree() {ans=0;}
    ~Tree() {}
    void read(int n) {
        for (int i=1;i<=n;i++) scanf("%d",&num[1][i]);
        for (int i=1;i<=n;i++) sor[i]=num[1][i];
        sort(sor+1,sor+1+n);
    }
    void build(int k,int L,int R) {
        if (L==R) return;
        int mid=(L+R)>>1;
        int same=mid-L+1;
        for (int i=L;i<=R;i++) if (num[k][i]<sor[mid]) same--;
        int Lpos=L,Rpos=mid+1;
        for (int i=L;i<=R;i++) {
            if (num[k][i]<sor[mid]) num[k+1][Lpos++]=num[k][i];
            else if (num[k][i]==sor[mid] && same>0) {
                num[k+1][Lpos++]=num[k][i];
                same--;
            }
            else num[k+1][Rpos++]=num[k][i];
            tol[k][i]=tol[k][L-1]+Lpos-L;
        }
        for (int i=L;i<=R;i++) sum[k+1][i]=sum[k+1][i-1]+num[k+1][i];
        build(k+1,L,mid);
        build(k+1,mid+1,R);
    }
    //返回值为区间第k小数，ans为区间前k小和
    LL query(int L,int R,int k,int l,int r,int dep)
    {
        if (L==R) return num[dep][L];
        int mid=(r+l)>>1;
        int cnt=tol[dep][R]-tol[dep][L-1];
        int ln1=tol[dep][L-1]-tol[dep][l-1],rn1=L-l-ln1;
        int ln2=cnt,rn2=R-L-cnt+1;
    
        if (cnt>=k){
            if (rn2>0) ans+=sum[dep+1][mid+rn2+rn1]-sum[dep+1][mid+rn1];
            int newl=l+tol[dep][L-1]-tol[dep][l-1];
            int newr=newl+cnt-1;
            return query(newl,newr,k,l,mid,dep+1);
        }
        else {
            if (ln2>0) ans-=sum[dep+1][l+ln2+ln1-1]-sum[dep+1][l+ln1-1];
            int newr=R+tol[dep][r]-tol[dep][R];
            int newl=newr-(R-L-cnt);
            return query(newl,newr,k-cnt,mid+1,r,dep+1);
        }
    }
    void print(int x,int y,int mid) {
        if ((y-x+1)%2==0) ans-=mid;
        printf("%lld\n",ans);
        ans=0;
    }
private:
    LL ans;
    int sor[maxn],num[20][maxn],tol[20][maxn];
    LL sum[20][maxn];
}tree;

//hdu3473
int main() {
    freopen("main.in","r",stdin);
    freopen("main.out","w",stdout);

    int T,t=0;scanf("%d",&T);
    while (T--) {
        printf("Case #%d:\n",++t);

        int n;scanf("%d",&n);
        tree.read(n);
        tree.build(1,1,n);

        int m;scanf("%d",&m);
        for (int i=1;i<=m;i++) {
            int L,R;scanf("%d%d",&L,&R);
            L++;R++;

            int mid=tree.query(L,R,(R-L)/2+1,1,n,1);
            tree.print(L,R,mid);
        }
        if (T!=0) puts("");
    }

    return 0;
}