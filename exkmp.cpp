#include <bits/stdc++.h>
using namespace std;

const int maxn=1e5+10;
int nex[maxn],ex[maxn];

void GETNEXT(char *str)
{
    int i=0,j,po,len=strlen(str);
    nex[0]=len;
    while(str[i]==str[i+1] && i+1<len) i++;
    nex[1]=i;
    po=1;
    for (i=2;i<len;i++)
    {
        if(nex[i-po]+i<nex[po]+po) nex[i]=nex[i-po];
        else
        {
            j=nex[po]+po-i;
            if (j<0) j=0;
            while (i+j<len && str[j]==str[j+i])
            j++;
            nex[i]=j;
            po=i;
        }
    }
}

void EXKMP(char *s1,char *s2)
{
    int i=0,j,po,len=strlen(s1),l2=strlen(s2);
    GETNEXT(s2);
    while (s1[i]==s2[i] && i<l2 && i<len) i++;
    ex[0]=i;
    po=0;
    for(i=1;i<len;i++)
    {
        if (nex[i-po]+i<ex[po]+po) ex[i]=nex[i-po];
        else
        {
            j=ex[po]+po-i;
            if (j<0) j=0;
            while (i+j<len && j<l2 && s1[j+i]==s2[j]) j++;
            ex[i]=j;
            po=i;
        }
    }
}

int main()
{
	//ex[i] is the same in a[i..n] and b
    char a[10],b[10];
    scanf("%s",a);scanf("%s",b);
    GETNEXT(a);
    EXKMP(a,b);
    for (int i=0;i<strlen(a);i++) printf("i=%d:%d\n",i,ex[i]);
	
	return 0;
}
/*
abbabc
abc
i=0:2
i=1:0
i=2:0
i=3:3
i=4:0
i=5:0
*/
