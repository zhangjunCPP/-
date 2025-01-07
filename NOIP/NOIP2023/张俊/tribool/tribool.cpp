#include<bits/stdc++.h>
using namespace std;
const int N=1e5+10;
int c,T;
struct node{
	char opt;
	int u,v;
}a[N];
char s[N];
char tmp[N];
int n,m;
int ans;
void dfs(int now){
	if(now==n+1){
		for(int i=1;i<=n;i++) tmp[i]=s[i];
		for(int i=1;i<=m;i++) {
			if(a[i].opt=='+')tmp[a[i].u]=tmp[a[i].v];
			else if(a[i].opt=='-') {
				char tmpp=tmp[a[i].v];
				if(tmpp=='U') tmp[a[i].u]='U';
				else if(tmpp=='T') tmp[a[i].u]='F';
				else tmp[a[i].u]='T';
			}
			else tmp[a[i].u]=a[i].opt;
		}
		bool flag=true;
		for(int i=1;i<=n;i++) {
			if(tmp[i]!=s[i]) {flag=false;break;}
		}
		if(flag) {
			int sum=0;
			for(int i=1;i<=n;i++) if(s[i]=='U') sum++;
			ans=min(ans,sum);
		}
		return;
	}
	s[now]='T';
	dfs(now+1);
	s[now]='F';
	dfs(now+1);
	s[now]='U';
	dfs(now+1);
}
void solve(){
	cin>>n>>m;
	for(int i=1;i<=m;i++) {
		cin>>a[i].opt;
		if(a[i].opt=='+' || a[i].opt=='-')cin>>a[i].u>>a[i].v;
		else cin>>a[i].u;
	}
	if(c==1||c==2) {
		ans=0x3f3f3f3f;
		dfs(1);
		cout<<ans<<"\n";
		return;
	}
	if(c==3||c==4) {
		for(int i=1;i<=n;i++) s[i]='T';
		for(int i=1;i<=m;i++)s[a[i].u]=a[i].opt;
		int sum=0;
		for(int i=1;i<=n;i++) if(s[i]=='U') sum++;
		cout<<sum<<"\n";
		return;
	}
}
int main(){
	freopen("tribool.in","r",stdin);
	freopen("tribool.out","w",stdout);
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	cin>>c>>T;
	while(T--) solve();
}