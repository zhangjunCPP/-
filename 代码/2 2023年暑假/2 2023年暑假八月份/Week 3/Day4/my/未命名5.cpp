#include<bits/stdc++.h>
using namespace std;
const int N=1e5+10;
struct node{
	int id,val;
}a[N];
bool cmp(const node& x,const node& y){
	if(x.val==y.val) return x.id<y.id; 
	return x.val>y.val;
}
int q[N],cnt;
int main(){
	int n;
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i].val;
		a[i].id=i;
	}
	sort(a+1,a+n+1,cmp);
	int ans=0;
	int last=n;
	int sum=0;
	for(int i=1;i<=n;i++){
		if(a[i].id<last){
			q[++cnt]=a[i].id; 
			ans+=(last-a[i].id)*a[i].val;
			last=a[i].id;
		}
	}
	cout<<ans<<"\n";
	


	return 0;
}

