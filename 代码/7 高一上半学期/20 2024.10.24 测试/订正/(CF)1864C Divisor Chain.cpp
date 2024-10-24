#include<bits/stdc++.h>
using namespace std;
int pw[35];
void init(){
	pw[0]=1;
	for(int i=1;i<31;i++)pw[i]=pw[i-1]*2;
}
void solve(){
	int n;
	cin>>n;
	vector<int> ans;
	bool flag=false;
	int now=n;
	for(int i=30;i>=0;i--){
		if(n>=pw[i]){
			if(!flag){//第一次
				for(int j=0;j<i;j++)ans.push_back(pw[j]);
				n-=pw[i];
				flag=true;
			}
			else ans.push_back(pw[i]),n-=pw[i];
		}
	}
	reverse(ans.begin(),ans.end());
	cout<<ans.size()+1<<"\n";
	cout<<now<<" ";
	for(int it:ans)cout<<now-it<<" ",now-=it;
	cout<<"\n";
}
int main(){
	init();
	ios::sync_with_stdio(false);cin.tie(nullptr),cout.tie(nullptr);
	int T;
	cin>>T;
	while(T--)solve();
}