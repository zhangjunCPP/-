#include<bits/stdc++.h>
using namespace std;
int ans;
map<string,bool> mp;
void dfs1(string s,int lastid,int lastopt){
	if(mp[s]==true) return;
	mp[s]=true;
	ans++;
	int len=s.size();
	for(int i=0;i<len;i++) {
		if(s[i]=='1'){
			if(i>=2&&(s[i-1]=='1'&&s[i-2]=='0')) {
				if(i!=lastid||(i==lastid&&lastopt==1)){
					string tmp=s;
					tmp[i-2]='1';
					tmp[i]='0';
					dfs1(tmp,i-2,1);
				}
			}
			if(i<len-2&&(s[i+1]=='1'&&s[i+2]=='0')) {
				if(i!=lastid||(i==lastid&&lastopt==2)){
					string tmp=s;
					tmp[i+2]='1';
					tmp[i]='0';
					dfs1(tmp,i+2,2);
				}
			}
		}
	}
}


int n;

string s;
string tmp;
void dfs2(int now){
	if(now>=n) {
		mp.clear();
		dfs1(tmp,-1,-1);
		return;
	}
	if(s[now]=='?') {
		tmp[now]='1';
		dfs2(now+1);
		tmp[now]='0';
		dfs2(now+1);
	}
	else {
		dfs2(now+1);
	}
}

int main(){
	freopen("jumpgo.in","r",stdin);
	freopen("jumpgo.out","w",stdout);
	cin>>n;
	cin>>s;
	tmp=s;
	dfs2(0);
	cout<<ans;

	return 0;
}

