#include<bits/stdc++.h>
using namespace std;
const int N=2e6+10;
int t[N];
stack<pair<int,int>> sta;
int top[N],pos[N];
bool vis[N];
int main(){
	ios::sync_with_stdio(false);cin.tie(nullptr),cout.tie(nullptr);
	int n,d,T;
	cin>>n>>d>>T;
	for(int i=1;i<=n;i++)cin>>t[i];
	int ans=0;
	for(int i=1;i<=n;i++){
		if(t[i]<=T)sta.push({i,i});
		else{
			while(!sta.empty()&&sta.top().first+T-t[sta.top().first]<i){
				if(top[sta.top().second]>top[i]){
					top[i]=top[sta.top().second];
					pos[i]=sta.top().second;
				}
				sta.pop();
			}
			if(!sta.empty()){
				if(top[sta.top().second]>top[i]){
					top[i]=top[sta.top().second];
					pos[i]=sta.top().second;
				}
				vis[pos[i]]=true;
				top[i]++;
				sta.top().second=i;
			}
			else ans++,vis[i]=true;
		}
	}
	priority_queue<int> q;
	for(int i=1;i<=n;i++)if(!vis[i])q.push(top[i]);
	for(int i=1;i<=d;i++){if(q.empty())break;ans+=q.top(),q.pop();}
	cout<<n-ans;
}