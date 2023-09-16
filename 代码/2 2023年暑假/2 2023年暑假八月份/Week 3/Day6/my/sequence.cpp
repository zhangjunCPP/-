#include<bits/stdc++.h>
using namespace std;
const int N=1e5;
int n,k;

map<string,bool> mp;
int ans;

string t;
void solve(int x,string s,int sum){
	if(x>=n){
		if(sum>0){
			if(!mp[s]) ans++,mp[s]=true;
		} 
		return;
	}
	solve(x+1,s+t[x],sum+1);
	solve(x+1,s,sum);
} 
int sum[N];
void dfs(int x,string s){
	if(x>n){
		mp.clear();
		ans=0;
		t=s;
		string tmp="";
		solve(0,tmp,0);
		sum[ans]++;
		return;	
	}
	dfs(x+1,s+'0');
	dfs(x+1,s+'1');
}
int main(){
	freopen("sequence.in","r",stdin);
	freopen("sequence.out","w",stdout);
	cin>>n>>k;
	string tmp="";
	dfs(1,tmp);
	for(int i=1;i<=k;i++){
		cout<<sum[i]<<" ";
	}
	return 0;
}

