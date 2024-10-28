#include<bits/stdc++.h>
#define int long long
using namespace std;
int l[150005],r[150005];
int n,q,v;
int t[205][205][3];
const int mod=998244853;
int ans=0,tot=1;
int inv[205];
void add(int x)
{
	int l= ::l[x],r= ::r[x];
	tot=tot*(r-l)%mod;
	for(int i=1;i<=v;i++)
	{
		if(i<=l)
		{
			(ans+=inv[r-l]*(t[i][r-1][2]-t[i][l-1][2]+mod)%mod-l*inv[r-l]%mod*(t[i][r-1][1]-t[i][l-1][1]+mod)%mod+mod)%=mod;
			(ans+=t[i][v][1]-t[i][r-1][1]+mod)%=mod;
		}
		else if(i<=r)
		{
			(ans+=(t[i][r-1][0]-t[i][l-1][0]+mod)*inv[r-l]%mod)%=mod;
			(ans+=inv[r-l]*r%mod*(t[i][v][1]-t[i][r-1][1]+mod)%mod-inv[r-l]*i%mod*(t[i][v][1]-t[i][r-1][1]+mod)%mod+mod)%=mod;
		}
	}
	for(int i=r;i<=v;i++)
	{
		t[l][i][0]++;
		(t[l][i][1]+=inv[r-l])%=mod;
		(t[l][i][2]+=inv[r-l]*r%mod)%=mod;
	}
}
void del(int x)
{
	int l= ::l[x],r= ::r[x];
	tot=tot*inv[r-l]%mod;
	for(int i=r;i<=v;i++)
	{
		t[l][i][0]--;
		(t[l][i][1]+=mod-inv[r-l])%=mod;
		(t[l][i][2]+=mod-inv[r-l]*r%mod)%=mod;
	}
	for(int i=1;i<=v;i++)
	{
		if(i<=l)
		{
			(ans+=mod-inv[r-l]*(t[i][r-1][2]-t[i][l-1][2]+mod)%mod+l*inv[r-l]%mod*(t[i][r-1][1]-t[i][l-1][1]+mod)%mod)%=mod;
			(ans+=mod-t[i][v][1]+t[i][r-1][1])%=mod;
		}
		else if(i<=r)
		{
			(ans+=mod-(t[i][r-1][0]-t[i][l-1][0]+mod)*inv[r-l]%mod)%=mod;
			(ans+=mod-inv[r-l]*r%mod*(t[i][v][1]-t[i][r-1][1]+mod)%mod+inv[r-l]*i%mod*(t[i][v][1]-t[i][r-1][1]+mod)%mod)%=mod;
		}
	}
}
signed main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin>>n>>q>>v;
	v++;
	inv[1]=1;
	for(int i=2;i<=v;i++)
		inv[i]=(-inv[mod%i]*(mod/i)%mod+mod)%mod;
	for(int i=1;i<=n;i++)
		cin>>l[i];
	for(int i=1;i<=n;i++)
		cin>>r[i],r[i]++;
	for(int i=1;i<=n;i++)
		add(i);
	int tans=(n*(n+1)/2-ans+mod)%mod;
	cout<<tans*tot%mod<<"\n";
	for(int i=1;i<=q;i++)
	{
		int x,y,k;
		cin>>x>>y>>k;
		del(y);
		if(x==1)
			l[y]=k;
		else
			r[y]=k+1;
		add(y);
		int tans=(n*(n+1)/2-ans+mod)%mod;
		cout<<tans*tot%mod<<"\n";
	}
}