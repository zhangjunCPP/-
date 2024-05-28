#include <bits/stdc++.h>
using namespace std;
const int N=4e7+10;
int read(){
	int x=0;
	char ch=getchar();
	while(ch<'0'||ch>'9')ch=getchar();
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch^48);ch=getchar();}
	return x;
}
int n;
int fa[N];
int deg[N];
int p[N];
void solve1(){
	for(int i=1;i<n;i++)fa[i]=read(),deg[fa[i]]++;
	for(int i=1,j=1;i<=n-2;i++,j++){
		while(deg[j])j++;
		p[i]=fa[j];
		while(i<=n-2&&!(--deg[p[i]])&&p[i]<j)p[i+1]=fa[p[i]],i++;
	}
	long long ans=0;
	for(int i=1;i<=n-2;i++)ans^=1ll*i*p[i];
	cout<<ans;
}
void solve2(){
	for(int i=1;i<=n-2;i++)p[i]=read(),++deg[p[i]];
	p[n-1]=n;
	for(int i=1,j=1;i<n;i++,j++){
		while(deg[j])j++;
		fa[j]=p[i];
		while(i<n&&!(--deg[p[i]])&&p[i]<j)fa[p[i]]=p[i+1],i++;
	}
	long long ans=0;
	for(int i=1;i<n;i++)ans^=1ll*i*fa[i];
	cout<<ans;
}
signed main(){
	n=read();
	int opt;
	opt=read();
	if(opt==1)solve1();
	else if(opt==2) solve2();
}