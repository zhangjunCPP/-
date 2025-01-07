#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e6+10;
char s[N];
int n;

int sa[N];
int c[N];
int x[N],y[N];
void get_sa(){
	int m=122;

	for(int i=1;i<=n;i++) {x[i]=s[i];c[x[i]]++;}
	for(int i=1;i<=m;i++) c[i]+=c[i-1];
	for(int i=n;i>=1;i--) sa[c[x[i]]--]=i;

	for(int k=1;k<=n;k*=2){
		int num=0;
		for(int i=n-k+1;i<=n;i++) y[++num]=i;
		for(int i=1;i<=n;i++) if(sa[i]>k) y[++num]=sa[i]-k;
		for(int i=1;i<=m;i++) c[i]=0;
		for(int i=1;i<=n;i++) c[x[i]]++;
		for(int i=1;i<=m;i++) c[i]+=c[i-1];
		for(int i=n;i>=1;i--) {sa[c[x[y[i]]]--] = y[i];y[i] = 0;}
		swap(x,y);
		num=1;
		x[sa[1]]=1;
		for(int i=2;i<=n;i++){
			if(y[sa[i]]==y[sa[i-1]]&&y[sa[i]+k]==y[sa[i-1]+k]) x[sa[i]]=num;
			else x[sa[i]]=++num;
		}
		if(num==n) break;
		m=num;
	}
}
int rk[N];
int height[N];
void get_height(){
	for(int i=1;i<=n;i++) rk[sa[i]]=i;// sa[rk[i]]=rk[sa[i]]=i
	int k=0;
	for(int i=1;i<=n;i++){
		if(rk[i]==1) continue;
		if(k) k--;
		int tmp1=sa[rk[i]];  //tmp1=i;
		int tmp2=sa[rk[i]-1];
		while(tmp1+k<=n&&tmp2+k<=n&&s[tmp1+k]==s[tmp2+k])k++;
		height[rk[i]]=k;
	}
}
signed main() {
	cin>>n>>(s+1);
	get_sa();
	get_height();
	int ans=n*(n+1)/2;
	for(int i=2;i<=n;i++) ans-=height[i];
	cout<<ans;
}