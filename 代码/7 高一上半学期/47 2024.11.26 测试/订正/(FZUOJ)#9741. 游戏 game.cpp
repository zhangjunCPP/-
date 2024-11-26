#include<bits/stdc++.h>
#define ull unsigned long long
using namespace std;
const int N=1000+10;
const ull p=1331;
string s[N];

ull Hash[N],pw[N];
ull Hash_T[N];
int a[N],tot;
unordered_map<ull,bool>mp;
int main(){
	ios::sync_with_stdio(false);cin.tie(nullptr),cout.tie(nullptr);
	int n,k;
	cin>>n>>k;
	int lgn=log2(n);
	lgn++;
	lgn=min(lgn,k);
	pw[0]=1;
	for(int i=1;i<=k;i++)pw[i]=pw[i-1]*p;
	for(int i=1;i<=n;i++){
		cin>>s[i];
		for(int j=lgn;j<k;j++)s[i][j]='0';
		for(int j=0;j<lgn;j++)Hash[i]=Hash[i]*p+s[i][j];
	}
	string t;
	for(int i=0;i<lgn;i++)t.push_back('0');
	t.push_back('0');
	for(int i=1;i<=n;i++){
		for(int j=0;j<lgn;j++)Hash_T[i]=Hash_T[i]*p+t[j];
		t[0]++;
		for(int j=0;j<lgn;j++)if(t[j]=='2')t[j]='0',t[j+1]++;
	}
	int ans=0;
	for(int S=0;S<(1<<lgn);S++){
		mp.clear();
		for(int j=0;j<lgn;j++){
			if((S>>j)&1){
				for(int i=1;i<=n;i++){
					if(s[i][j]=='1')Hash[i]-=pw[lgn-j-1];
					mp[Hash[i]]=true;
				}
			}
		}
		int sum=0;
		for(int i=1;i<=n;i++){
			if(mp.count(Hash_T[i]))sum++;
			else break;
		}
		ans=max(ans,sum);
		for(int j=0;j<lgn;j++)
			if((S>>j)&1)
				for(int i=1;i<=n;i++)if(s[i][j]=='1')Hash[i]+=pw[lgn-j-1];
	}
	cout<<ans;

}
