#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e5+10;
int v[N];

int n;

int ans;
vector<int> ANS;

vector<int> now;
bool vis[N];
void dfs(int x){
	if(x>n){
		stack<int> s;
		int num=0;
		for(int i:now){
			while(s.size()&&s.top()>i){
				num+=v[i];
				s.pop();
			} 
			s.push(i);
		}
		if(num>ans) {
			ans=num;
			ANS=now;
		}
		return;
	}
	for(int i=1;i<=n;i++){
		if(!vis[i]){
			vis[i]=true;
			now.push_back(i);
			dfs(x+1);
			now.pop_back();
			vis[i]=false;
		}
	}
	
	
}
signed main(){

	freopen("game.in","r",stdin);
//	freopen("game.out","w",stdout);
	cin>>n;
	for(int i=1;i<=n;i++) cin>>v[i];
	bool flag1=true,flag2=true;
	for(int i=1;i<=n;i++){
		if(v[i]!=i) flag1=false;
		if(v[i]!=n-i+1) flag2=false;
	}
	if(flag1){
		int num=0;
		for(int i=1;i<n;i++) num+=v[i];
		cout<<num<<"\n";
		for(int i=n;i>=1;i--) cout<<i<<" ";
		return 0;
	}
	if(flag2){
		cout<<v[1]*(n-1)<<"\n";
		for(int i=2;i<=n;i++) cout<<i<<" ";
		cout<<1;
		return 0;
	}
	if(n<=10){
		dfs(1);
		cout<<ans<<"\n";
		for(int i:ANS) cout<<i<<" ";
		return 0;
	}
	
	
	return 0;
}


//
