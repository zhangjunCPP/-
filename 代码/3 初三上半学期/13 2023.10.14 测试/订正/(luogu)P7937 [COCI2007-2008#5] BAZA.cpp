#include<bits/stdc++.h>
#define ull unsigned long long
using namespace std;
const int N = 1e5+10;
const ull base=31;
unordered_map<ull,int>mp;
ull hash1[N],hash2[N];
string s[N],t[N];
int n,q;
vector<int> v[N];
long long ans[N];
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>s[i];
		int SIZ=s[i].size();
		for(int j=0;j<SIZ;j++)hash1[i]=(hash1[i]*base+s[i][j]-'a'+1);
		if(mp.find(hash1[i])==mp.end()) mp[hash1[i]]=i;
	}
	cin>>q;
	for(int i=1;i<=q;i++){
		cin>>t[i];
		int SIZ=t[i].size();
		for(int j=0;j<SIZ;j++)hash2[i]=(hash2[i]*base+t[i][j]-'a'+1);
		if(mp.find(hash2[i])!=mp.end()){
			v[mp[hash2[i]]].push_back(i);
			ans[i]+=mp[hash2[i]];
		}
		else {
			v[n+1].push_back(i);
			ans[i]+=n;
		}
	}
	for(int i=1;i<=n;i++) hash1[i]=0;
	for(int i=1;i<=q;i++) hash2[i]=0;
	for(int len=0;len<30;len++) {
		mp.clear();
		for(int i=1;i<=q;i++) hash2[i]=(hash2[i]*base+t[i][len]-'a'+1);
		for(int i=1;i<=n;i++) {
			if(s[i].size()<=len) continue;
			hash1[i]=(hash1[i]*base+s[i][len]-'a'+1);
			mp[hash1[i]]++;
			for(int j:v[i]){
				if(mp.find(hash2[j])!=mp.end())ans[j]+=mp[hash2[j]];
			}
		}
		for(int j:v[n+1]){
			if(mp.find(hash2[j])!=mp.end()) ans[j]+=mp[hash2[j]];
		}
	}
	for(int i=1;i<=q;i++) cout<<ans[i]<<"\n";
	return 0;
}