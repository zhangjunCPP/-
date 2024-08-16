#include<bits/stdc++.h>
using namespace std;

int n,m;
int f[5005][205][8], g[205];
int mx[5005], lg[205];
int a[5005], b[5005];

int dis(int x,int y) {
	return min(abs(x-y),n-abs(x-y));
}

void modify(int p,int l,int r,int v) {
	int k=lg[r-l+1];
	f[p][l][k]=max(f[p][l][k],v);
	f[p][r-(1<<k)+1][k]=max(f[p][r-(1<<k)+1][k],v);
	return ;
}

int query(int p,int l,int r) {
	int k=lg[r-l+1];
	return max(f[p][l][k],f[p][r-(1<<k)+1][k]);
}

vector<pair<int,int> > vec[205];

int main() {
	freopen("cisum.in","r",stdin);
	freopen("cisum.out","w",stdout);
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	cin>>n>>m;
	lg[1]=0;
	for(int i=2;i<=n;i++) lg[i]=lg[i>>1]+1;
	memset(f,-0x3f,sizeof(f));
	for(int k=0;k<=lg[n];k++) f[0][0][k]=0;
	vec[0].push_back({0,0});
	for(int i=1;i<=m;i++) {
		cin>>a[i]>>b[i];
		memset(g,-0x3f,sizeof(g));
		for(int j=i-1;j>=0;j--) {
			if(a[i]-a[j]>n/2) {
				for(int k=0;k<n;k++) g[k]=max(g[k],mx[j]+1);
				break;
			}
			int t=a[i]-a[j], v=0;
			if(b[i]+t>=n) {
				int l=b[i]-t;
				int r=b[i]+t-n;
				v=max(query(j,l,n-1),query(j,0,r))+1;
				
			}else if(b[i]-t<0) {
				int l=b[i]+t;
				int r=b[i]-t+n;
				v=max(query(j,0,l),query(j,r,n-1))+1;
			}else {
				int l=b[i]-t;
				int r=b[i]+t;
				v=query(j,l,r)+1;
			}
			if(b[j]+t>=n) {
				int l=b[j]-t;
				int r=b[j]+t-n;
				modify(i,l,n-1,v);
				modify(i,0,r,v);
			}else if(b[j]-t<0) {
				int l=b[j]+t;
				int r=b[j]-t+n;
				modify(i,0,l,v);
				modify(i,r,n-1,v);
			}else {
				int l=b[j]-t;
				int r=b[j]+t;
				modify(i,l,r,v);
			}
		}
		for(int d=0;d<n;d++) {
			int ds=dis(b[i],d);
			int tx=a[i]-ds;
			pair<int,int> pr={tx,i};
			auto it=upper_bound(vec[d].begin(),vec[d].end(),pr);
			if(it==vec[d].begin()) continue;
			--it;
			int j=(*it).second, t=a[i]-a[j];
			if(t>n/2) continue;
			for(int p=0;p<n;p++) {
				if(p+t>=n) {
					int l=p-t;
					int r=p+t-n;
					g[p]=max(g[p],max(query(j,l,n-1),query(j,0,r))+1);
				}else if(p-t<0) {
					int l=p+t;
					int r=p-t+n;
					g[p]=max(g[p],max(query(j,0,l),query(j,r,n-1))+1);
				}else {
					int l=p-t;
					int r=p+t;
					g[p]=max(g[p],query(j,l,r)+1);
				}
			}
		}
		for(int k=lg[n];k>0;k--) {
			for(int j=0;j+(1<<k)-1<n;j++) {
				f[i][j][k-1]=max(f[i][j][k-1],f[i][j][k]);
				f[i][j+(1<<k-1)][k-1]=max(f[i][j+(1<<k-1)][k-1],f[i][j][k]);
			}
		}
		mx[i]=mx[i-1];
		for(int j=0;j<n;j++) {
			g[j]=max(g[j],f[i][j][0]);
			mx[i]=max(mx[i],g[j]);
			f[i][j][0]=g[j];
		}
		for(int k=1;(1<<k)<=n;k++) {
			for(int j=0;j+(1<<k)-1<n;j++) {
				f[i][j][k]=max(f[i][j][k-1],f[i][j+(1<<k-1)][k-1]);
			}
		}
		vec[b[i]].push_back({a[i],i});
	}
	cout<<mx[m]<<'\n';
	return 0;
}