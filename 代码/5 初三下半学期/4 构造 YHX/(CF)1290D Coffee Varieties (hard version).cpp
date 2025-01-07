#include <bits/stdc++.h>

using namespace std;
const int N=1e5+10;
int block;
bool ans[N];
bool ask(int x){
	cout<<"? "<<x<<endl;
	char ch;
	cin>>ch;
	return ch=='N';
}
void solve(int id){
	int st=(id-1)*block+1;
	int ed=id*block;
	for(int i=st;i<=ed;i++)ans[i]&=ask(i);
}
int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr),cout.tie(nullptr);
	int n,k;
	cin>>n>>k;
	block=(k+1)/2;
	int tot=n/block;
	memset(ans,true,sizeof ans);
	if(tot==1)solve(1);
	for(int d=1;d<tot;d++){
		for(int i=1;i<=d&&i+d<=tot;i++){
			cout<<"R"<<endl;
			for(int j=i;j<=tot;j+=d)solve(j);
		}
	}
	int sum=0;
	for(int i=1;i<=n;i++)sum+=ans[i];
	cout<<"! "<<sum<<endl;
	return 0;
}