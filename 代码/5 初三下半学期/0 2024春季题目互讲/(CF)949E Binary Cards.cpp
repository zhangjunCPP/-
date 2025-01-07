#include <bits/stdc++.h>
using namespace std;
vector<int> a;
vector<int> calc(int k){
	if(k>20)return vector<int>(0);
	bool flag=true;
	for(int i:a)if(i&1){flag=false;break;}
	if(flag){
		for(int &i:a)i>>=1;
		return calc(k+1);
	}
	vector<int> tmp=a;
	vector<int> ans1,ans2;
	for(int &i:a)if(i&1)i=(i-1)>>1;else i>>=1;
	sort(a.begin(),a.end());
	a.erase(unique(a.begin(),a.end()),a.end());
	ans1=calc(k+1);
	ans1.push_back(1<<k);
	a=tmp;
	for(int &i:a)if(i&1)i=(i+1)>>1;else i>>=1;
	sort(a.begin(),a.end());
	a.erase(unique(a.begin(),a.end()),a.end());
	ans2=calc(k+1);
	ans2.push_back(-(1<<k));
	return ans1.size()<=ans2.size()?ans1:ans2;
}
int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr),cout.tie(nullptr);
	int n;
	cin>>n;
	for(int i=1;i<=n;i++){
		int x;
		cin>>x;
		a.push_back(x);
	}
	vector<int> ans;
	ans=calc(0);
	cout<<ans.size()<<"\n";
	for(int i:ans)cout<<i<<" ";
}