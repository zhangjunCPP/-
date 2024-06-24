#include<bits/stdc++.h>
using namespace std;
const int N=1e5+10;
int a[N];
int p[N];
int main(){
	int n,q;
	cin>>n>>q;
	for(int i=0;i<n;i++)cin>>a[i];
	while(q--){
		int l,r;
		cin>>l>>r;
		int ans=0;
		for(int i=0;i<n;i++)p[i]=i;
		do{
			bool flag=true;
			for(int i=l;i<r;i++)if(a[i]==p[i]){flag=false;break;}
			ans+=flag;
		}while(next_permutation(p,p+n));
		cout<<ans<<"\n";
	}
}