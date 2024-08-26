#include<bits/stdc++.h>
#define int long long
using namespace std;
const int mod=1e9+7;
struct matrix{
	int mat[125][125];
	int n,m;
	matrix operator*(const matrix&oth) const{
		matrix ans;
		ans.n=n,ans.m=oth.m;
		for(int i=1;i<=ans.n;i++)for(int j=1;j<=ans.m;j++)ans.mat[i][j]=0;
		for(int i=1;i<=n;i++)
			for(int j=1;j<=oth.m;j++)
				for(int k=1;k<=m;k++)
					ans.mat[i][j]=(ans.mat[i][j]+mat[i][k]*oth.mat[k][j]%mod)%mod;
		return ans;
	}
	bool operator==(const matrix&oth) const {
		if(n!=oth.n||m!=oth.m)return false;
		for(int i=1;i<=n;i++)for(int j=1;j<=m;j++)if(mat[i][j]!=oth.mat[i][j])return false;
		return true;
	}
	bool operator<(const matrix&oth)const {
		for(int i=1;i<=n;i++) {
			for(int j=1;j<=m;j++) {
				if(mat[i][j]<oth.mat[i][j])return false;
				if(mat[i][j]>oth.mat[i][j])return true;
			}
		}
		return false;
	}
};
matrix qpow(matrix x,int y,int n) {
	matrix ans;
	ans.n=ans.m=n;
	for(int i=1;i<=ans.n;i++)for(int j=1;j<=ans.m;j++)ans.mat[i][j]=0;
	for(int i=1;i<=n;i++)ans.mat[i][i]=1;
	while(y) {
		if(y&1)ans=ans*x;
		y>>=1;
		x=x*x;
	}
	return ans;
}
int lim[21]={10,5,5,1000,1000,32,32,320,320,320,3170,3170,3170,3170,3170,100000,100000,100000,100000,100000,100000};
int bsgs(matrix a,matrix b,int n,int id){  //a^x≡b
	map<matrix,int> mp;
	int m=lim[id];
	matrix k=b;
	mp[k]=0;
	for(int i=1;i<=m;i++){
		k=k*a;
		mp[k]=i;
	}
	k=qpow(a,m,n);
	matrix now;
	now.n=now.m=n;
	for(int i=1;i<=n;i++)for(int j=1;j<=n;j++)now.mat[i][j]=0;
	for(int i=1;i<=n;i++)now.mat[i][i]=1;
	for(int i=1;i<=m;i++){
		now=now*k;
		if(mp.count(now)){
			int ans=i*m-mp[now];
			return (ans%mod+mod)%mod;
		}
	}
	return -1;
}
matrix c,a;
void solve(int id) {
	int n;
	cin>>n;
	c.n=c.m=n;
	a.n=a.m=n;
	for(int i=1;i<=n;i++)for(int j=1;j<=n;j++)cin>>c.mat[i][j];
	for(int i=1;i<=n;i++)for(int j=1;j<=n;j++)cin>>a.mat[i][j];
	cout<<bsgs(c,a,n,id)<<"\n";
}
signed main() {
	ios::sync_with_stdio(false);cin.tie(nullptr),cout.tie(nullptr);
	freopen("easy.in","r",stdin);
	freopen("easy.out","w",stdout);
	int o;
	int T;
	cin>>o>>T;
	while(T--)solve(o);
}