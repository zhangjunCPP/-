#include <bits/stdc++.h>
using namespace std;
const int N=1e6+10;
int a[N];
int l[10][N],r[10][N];
int solve(){
	string s;
	cin>>s;
	int n=s.size();
	for(int i=0;i<n;i++)a[i+1]=(s[i]-'0');
	for(int k=0;;k++){
		int j=k%10;
		for(int i=0;i<=n+1;i++)l[j][i]=i+1,r[j][i]=i-1;
		for(int i=1;i<=n;i++){
			if(k<a[i])continue;
			int L=l[(k-a[i])%10][i-1];
			int R=r[(k-a[i])%10][i+1];
			l[j][R]=min(l[j][R],L);
			r[j][L]=max(r[j][L],R);
		}
		for(int i=n-1;i;i--)l[j][i]=min(l[j][i],l[j][i+1]);
		for(int i=2;i<=n;i++)r[j][i]=max(r[j][i],r[j][i-1]);
		if(l[j][n]<=1||r[j][1]>=n)return k;
	}
}
int main() {
	ios::sync_with_stdio(false);cin.tie(nullptr),cout.tie(nullptr);
	int T;
	cin>>T;
	for(int i=1;i<=T;i++)cout<<"Case #"<<i<<": "<<solve()<<"\n";
}