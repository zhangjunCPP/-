#include<bits/stdc++.h>
using namespace std;
const int N=1e6+10;
int nxt[N][55];
void get_nxt(string s,int id) {
	//得到模式串s的nxt数组
	int len=s.length();
	int i=0,j=-1;
	nxt[id][i]=j;
	while(i<len) {
		if(j==-1||s[i]==s[j])nxt[id][++i]=++j;
		else j=nxt[id][j];
	}
}
int kmp(string s,string t,int id) {
	//查询模式串s在文本串t中出现的次数
	int len1=s.size(),len2=t.size();
	int i=0,j=0;
	int ans=0;
	while(j<len2) {
		if(i==-1||s[i]==t[j])i++,j++;
		else i=nxt[id][i];
		if(i==len1)ans++;
	}
	return ans;
}
string s[N];
int main(){
	ios::sync_with_stdio(false);cin.tie(nullptr),cout.tie(nullptr);
	int n,m,q;
	cin>>n>>m>>q;
	string c;
	cin>>c;
	for(int i=1;i<=m;i++)cin>>s[i];
	for(int i=1;i<=m;i++)get_nxt(s[i],i);
	while(q--){
		int opt;
		cin>>opt;
		if(opt==1){
			int l,r;
			cin>>l>>r;
			string tmp;
			tmp.resize(r-l+1);
			for(int i=0;i<r-l+1;i++)tmp[i]=c[i+l-1];
			int ans=0;
			for(int i=1;i<=m;i++)ans+=kmp(s[i],tmp,i);
			cout<<ans<<"\n";
		}
		else{
			int l,r;
			string t;
			cin>>l>>r>>t;
			int Siz=t.size();
			int tot=0;
			for(int i=l-1;i<r;i++){
				c[i]=t[tot];
				tot++;
				if(tot==Siz)tot=0;
			}
		}
	}
}
