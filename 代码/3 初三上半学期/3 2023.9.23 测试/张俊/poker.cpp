#include<bits/stdc++.h>
using namespace std;
const int N=1e6+10;
struct node{
	int x,y;
}a[N];
int cnt1[N],cnt2[N];
bool cmp(const node&x,const node&y){return x.x<y.y;}
int main(){
	freopen("poker.in","r",stdin);
	freopen("poker.out","w",stdout);
	int n,k;
	cin>>n>>k;
	bool flag=true;
	for(int i=1;i<=k;i++){
		cin>>a[i].x>>a[i].y;
		if(a[i].x!=a[i].y) flag=false;
	}
	
	if(flag){
		sort(a+1,a+k+1,cmp);
		for(int i=1;i<=k;i++) cnt1[a[i].x]++;
		for(int i=1;i<=n;i++) cnt2[i]=cnt2[i-1]+cnt1[i];
		for(int i=1;i<=n;i++) if(cnt1[i]) cnt1[i]--;
		for(int i=1;i<=n;i++) cnt1[i]=cnt1[i-1]+cnt1[i];
		
		int q;
		cin>>q;
		while(q--){
			int l,r;
			cin>>l>>r;
			int sum=cnt2[r]-cnt2[l-1];
			int num=cnt1[r]-cnt1[l-1];
			if(sum-num==r-l+1)puts("Yes");
			else puts("No");
		}
	}
	
}
