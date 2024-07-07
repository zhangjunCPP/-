#include <bits/stdc++.h>
using namespace std;
const int N=1e5+10;
bool vis[N];
void solve(){
	int k;
	string s;
	cin>>s>>k;
	string tmp=s;
	string ans="NOTFOUND!";
	int n=s.size();
	for(int len=1;len<=n;len++){
		if(ans!="NOTFOUND!")break;
		for(int i=0;i+len-1<n;i++){
			string t;
			int j=i+len-1;
			for(int l=i;l<=j;l++)t+=s[l];
			for(int l=0;l<n;l++)vis[l]=false;
			int pos=s.find(t,0);
			while(true){
				for(int l=1;l<=len;l++)vis[pos+l-1]=true;
				pos++;
				if((pos=s.find(t,pos))==-1)break;
			}
			int sum=0;
			for(int l=0;l<n;l++)sum+=vis[l];
			if(sum==k) {
				if(ans=="NOTFOUND!")ans=t;
				else ans=min(ans,t);
			}
		}
	}
	cout<<ans<<"\n";
}
int main(){
	int T;
	cin>>T;
	while(T--)solve();
}