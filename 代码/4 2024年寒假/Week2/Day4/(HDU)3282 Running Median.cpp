#include<bits/stdc++.h>
#define int long long
using namespace std;
void solve(){
	priority_queue<int,vector<int>,greater<> >q1;
	priority_queue<int>q2;
	int opt,n;
	cin>>opt>>n;
	cout<<opt<<" "<<(n+1)/2<<"\n";
	for(int i=1;i<=n;++i){
		int x;
		cin>>x;
		if(q1.empty()||q1.top()>x)q2.push(x);
		else q1.push(x);
		if(q1.size()>q2.size()){
			q2.push(q1.top());
			q1.pop();
		}
		if(q1.size()<q2.size()-(i&1)){
			q1.push(q2.top());
			q2.pop();
		}
		if(i&1)cout<<q2.top()<<" ";
		if(i%20==0)cout<<"\n";
	}
	cout<<"\n";
}
signed main(){
	int T;
	cin>>T;
	while(T--)solve();
	return 0;
}