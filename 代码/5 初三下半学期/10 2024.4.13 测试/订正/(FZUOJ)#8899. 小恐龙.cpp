#include<bits/stdc++.h>
using namespace std;
const int N=1e6+10;
int dp[N];
bool flag[N];
int x[N],t[N];
int main(){
	ios::sync_with_stdio(false);cin.tie(nullptr),cout.tie(nullptr);
	int n,k,m;
	cin>>n>>k>>m;
	memset(dp,0x3f,sizeof dp);
	dp[1]=0;
	for(int i=2;i<=n;i++)dp[i]=min(dp[i-1],(i-k>0?dp[i-k]+1:0x3f3f3f3f));
	for(int i=1;i<=m;i++)cin>>x[i]>>t[i];
	queue<int> q;
	for(int i=1;i<=m;i++){
		if(dp[x[i]]==0x3f3f3f3f){
			flag[x[i]]=true;
			cout<<(dp[t[i]]==0x3f3f3f3f?-1:dp[t[i]])<<"\n";
			continue;
		}
		dp[x[i]]=0x3f3f3f3f;
		q.push(x[i]);
		while(!q.empty()){
			int now=q.front();
			q.pop();
			if(flag[now])continue;
			if(now+1<=n){
				if(!flag[now+1]){
					int tmp=dp[now+1];
					dp[now+1]=min(dp[now],(now+1-k>0?dp[now+1-k]+1:0x3f3f3f3f));
					if(dp[now+1]>tmp)q.push(now+1);
				}
			}
			if(now+k<=n){
				if(!flag[now+k]){
					int tmp=dp[now+k];
					dp[now+k]=min(dp[now+k-1],dp[now]+1);
					if(dp[now+k]>tmp)q.push(now+k);
				}
			}
		}
		flag[x[i]]=true;
		cout<<(dp[t[i]]==0x3f3f3f3f?-1:dp[t[i]])<<"\n";
	}
}