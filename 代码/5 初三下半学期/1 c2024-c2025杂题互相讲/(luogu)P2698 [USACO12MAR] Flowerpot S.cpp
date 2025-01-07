#include <bits/stdc++.h>

using namespace std;
const int N=1e5+10;
struct node{
	int x,y;
}a[N];
bool cmp(const node&x,const node&y){return x.y<y.y;}
multiset<int> s;
int main(){
	int n,d;
	cin>>n>>d;
	for(int i=1;i<=n;i++)cin>>a[i].x>>a[i].y,s.insert(a[i].x);
	sort(a+1,a+n+1,cmp);
	int ans=0x3f3f3f3f;
	int tmp=1;
	for(int i=1;i<=n;i++){
		while(tmp<=n&&a[tmp].y<a[i].y+d){
			s.erase(s.find(a[tmp].x));
			tmp++;
		}
		auto it=s.lower_bound(a[i].x);
		if(it!=s.end())ans=min(ans,*it-a[i].x);
		it=s.upper_bound(a[i].x-1);
		if(it!=s.begin())ans=min(ans,a[i].x-*(--it));
	}
	if(ans==0x3f3f3f3f)ans=-1;
	cout<<ans;
}