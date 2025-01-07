#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e5+10;
int x[N];
int c[N];
priority_queue<int,vector<int>,greater<int> >q;
signed main(){
	int n,k;
	cin>>n>>k;
	for(int i=1;i<=n;i++)cin>>x[i];
	int a;
	cin>>a;
	for(int i=1;i<=n;i++)cin>>c[i];
	int ans=0;
	for(int i=1;i<=n;i++){
		q.push(c[i]);
		while(k<x[i]){
			if(q.empty()){puts("-1");return 0;}
			k+=a;
			ans+=q.top();
			q.pop();
		}
	}
	cout<<ans;
	return 0;
}