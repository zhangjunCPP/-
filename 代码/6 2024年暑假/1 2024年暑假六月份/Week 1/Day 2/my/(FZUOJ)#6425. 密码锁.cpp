#include<bits/stdc++.h>
using namespace std;
int n,T;
int f(string s1,string s2){
	int Max=-1;
	for(int i=0;i<n;i++){
		int up=0,down=0 ;
		if(s1[i]-'0'<s2[i]-'0')up=(s2[i]-'0')-(s1[i]-'0'),down=10-up;
		else down=(s1[i]-'0')-(s2[i]-'0'),up=10-down;
		Max=max(Max,min(up,down));
	}
	return Max;
}
string calc(string s,int l,int r,int dep,bool opt){
	for(int i=l;i<=r;i++){
		if(opt){
			s[i]+=dep;
			if(s[i]-'0'>=10)s[i]-=10;
		}
		else{
			s[i]-=dep;
			if(s[i]-'0'<0)s[i]+=10;
		}
	}
	return s;
}
bool dfs(string s1,string s2,int dep){
	if(dep<0)return false;
	if(f(s1,s2)>dep)return false;
	if(s1==s2)return true;
	string tmp=s1;
	for(int i=0;i<n;i++){
		if(s1[i]==s2[i])continue;
		int up=0,down=0;
		if(s1[i]-'0'<s2[i]-'0')up=(s2[i]-'0')-(s1[i]-'0'),down=10-up;
		else down=(s1[i]-'0')-(s2[i]-'0'),up=10-down;
		for(int j=i;j<n;j++){
			if(s1[j]==s2[j])continue;
			s1=calc(s1,i,j,up,1);
			if(dfs(s1,s2,dep-up))return true;
			s1=tmp;
			s1=calc(s1,i,j,down,0);
			if(dfs(s1,s2,dep-down))return true;
			s1=tmp;
			int upp=0,downn=0;
			if(s1[j]-'0'<s2[j]-'0')upp=(s2[j]-'0')-(s1[j]-'0'),downn=10-upp;
			else downn=(s1[j]-'0')-(s2[j]-'0'),upp=10-downn;
			s1=calc(s1,i,j,upp,1);
			if(dfs(s1,s2,dep-upp))return true;
			s1=tmp;
			s1=calc(s1,i,j,downn,0);
			if(dfs(s1,s2,dep-downn))return true;
			s1=tmp;
		}
	}
	return false;
}
void solve(){
	string s1,s2;
	cin>>s1>>s2;
	int ans=f(s1,s2);
	while(!dfs(s1,s2,ans))ans++;
	cout<<ans<<"\n";
}
int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr),cout.tie(nullptr);
	cin>>n>>T;
	while(T--)solve();
}