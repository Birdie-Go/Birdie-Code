#include <bits/stdc++.h>
using namespace std;

const int maxn=100;
int wa[maxn],wb[maxn],wv[maxn],wt[maxn];

int cmp(int *r,int a,int b,int l) {return r[a]==r[b] && r[a+l]==r[b+l];}

void da(int *r,int *sa,int n,int m)
{
    int i,j,p,*x=wa,*y=wb,*t; 
    for (i=0;i<m;i++) wt[i]=0; 
    for (i=0;i<n;i++) wt[x[i]=r[i]]++; 
    for (i=1;i<m;i++) wt[i]+=wt[i-1]; 
    for (i=n-1;i>=0;i--) sa[--wt[x[i]]]=i; 
    for (j=1,p=1;p<n;j*=2,m=p) 
    { 
        for (p=0,i=n-j;i<n;i++) y[p++]=i; 
        for (i=0;i<n;i++) if(sa[i]>=j) y[p++]=sa[i]-j; 
        for (i=0;i<n;i++) wv[i]=x[y[i]]; 
        for (i=0;i<m;i++) wt[i]=0; 
        for (i=0;i<n;i++) wt[wv[i]]++; 
        for (i=1;i<m;i++) wt[i]+=wt[i-1]; 
        for (i=n-1;i>=0;i--) sa[--wt[wv[i]]]=y[i]; 
        for (t=x,x=y,y=t,p=1,x[sa[0]]=0,i=1;i<n;i++) x[sa[i]]=cmp(y,sa[i-1],sa[i],j)?p-1:p++; 
    } 
    return; 
}

int rk[maxn],height[maxn];
void calheight(int *r,int *sa,int n)
{
    int i,j,k=0; 
    for (i=1;i<=n;i++) rk[sa[i]]=i; 
    for (i=0;i<n;height[rk[i++]]=k) 
        for (k?k--:0,j=sa[rk[i]-1];r[i+k]==r[j+k];k++); 
    return; 
}

int r[maxn],sa[maxn];

int main()
{
    freopen("main.in","r",stdin);
    freopen("main.out","w",stdout);

	char ch[10];
	scanf("%s",ch);
	int L=strlen(ch);
	
	//add an new smallest char to ch[L];
	for (int i=0;i<L;i++) r[i]=ch[i]-'a'+1;
	r[L]=0;
	da(r,sa,L+1,27);
	calheight(r,sa,L+1);
	
	for (int i=0;i<=L;i++) cout<<"sa["<<i<<"]="<<sa[i]<<endl;//which string rank i
	for (int i=0;i<=L;i++) cout<<"rk["<<i<<"]="<<rk[i]<<endl;//rank of string i..n
	for (int i=0;i<=L;i++) cout<<"height["<<i<<"]="<<height[i]<<endl;
    //longest former same of suffix i and suffix i-1
	
	return 0;
}
