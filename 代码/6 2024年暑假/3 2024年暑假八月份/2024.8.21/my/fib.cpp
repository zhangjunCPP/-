#include<bits/stdc++.h>
using namespace std;
const int N=1e5+10,mod=1e9+7;
int sum0[N];
string s[N];
int main() {
	ios::sync_with_stdio(false);cin.tie(nullptr),cout.tie(nullptr);
	freopen("fib.in","r",stdin);
	freopen("fib.out","w",stdout);
	int n,T;
	cin>>n>>T;
	if(n<=10&&T<=10) {
		s[1]='0';
		s[2]='1';
		for(int i=3;i<=n;i++)s[i]=s[i-1]+s[i-2];
		while(T--) {
			string t;
			cin>>t;
			int sum=0;
			int pos=0;
			while(s[n].find(t,pos)!=-1) {
				sum++;
				int tmp=s[n].find(t,pos);
				pos=tmp+1;
			}
			cout<<sum<<"\n";
		}
		return 0;
	}
	else {
		sum0[1]=1;
		sum0[2]=0;
		for(int i=3;i<=n;i++)sum0[i]=(sum0[i-1]+sum0[i-2])%mod;
		while(T--) {
			string t;
			cin>>t;
			if(t.size()>=2)cout<<"0\n";
			else cout<<sum0[n]<<"\n";
		}
		return 0;
	}
}