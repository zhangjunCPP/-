#include <bits/stdc++.h>
using namespace std;
const int N=40+10,mod=2000019;
int a[N];
vector<int> v1,v2;
void calc(vector<int>&v,int now){
	vector<int> tmp[15];
	for(int it:v)tmp[(it/now)%10].push_back(it);
	v.clear();
	for(int i=0;i<10;i++)for(int it:tmp[i])v.push_back(it);
}
int main(){
	int n;
	cin>>n;
	for(int i=1;i<=n;i++)cin>>a[i];
	int tmp=n/2;
	for(int i=0;i<(1<<tmp);i++){
		int sum=0;
		for(int j=0;j<tmp;j++)if(i&(1<<j))sum+=a[j+1];
		v1.push_back(sum);
	}
	for(int i=0;i<(1<<(n-tmp));i++){
		int sum=0;
		for(int j=0;j<(n-tmp);j++)if(i&(1<<j))sum+=a[tmp+j+1];
		v2.push_back(sum);
	}
	int ans=0;
	long long now=1;
	for(int p=0;p<10;p++){
		calc(v1,now);
		calc(v2,now);
		now*=10;
		int l1=v2.size()-1,l2=l1,r1=l1,r2=l1;
		for(int it:v1){
			while(l1>=0&&it%now+v2[l1]%now>=now*4/10)l1--;
			while(r1>=0&&it%now+v2[r1]%now>=now*5/10)r1--;
			while(l2>=0&&it%now+v2[l2]%now>=now*14/10)l2--;
			while(r2>=0&&it%now+v2[r2]%now>=now*15/10)r2--;
			ans=(ans+r1-l1+r2-l2)%mod;
		}
	}
	cout<<ans<<"\n";
}