#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e5+10;
int a[N],sum1[N],sum2[N];
struct node{int val,id;};
void solve(){
	stack<node>s;
	int n;
	cin>>n;
	for(int i=1;i<=n;i++)cin>>a[i];

	sum1[0]=0;
	for(int i=1;i<=n;i++) sum1[i]=sum1[i-1]+a[i];
	sum2[n+1]=0;
	for(int i=n;i>=1;i--) sum2[i]=sum2[i+1]+a[i];

	bool ans=true;
	for(int i=1;i<=n;i++){
		int Max=0;
		while(!s.empty()&&s.top().val<=a[i]){
			Max=max(Max,sum1[i-1]-sum1[s.top().id-1]);
			s.pop();
		}
		if(Max>0){
			ans=false;
			break;
		}
		s.push(node{a[i],i});
	}
	while(!s.empty()) s.pop();
	for(int i=n;i>=1;i--){
		int Max=0;
		while(!s.empty()&&s.top().val<=a[i])
		{
			Max=max(Max,sum2[i+1]-sum2[s.top().id+1]);
			s.pop();
		}
		if(Max>0){
			ans=false;
			break;
		}
		s.push(node{a[i],i});
	}
	if(ans) puts("YES");
	else puts("NO");
}
signed main(){
	int T;
	cin>>T;
	while(T--)solve();
	return 0;
}