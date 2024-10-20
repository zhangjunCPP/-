#include<bits/stdc++.h>
using namespace std;
const int N=1e6+10;
int a[N];
vector<int> v[N];
int cnt[N];
int main(){
	ios::sync_with_stdio(false);cin.tie(nullptr),cout.tie(nullptr);
	int n,k;
	cin>>n>>k;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		v[(i-1)%k+1].push_back(a[i]);
	}
	for(int i=1;i<=k;i++)sort(v[i].begin(), v[i].end());
	for(int i=1;i<=n;i++){
		int tmp=(i-1)%k+1;
		cout<<v[tmp][cnt[tmp]++]<<" ";
	}
}