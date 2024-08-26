#include<bits/stdc++.h>
#define ll long long
using namespace std;
mt19937 rd(time(0));
const int N=122,M=3e6+7,mod=1e9+7;
const ll K=1e10;
int c,T,n,co[N][N];__int128 res[N];
void qm(int &x,int y){x+=y;if(x>=mod)x-=mod;}
int ksm(int a,ll b=mod-2){int s=1;
	for(;b;b>>=1,a=1ll*a*a%mod)if(b&1)s=1ll*s*a%mod; 
	return s;
}
struct Mat{
	int n,m,a[N][N];
	Mat(){memset(a,0,sizeof(a));}
	Mat operator * (Mat b){Mat c;c.n=n,c.m=m;
		for(int i=1;i<=n;i++)for(int j=1;j<=m;j++)for(int k=1;k<=m;k++)
			qm(c.a[i][k],1ll*a[i][j]*b.a[j][k]%mod);
		return c;
	}
	int det(){int res=1;
		memcpy(co,a,sizeof(co));
		for(int i=1;i<=n;i++){int p=i;
			for(int j=i;j<=n;j++)if(a[j][i]){p=j;break ;}
			if(i!=p)swap(a[i],a[p]),res=-res;
			int tmp=ksm(a[i][i]);
			for(int j=i+1;j<=n;j++){
				int x=1ll*a[j][i]*tmp%mod;
				for(int k=i;k<=n;k++)qm(a[j][k],mod-1ll*x*a[i][k]%mod);
			}
			res=1ll*res*a[i][i]%mod;
		}
		memcpy(a,co,sizeof(a));
		return (res%mod+mod)%mod;
	}
	void print(){
		for(int i=1;i<=n;i++){
			for(int j=1;j<=m;j++)printf("%d ",a[i][j]);
			printf("\n");
		}
	}
}bs[50],g;
struct BSGS{map<int,int> mp;
	int get(int a,int b){mp.clear();
		int B=sqrt(K)+1,s=1;
		for(int i=0;i<B;i++,s=1ll*s*a%mod)mp[1ll*s*b%mod]=i;
		for(int i=1,s1=s;i<=B;i++,s1=1ll*s1*s%mod)if(mp.count(s1))return i*B-mp[s1];
	}
}G;
bool check(Mat &a,Mat b,ll k){
	for(int i=0;i<=40;i++)if((k>>i)&1)b=b*bs[i];
	for(int i=1;i<=a.m;i++)if(a.a[1][i]!=b.a[1][i])return 0;
	return 1;
}
void solve(){
	scanf("%d",&n);
	memset(g.a,0,sizeof(g.a));
	Mat a,d;a.n=g.n=a.m=g.m=d.m=n,d.n=1;
	for(int i=1;i<=n;i++)for(int j=1;j<=n;j++)scanf("%d",&g.a[i][j]);
	for(int i=1;i<=n;i++)for(int j=1;j<=n;j++)scanf("%d",&a.a[i][j]);
	bool p=1;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++)p&=((i==j)==a.a[i][j]);
	}
	if(p)return printf("0\n"),void();
	for(int i=1;i<=n;i++)d.a[1][i]=((rd()<<13)^rd()%mod+mod)%mod;
	bs[0]=g;
	for(int i=1;i<=40;i++)bs[i]=bs[i-1]*bs[i-1];
	int x=G.get(g.det(),a.det());
	int y=G.get(g.det(),1);
	a=d*a;
	for(ll k=x;1;k+=y){
		if(check(a,d,k))return printf("%lld\n",k),void();
	} 
}
int main(){
freopen("easy.in", "r", stdin);
	freopen("easy.out", "w", stdout);
	scanf("%d%d",&c,&T);
	while(T--)solve();
	return 0;
}
