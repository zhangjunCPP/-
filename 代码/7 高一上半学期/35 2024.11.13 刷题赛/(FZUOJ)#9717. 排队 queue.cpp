#include<bits/stdc++.h>
using namespace std;
const int N=1e6+10;
int a[N];
int main(){
	ios::sync_with_stdio(false);cin.tie(nullptr),cout.tie(nullptr);
	int n;
	cin>>n;
	for(int i=1;i<=n;i++)cin>>a[i];
	int Min=n+10,Max=0;
	vector<int>ans;
	for(int i=1;i<n;i++){
		int tmp_Min=min(Min,a[i]);
		int tmp_Max=max(Max,a[i]);
		if(tmp_Min==1&&tmp_Max==i){
			ans.push_back(i);
			swap(a[i],a[i+1]);
		}
		Min=min(Min,a[i]);
		Max=max(Max,a[i]);
	}
	cout<<ans.size()<<"\n";
	for(int i:ans)cout<<i<<" ";
}