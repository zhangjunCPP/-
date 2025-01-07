#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N=2e5+10;
int v[N];
int a[N];
int L[N],R[N];
signed main(){
	int n,q;
	cin>>n>>q;
	for(int i=1;i<=n;++i)cin>>v[i];
	for(int i=1;i<n;++i)a[i]=llabs(v[i+1]-v[i]);
	while(q--){
		memset(L,0,sizeof L);
		memset(R,0,sizeof R);
		int l,r;
		cin>>l>>r;
		r--;
		int tmp=0;
		for(int i=l;i<=r;++i)a[++tmp]=llabs(v[i+1]-v[i]);
		int len=r-l+1;
		stack<int>s;
		for(int i=1;i<=len;++i){
			while(!s.empty()&&a[s.top()]<a[i]){
				R[s.top()]=i-s.top();
				s.pop();
			}
			if(s.empty())L[i]=i;
			else L[i]=i-s.top();
			s.push(i);
		}
		while(!s.empty()){
			R[s.top()]=len+1-s.top();
			s.pop();
		}
		int ans=0;
		for(int i=1;i<=len;++i)ans+=a[i]*L[i]*R[i];
		cout<<ans<<"\n";
	}
	return 0;
}