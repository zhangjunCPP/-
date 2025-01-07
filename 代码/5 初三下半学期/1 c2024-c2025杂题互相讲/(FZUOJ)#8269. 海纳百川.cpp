#include <bits/stdc++.h>
using namespace std;
const int N=1e5+10;
int n,a[N];
int st[N][25];
int lg[N];
int gcd(int x,int y){
	while(y^=x^=y^=x%=y);
	return x;
}
void init(){
	for(int i=1;i<=n;i++)st[i][0]=a[i];
	for(int i=2;i<=n;i++)lg[i]=lg[i>>1]+1;
	for(int j=1;j<=20;j++){
		for(int i=1;i+(1<<j)-1<=n;i++){
			st[i][j]=gcd(st[i][j-1],st[i+(1<<(j-1))][j-1]);
		}
	}
}
int ask(int l,int r){
	if(l>r)return 1;
	int tmp=lg[r-l+1];
	return gcd(st[l][tmp],st[r-(1<<tmp)+1][tmp]);
}
int solvel(int i,int x){
	if(i==1)return 1;
	if(x==1)return 0;
	int l=1,r=i-1,ans=0;
	while(l<=r){
		int mid=(l+r)>>1;
		if(gcd(ask(mid,i-1),x)==1)l=mid+1;
		else r=mid-1,ans=mid;
	}
	if(ans==0)return 1;
	return i-ans+1;
}
int solver(int i,int x){
	if(i==n)return 1;
	if(x==1)return 0;
	int l=i+1,r=n,ans=0;
	while(l<=r){
		int mid=(l+r)>>1;
		if(gcd(ask(i+1,mid),x)==1)r=mid-1;
		else l=mid+1,ans=mid;
	}
	if(ans==0)return 1;
	return ans-i+1;
}
int fl[N],fr[N];
vector<pair<int,int> > gl[N],gr[N];
unordered_map<int,int> mp[N];
bool cmp(const pair<int,int> &x,const pair<int,int> &y){
	if(x.second==y.second)return x.first>y.first;
	return x.second>y.second;
}
int sum1[N],sum2[N];
int main(){
	cin>>n;
	for(int i=1;i<=n;i++)cin>>a[i];
	init();
	for(int i=1;i<=n;i++){
		fl[i]=solvel(i,a[i]);
		fr[i]=solver(i,a[i]);
		gl[i].push_back({1,0});//只选右边
		gr[i].push_back({1,0});//只选左边
		int x=a[i];
		for(int j=2;j*j<=x;j++){
			if(x%j==0){
				gl[i].push_back({j, solvel(i,j)});
				gr[i].push_back({j, solver(i,j)});
				while(x%j==0)x/=j;
			}
		}
		if(x>1){
			gl[i].push_back({x, solvel(i,x)});
			gr[i].push_back({x, solver(i,x)});
		}
		for(auto j:gr[i])mp[i][j.first]=j.second;
		sort(gl[i].begin(), gl[i].end(),cmp);
		sort(gr[i].begin(), gr[i].end(),cmp);
	}
	for(int i=1;i<=n;i++)sum1[i]=sum1[i-1]+fl[i];
	for(int i=n;i>=1;i--)sum2[i]=sum2[i+1]+fr[i];
	int ans=-1;
	for(int i=1;i<=n;i++){
		int other=sum1[i-1]+sum2[i+1];
		if(i==1)ans=max(ans,other+1+gr[2][0].second);
		else if(i==n)ans=max(ans,other+1+gl[n-1][0].second);
		else{
			for(auto x:gl[i-1]){
				for(auto y:gr[i+1]){
					if(x.first*y.first<=50000){
						ans=max(ans,other+x.second*mp[i+1][x.first]+x.second+y.second+1);
					}
				}
			}
		}
	}
	cout<<ans;
}