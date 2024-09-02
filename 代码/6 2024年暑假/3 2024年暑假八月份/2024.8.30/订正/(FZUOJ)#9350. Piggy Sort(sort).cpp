#include <bits/stdc++.h>
using namespace std;
const int N=500+10;
const double eps=1e-7;
int n,m;
double a[N][N];
double sum[N];
int id[N];
bool cmp(const int&x,const int&y){return sum[x]<sum[y];}
int pos[N];
pair<double,int> rk[N];
int ans[N];
void solve() {
	cin>>n>>m;
	for(int i=1;i<=m;i++)sum[i]=0;
	for(int i=1;i<=m;i++) {
		for(int j=1;j<=n;j++) {
			cin>>a[i][j];
			sum[i]+=a[i][j];
		}
	}
	for(int i=1;i<=m;i++)id[i]=i;
	sort(id+1,id+m+1,cmp);
	if(fabs(sum[id[m]]-sum[id[1]])<eps) {
		for(int i=1;i<=n;i++)cout<<i<<" ";
		cout<<"\n";
		return;
	}
	for(int i=1;i<=n;i++) {
		for(int j=1;j<=m;j++)pos[j]=1;
		for(int j=1;j<=n;j++) {
			double slope=(a[id[2]][j]-a[id[1]][i])/(sum[id[2]]-sum[id[1]]);
			if(slope<0)continue;
			bool flag=true;
			for(int k=3;k<=m;k++) {
				double tmp=a[id[1]][i]+slope*(sum[id[k]]-sum[id[1]]);
				while(pos[k]<n&&tmp-a[id[k]][pos[k]]>eps)pos[k]++;
				if(abs(a[id[k]][pos[k]]-tmp)>eps){flag=false;break;}
			}
			if(flag)rk[i]={slope,i};
		}
	}
	sort(rk+1,rk+n+1);
	for(int i=1;i<=n;i++)ans[rk[i].second]=i;
	for(int i=1;i<=n;i++)cout<<ans[i]<<" ";
	cout<<"\n";
}
int main() {
	ios::sync_with_stdio(false);cin.tie(nullptr),cout.tie(nullptr);
	int T;
	cin>>T;
	while(T--)solve();
}