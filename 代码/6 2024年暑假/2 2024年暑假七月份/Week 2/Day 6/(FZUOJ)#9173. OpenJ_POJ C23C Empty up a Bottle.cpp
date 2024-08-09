#include<bits/stdc++.h>
#define int long long
#define ll __int128
using namespace std;
const int N=1e7+10;
int qpow(int x,int y,int mod) {
	int ans=1;
	while(y) {
		if(y&1)ans=(ll)ans*x%mod;
		x=(ll)x*x%mod;
		y>>=1;
	}
	return ans;
}
int prime[N],cnt;
bool vis[N];
void init() {
	for(int i=2;i<N;i++) {
		if(!vis[i])prime[++cnt]=i;
		for(int j=1;j<=cnt&&i*prime[j]<N;j++) {
			vis[i*prime[j]]=true;
			if(i%prime[j]==0)break;
		}
	}
}
int phi(int x) {
	int ans=x;
	for(int i=1;prime[i]*prime[i]<=x&&i<=cnt;i++) {
		if(x%prime[i]==0) {
			ans=ans/prime[i]*(prime[i]-1);
			while(x%prime[i]==0)x/=prime[i];
		}
	}
	if(x!=1)ans=ans/x*(x-1);
	return ans;
}
bool f(int x){return x&1;}
struct node {
	int x,y;
	int tot;
};
vector<node>ans;
int mp[5][5];
void print() {
	mp[1][3]=mp[3][1]=3;
	mp[1][2]=mp[2][1]=1;
	mp[2][3]=mp[3][2]=2;
	cout<<ans.size()<<"\n";
	for(auto it:ans)cout<<mp[it.x][it.y]<<" "<<it.tot<<"\n";
}
int id[N];
signed main() {
	init();
	int A,B,C;
	cin>>A>>B>>C;
	while(A&&B&&C) {
		while(!f(A)&&!f(B)&&!f(C))A/=2,B/=2,C/=2;
		if(!f(A)&&f(B)&&f(C)){
			ans.push_back({3,2,1});
			if(B>C)B-=C,C*=2;
			else C-=B,B*=2;
		}
		else if(f(A)&&!f(B)&&f(C)) {
			ans.push_back({1,3,1});
			if(A>C)A-=C,C*=2;
			else C-=A,A*=2;
		}
		else if(f(A)&&f(B)&&!f(C)) {
			ans.push_back({1,2,1});
			if(A>B)A-=B,B*=2;
			else B-=A,A*=2;
		}
		else break;
	}
	if(f(A)&&f(B)&&f(C)) {
		ans.push_back({1,2,1});
		if(A>B)A-=B,B*=2;
		else B-=A,A*=2;
	}
	if(!A||!B||!C){print();return 0;}

	id[1]=1,id[2]=2,id[3]=3;
	if(!f(C)) {
		if(f(A))swap(A,C),swap(id[1],id[3]);
		else swap(B,C),swap(id[2],id[3]);
	}
	if(B>A)swap(A,B),swap(id[1],id[2]);
	//调整为A>B的顺序

	while(A&&B&&C) {
		if(A==B) {
			ans.push_back({id[1],id[2],1});
			print();
			return 0;
		}
		int tmp=log2(ceil(1.0*(A+B)/(B*2)));
		ans.push_back({id[1],id[2],tmp});
		int tmp_B=B;
		int mod=A+B;
		A=(ll)A*qpow(2,tmp,mod)%mod;
		B=(ll)B*qpow(2,tmp,mod)%mod;
		mod=B+C;
		int Phi=phi(B+C);
		ans.push_back({id[2],id[3],(Phi-tmp%Phi)%Phi});
		B=tmp_B;
		C=(ll)C*qpow(2,(Phi-tmp%Phi)%Phi,mod)%mod;
		if(B>A)swap(A,B),swap(id[1],id[2]);
	}
	return 0;
}