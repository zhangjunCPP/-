#include<bits/stdc++.h>
using namespace std;
const int N=5e6+10;
vector<int> ans[N];
int cnt;
int qpow(int x,int y){
	int ans=1;
	while(y){
		if(y&1) ans=ans*x;
		x=x*x;
		y>>=1;
	}
	return ans;
}
void solve(int p,int k,int now){
	if(k==1){
		cnt++;
		for(int i=0;i<p;i++)ans[cnt].push_back(now+i);
		return;
	}
	int tmp=qpow(p,k-1);
	for(int i=0;i<tmp;i++){
		for(int d=tmp;d<2*tmp;d++) {
			++cnt;
			for(int x=0;x<p;x++)ans[cnt].push_back((i+d*x)%tmp+x*tmp+now);
		}
	}
	for(int i=0;i<p;i++) solve(p,k-1,now+i*tmp);
}
int main(){
	int p,k;
	cin>>p>>k;
	solve(p,k,0);	 
	cout<<cnt<<"\n";
	for(int i=1;i<=cnt;i++) {
		for(int j:ans[i]) cout<<j<<" ";
		cout<<"\n";
	}
	return 0;
}
