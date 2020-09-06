#include <bits/stdc++.h>
using namespace std;

const int maxn=1e5+10;
int nex[maxn];

int KmpSearch(char* s,char* p)  
{  
    int i=0,j=0;
    int sLen=strlen(s),pLen=strlen(p);
    while (i<sLen && j<pLen)
    {
        if (j==-1 || s[i]==p[j]) {i++;j++;}
            else j=nex[j];
    }
    if (j==pLen)  return i-j;
        else return -1;
}

void GetNextval(char* p, int nex[])
{  
    int pLen=strlen(p);
    nex[0]=-1;
    int k=-1;
    int j=0;
    while (j<pLen-1)
    {
        if (k==-1 || p[j]==p[k])
        {
            ++j;++k;
            if (p[j]!=p[k]) nex[j]=k;
            else nex[j]=nex[k];
        }
        else k=nex[k];
    }
}

int main()
{
    /*freopen("main.in","r",stdin);
    freopen("main.out","w",stdout);*/

	//where b appear in a
    char a[10],b[10];
    scanf("%s",a);scanf("%s",b);
    GetNextval(b,nex);
    printf("%d\n",KmpSearch(a,b));

    return 0;
}
