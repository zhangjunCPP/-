#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e5+10,mod=998244353;
struct matrix{
	int a[3][3];
	matrix(){memset(a,0,sizeof a);}
	matrix(int a00,int a01,int a02,int a10,int a11,int a12,int a20,int a21,int a22){
		a[0][0]=a00;a[0][1]=a01;a[0][2]=a02;
		a[1][0]=a10;a[1][1]=a11;a[1][2]=a12;
		a[2][0]=a20;a[2][1]=a21;a[2][2]=a22;
	}
	matrix operator*(const matrix&oth)const{
		matrix ans(0,0,0,0,0,0,0,0,0);
		for(int i=0;i<3;i++)
			for(int j=0;j<3;j++)
				for(int k=0;k<3;k++)ans.a[i][j]=(ans.a[i][j]+a[i][k]*oth.a[k][j]%mod)%mod;
		return ans;
	}
}tree[N<<2];
int a[N];
#define ls (k<<1)
#define rs (k<<1|1)
matrix Map[3]={
	matrix(1,0,0,1,1,0,1,0,1),//0
	matrix(1,1,0,0,1,0,0,1,1),//1
	matrix(1,1,0,1,1,0,1,1,1)//?
};
const matrix P(0,0,1,0,0,0,0,0,0);
void build(int k,int l,int r){
	if(l==r){
		tree[k]=Map[a[l]];
		return;
	}
	int mid=(l+r)>>1;
	build(ls,l,mid),build(rs,mid+1,r);
	tree[k]=tree[ls]*tree[rs];
}
void modify(int k,int l,int r,int x,int val){
	if(l==r){
		tree[k]=Map[val];
		return;
	}
	int mid=(l+r)>>1;
	if(x<=mid)modify(ls,l,mid,x,val);
	else modify(rs,mid+1,r,x,val);
	tree[k]=tree[ls]*tree[rs];
}
signed main(){
	ios::sync_with_stdio(false);cin.tie(nullptr),cout.tie(nullptr);
	int n,q;
	string s;
	cin>>n>>q>>s;
	for(int i=1;i<=n;i++){
		if(s[i-1]=='?')a[i]=2;
		else a[i]=s[i-1]-'0';
	}
	build(1,1,n);
	while(q--){
		int x;string val;
		cin>>x>>val;
		modify(1,1,n,x,(val=="?"?2:val[0]-'0'));
		matrix ans=P*tree[1];
		cout<<(ans.a[0][0]+ans.a[0][1])%mod<<"\n";
	}
}