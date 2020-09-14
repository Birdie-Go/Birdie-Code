#include <bits/stdc++.h>
using namespace std;

const int maxn=1e3+10;
int n,m,e,girl[maxn];
bool used[maxn],line[maxn][maxn];

bool find(int x) {
	for (int j=1;j<=m;j++){
		if (line[x][j]==true && used[j]==false) {
			used[j]=1;
			if (girl[j]==0 || find(girl[j])) {
				girl[j]=x;
				return true;
			}
		}
	}
	return false;
}

int main() {
    freopen("main.in","r",stdin);
    freopen("main.out","w",stdout);

    scanf("%d%d%d",&n,&m,&e);
	//n left(boys),m right(girls),e edges
    for (int i=1;i<=e;i++) {
        int x,y;scanf("%d%d",&x,&y);
		line[x][y]=true;
    }
    
	int all=0;
    for (int i=1;i<=n;i++) {
        memset(used,0,sizeof(used));
        if (find(i)) all+=1;
    }
	printf("%d\n",all);

    return 0;
}