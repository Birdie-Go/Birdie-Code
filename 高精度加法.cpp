#include <bits/stdc++.h>

int La,Lb;
int a[2000],b[2000],c[2000];

void add()
{
	for (int i=1;i<=La+1;i++) c[i]=0;
	for (int i=1;i<=La+1;i++)
	{
		c[i]=c[i]+a[i]+b[i];
		c[i+1]+=c[i]/10;
		c[i]%=10;
	}
	for (int i=(c[La+1]>0)?La+1:La;i>=1;i--) printf("%d",c[i]);
	printf("\n");
}

void swap(int &a,int &b) {int m=a;a=b;b=m;}

void exchange()
{
	if (La<Lb) for (int i=1;i<=Lb;i++) swap(a[i],b[i]);
	swap(La,Lb);
}

void reserve()
{
	for (int i=1;i<=La/2;i++) swap(a[i],a[La-i+1]);
	for (int i=1;i<=Lb/2;i++) swap(b[i],b[Lb-i+1]);
	for (int i=Lb+1;i<=La+Lb+1;i++) b[i]=0;
	for (int i=La+1;i<=La+Lb+1;i++) a[i]=0;
}

int main()
{
	while (1)
	{
		char ch[1000];
		scanf("%s",ch);int L=strlen(ch);
		
		char app=' ';La=0;Lb=0;
		for (int i=0;i<L;i++)
		{
			if ('0'<=ch[i] && ch[i]<='9')
				if (app==' ') a[++La]=ch[i]-'0';
					else b[++Lb]=ch[i]-'0';
			else app=ch[i];
		}
		
		exchange();
		reserve();
		add();
	}
	
	return 0;
}
