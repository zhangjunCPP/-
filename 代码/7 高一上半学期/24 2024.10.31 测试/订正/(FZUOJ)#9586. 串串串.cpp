#include<bits/stdc++.h>
#define ull unsigned long long
using namespace std;
const int N=1e5+10;
const ull P=1331;
ull pw[N];
void init(){
	pw[0]=1;
	for(int i=1;i<N;i++)pw[i]=pw[i-1]*P;
}
ull Hash[N][30];
ull query(int ch,int l,int r){return Hash[r][ch]-Hash[l-1][ch]*pw[r-l+1];}
string s;
int n;
int sa_tmp[30],sa_ans[30];
int rk_tmp[30],rk_ans[30];
bool check(int x,int y){
	int ans=n-y+1;
	for(int i=0;i<26;i++){
		int l=1,r=min(n-y+1,ans);
		while(l<=r){
			int mid=(l+r)>>1;
			if(query(sa_tmp[i],x,x+mid-1)==query(sa_ans[i],y,y+mid-1))ans=mid,l=mid+1;
			else r=mid-1;
		}
	}
	if(y+ans>n)return true;
	return rk_tmp[s[x+ans-1]-'a']<rk_ans[s[y+ans-1]-'a'];
}
void solve(){
	cin>>s;
	n=s.size();
	for(int i=0;i<26;i++) sa_tmp[i]=sa_ans[i]=rk_tmp[i]=rk_ans[i]=i;
	for(int i=1;i<=n;i++)for(int j=0;j<26;j++)Hash[i][j]=Hash[i-1][j]*P+(s[i-1]-'a'==j);
	int last=n+1;
	for(int i=n;i;i--){
		int ch=s[i-1]-'a';
		for(int j=rk_tmp[ch];j;j--)sa_tmp[j]=sa_tmp[j-1];
		sa_tmp[0]=ch;
		for(int j=0;j<26;j++)rk_tmp[sa_tmp[j]]=j;
		if(last==n+1||check(i,last)){
			for(int j=0;j<26;j++)sa_ans[j]=sa_tmp[j],rk_ans[j]=rk_tmp[j];
			last=i;
		}
	}
	for(int i=last;i<=n;i++)cout<<char('z'-rk_ans[s[i-1]-'a']);
	cout<<"\n";
}
int main(){
	ios::sync_with_stdio(false);cin.tie(nullptr),cout.tie(nullptr);
	init();
	int T;
	cin>>T;
	while(T--)solve();
}