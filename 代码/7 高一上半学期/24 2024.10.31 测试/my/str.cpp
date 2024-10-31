#include<bits/stdc++.h>
using namespace std;
const int N=1e5+10;
int p[N];
string t[N];

void solve(){
	string s;
	cin>>s;
	int n=s.size();
	bool flag=true;
	for(int i=0;i<n;i++)if(s[i]!='a'){flag=false;break;}
	if(flag){
		for(int i=0;i<n;i++)cout<<"z";
		cout<<"\n";
		return;
	}
	int tot=0;
	for(int i=0;i<n;i++){
		for(int j=1;j<=26;j++)p[j]=0;
		int now=26;
		string tmp;
		for(int j=i;j<n;j++){
			if(!p[s[j]-'a'+1])p[s[j]-'a'+1]=now,now--;
			tmp.push_back(p[s[j]-'a'+1]+'a'-1);
		}
		t[++tot]=tmp;
	}
	sort(t+1,t+tot+1);
	cout<<t[tot]<<"\n";
}
signed main(){
	freopen("str.in","r",stdin);
	freopen("str.out","w",stdout);
	ios::sync_with_stdio(false);cin.tie(nullptr),cout.tie(nullptr);
	int T;
	cin>>T;
	while(T--)solve();
}
/*
其实T就是S的一段连续字串
序列p就是一段[1,26]的排列

*/