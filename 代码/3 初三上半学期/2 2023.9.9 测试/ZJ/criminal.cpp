#include<bits/stdc++.h>
#define int long long 
using namespace std;
const int N=4e6+10;
int t[N],Min[N];
bool flag[N];
int val[N];
int sum[N];
priority_queue<int> q;
signed main(){
	freopen("criminal.in","r",stdin);
	freopen("criminal.out","w",stdout); 
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0); 
	int n,d,T; 
	cin>>n>>d>>T;
	int ans=n;
	for(int i=1;i<=n;i++){
		cin>>t[i];
		if(i==1) Min[i]=t[i];
		else Min[i]=min(t[i],Min[i-1]+1);
		if(Min[i]>T)  ans--;
		if(Min[i]<=T && t[i]>T)  flag[i]=true;
	}
	for(int i=1;i<=n;i++) sum[i]=sum[i-1]+(Min[i]<=T);
	for(int i=1;i<=n;i++){
		if (!flag[i]) continue;
		int sum=0;
		while(i<=n&&flag[i])sum++,i++;
		q.push(sum);
	}
	while(!q.empty()){
		ans-=q.top();
		q.pop();
		d--;
		if(d==0) break;
	}
	cout<<ans;

	return 0;
}

