#include <bits/stdc++.h>
using namespace std;
const int N=250000+10;
int n,m,q;
struct node{
	int id;
	vector<int> s;
};
bool cmp(const node&x,const node&y){
	for(int i=1;i<=m;i++){
		if(x.s[i]==y.s[i])continue;
		return x.s[i]<y.s[i];
	}
	return x.id<y.id;
}

int main(){
	cin>>n>>m>>q;
	static node a[N];
	for(int i=1;i<=n;i++)a[i].id=i,a[i].s.resize(m+1);
	for(int i=1;i<=q;i++){
		int l,r,p,w;
		cin>>l>>r>>p>>w;
		for(int j=l;j<=r;j++)a[j].s[p]=w;
	}
	sort(a+1,a+n+1,cmp);
	for(int i=1;i<=n;i++)cout<<a[i].id<<"\n";
}