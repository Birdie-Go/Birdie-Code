#include<iostream>
#include<vector>
#include<cstdio>
#include<set>
#include<cstring>
using namespace std;
typedef long long ll;
class Bignum{ // keep number>0 while the whole calculation
private:
	vector<int>c;
	void assign(long long x){
		c.clear();
		while(x){
			c.push_back(x%10);
			x/=10;
		}
	}
	void assign(const string &str){
		c.clear();
		int s=str.size()-1;
		for(;s>=0;--s){
			c.push_back(str[s]-'0');
		}
	}
	void erase_front_zero(){
		int s=c.size()-1;
		while(s>0&&c[s]==0) --s;
		c.resize(s+1);
	}
public:
	Bignum(){
		assign(0);
	}
	Bignum(long long x){
		assign(x);
	}
	Bignum(const string &str){
		assign(str);
	}
	Bignum operator + (const Bignum &rhs) const{
		Bignum tmp;
		vector<int> &vec=tmp.c;
		for(int i=0,d=0;;++i){
			if(i>=rhs.c.size()&&i>=c.size()&&!d) break;
			int add=0;
			if(i<rhs.c.size()) add+=rhs.c[i];
			if(i<c.size()) add+=c[i];
			vec.push_back((d+add)%10);
			d=(d+add)/10;
		}
		return tmp;
	}
	Bignum operator + (long long rhs) const{
		Bignum tmp(*this);
		int add=0;
		for(int i=0;rhs||add;++i,rhs/=10){
			if(i<tmp.c.size()){
				tmp.c[i]+=rhs%10+add;
			} else {
				tmp.c.push_back(rhs%10+add);
			}
			add=tmp.c[i]/10;
			tmp.c[i]%=10;
	}
		return tmp;
	}
	Bignum operator - (const Bignum &rhs) const{
		Bignum tmp;
		vector<int> &vec=tmp.c;
		vec.assign(c.begin(),c.end());
		for(int i=0,d=0;;++i){
			if(i>=rhs.c.size()&&!d) break;
			if(i<rhs.c.size()) vec[i]-=rhs.c[i];
			vec[i]-=d;d=0;
			if(vec[i]<0){
				vec[i]+=10;
				d=1;
			}
		}
		tmp.erase_front_zero();
		return tmp;
	}
	Bignum operator * (const Bignum &rhs) const{
		Bignum tmp;
		vector<int> &vec=tmp.c;
		vec.resize(c.size()+rhs.c.size());
		for(int i=0;i<c.size();++i)
			for(int j=0;j<rhs.c.size();++j){
				vec[i+j]+=c[i]*rhs.c[j];
			}
		for(int i=0,d=0;i<vec.size();++i){
			vec[i]+=d;d=0;
			if(vec[i]>=10){
				d=vec[i]/10;
				vec[i]%=10;
			}
		}
		tmp.erase_front_zero();
		return tmp;
	}
	Bignum operator / (const long long &rhs) const{
		string ans("0");
		long long now=0;
		int n=c.size()-1;
		for(int i=n;i>=0;--i){
			now=now*10+c[i];
			if(now>=rhs){
				ans+=now/rhs+'0';
				now%=rhs;
				n=i-1;break;
			}
		}
		for(int i=n;i>=0;--i){
			now=now*10+c[i];
			ans+=now/rhs+'0';
			now%=rhs;
		}
		Bignum tmp(ans);
		tmp.erase_front_zero();
		return tmp;
	}
	Bignum operator = (const Bignum &rhs){
		if(&rhs==this) return *this;
		c.assign(rhs.c.begin(),rhs.c.end());
		return *this;
	}
    bool operator < (const Bignum &rhs) {
        if (rhs.c.size()!=c.size()) return c.size()<rhs.c.size();
        for (int i=c.size()-1;i>=0;i--) {
            if (c[i]!=rhs.c[i]) return c[i]<rhs.c[i];
        }
        return false;
    }
	friend istream &operator >> (istream &in,Bignum &rhs){
		string tmp;
		in>>tmp;
		rhs.assign(tmp);
		return in;
	}
	friend ostream &operator << (ostream &out,const Bignum &rhs){
		int s=rhs.c.size()-1;
		for(;s>=0;--s){
			out<<rhs.c[s];
		}
		return out;
	}
};

const int maxn=1000+10;
Bignum f[maxn];

void ready() {
    f[0]=Bignum(0);
    f[1]=Bignum(3);
    for (int i=2;i<=1000;i++) {
        f[i]=f[i-1]*6-f[i-2]+2;
    }
}

char ch[maxn];

int main(){
    ready();

	int T;cin>>T;
    while (T--) {
        cin>>ch;
        Bignum now(ch);
        for (int i=0;i<=1000;i++) {
            if (f[i]<now) continue;
            cout<<f[i]<<endl;
            break;
        }
    }
}