#include <bits/stdc++.h>
using namespace std;
const int N=1e5+10;
int a[N],b[N];
int pos[N];
void solve(){
	int n;
	cin>>n;
	for(int i=1;i<=n;i++)cin>>a[i],b[a[i]]=i;
	int cnt=0;
	for(int l=1;l<=n;l++){
		int r=l;
		while(r<n&&b[r+1]>b[r])r++;
		cnt++;
		for(int i=l;i<=r;i++)pos[i]=cnt;
		l=r;
	}
	int tmp=(int)log2(cnt*2-1);
	vector<string>Ans;
	for(int j=0;j<tmp;j++){
		string ans;
		queue<int> q1,q2;
		for(int i=1;i<=n;i++){
			if((pos[a[i]]-1)>>j&1)q2.push(a[i]),ans.push_back('B');
			else q1.push(a[i]),ans.push_back('A');
		}
		for(int i=1;i<=n;i++){
			if(!q1.empty())a[i]=q1.front(),q1.pop();
			else a[i]=q2.front(),q2.pop();
		}
		Ans.push_back(ans);
	}
	reverse(Ans.begin(),Ans.end());
	cout<<Ans.size()<<"\n";
	for(auto i:Ans)cout<<i<<"\n";
}
int main(){
	ios::sync_with_stdio(false);cin.tie(nullptr),cout.tie(nullptr);
	int T;
	cin>>T;
	while(T--)solve();
}