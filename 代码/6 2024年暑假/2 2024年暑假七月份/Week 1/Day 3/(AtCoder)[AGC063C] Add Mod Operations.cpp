#include<bits/stdc++.h>
#define int long long
using namespace std;
const int INF=1e10;
const int N=1e5+10;
struct node{
	int a,b;
	bool operator==(const node&oth)const{
		return a==oth.a&&b==oth.b;
	}
}a[N];
bool cmp(const node&x,const node&y){return x.a<y.a;}
signed main(){
	int n;
	cin>>n;
	for(int i=1;i<=n;i++)cin>>a[i].a;
	for(int i=1;i<=n;i++)cin>>a[i].b;
	sort(a+1,a+n+1,cmp);
	n=unique(a+1,a+n+1)-a-1;
	for(int i=1;i<n;i++)if(a[i].a==a[i+1].a&&a[i].b!=a[i+1].b){cout<<"No";return 0;}
	cout<<"Yes\n"<<n<<"\n";
	if(n==1){
		if(a[1].a>a[1].b)cout<<INF-a[1].a<<" "<<INF-a[1].b;
		else cout<<a[1].b-a[1].a<<" "<<INF;
		return 0;
	}
	for(int i=2;i<=n;i++)a[i].b+=(i-2)*INF;
	a[1].b+=INF*n;
	for(int i=n;i>=2;i--){
		int x=a[i+1].b-a[i].b;
		if(i==n)x=INF-a[1].a+a[1].b-a[n].b;
		int y=a[i].a+x;
		cout<<x<<" "<<y<<"\n";
		for(int j=1;j<=n;j++)a[j].a=(a[j].a+x)%y;
	}
	cout<<a[2].b<<" "<<INF;
}