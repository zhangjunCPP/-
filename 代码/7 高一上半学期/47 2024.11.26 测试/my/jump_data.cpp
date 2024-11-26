#include<bits/stdc++.h>
using namespace std;
mt19937 myrand(random_device{}());
int random(int l,int r){
	return myrand()%(r-l+1)+l;
}
void solve(){
	int n=300;
	cout<<n<<"\n";
	for(int i=1;i<=n;i++)cout<<random(1,1000000000)<<" ";
	cout<<"\n";
	for(int i=1;i<=n;i++)cout<<random(1,100000)<<" ";
	cout<<"\n";
}
int main(){
	freopen("jump.in","w",stdout);
	int T;
	T=10;
	cout<<T<<"\n";
	while(T--)solve();
}