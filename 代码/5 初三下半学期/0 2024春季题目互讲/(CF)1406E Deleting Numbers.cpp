#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e5+10;
int calc1(int x){
	cout<<"A "<<x<<endl;
	int tmp;
	cin>>tmp;
	return tmp;
}
int calc2(int x){
	cout<<"B "<<x<<endl;
	int tmp;
	cin>>tmp;
	return tmp;
}

int prime[N],cnt;
bool vis[N];
void init(int n){
	for(int i=2;i<=n;i++){
		if(!vis[i])prime[++cnt]=i;
		for(int j=1;j<=cnt&&i*prime[j]<=n;j++){
			vis[i*prime[j]]=true;
			if(i%prime[j]==0)break;
		}
	}
}
signed main(){
	int n;
	cin>>n;
	init(n);
	int block=sqrt(n);
	int ans=1;
	int nex=cnt+1;
	for(int i=1;i<=cnt;i++){
		if(prime[i]>block){nex=i;break;}
		if(!calc2(prime[i]))continue;
		int last=0;
		for(int j=prime[i];j<=n;j*=prime[i]){
			if(!calc1(j)){ans=ans*j/prime[i];last=1;break;}
			else last=j;
		}
		ans*=last;
	}
	if(ans!=1){
		for(int i=nex;i<=cnt;i++){
			if(prime[i]*ans>n)break;
			if(calc1(prime[i]*ans)){cout<<"C "<<ans*prime[i]<<endl;return 0;}
		}
		cout<<"C "<<ans<<endl;return 0;
	}
	for(int i=nex;i<=cnt;i+=90){
		int j=min(i+90-1,cnt);
		for(int k=i;k<=j;k++)calc2(prime[k]);
		if(calc1(1)>cnt-j+1){
			for(int k=i;k<=j;k++){
				if(calc1(prime[k])){cout<<"C "<<prime[k]<<endl;return 0;}
			}
		}
	}
	cout<<"C "<<ans<<endl;
	return 0;
}