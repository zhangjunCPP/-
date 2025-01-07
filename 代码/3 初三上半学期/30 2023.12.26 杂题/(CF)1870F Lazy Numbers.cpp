#include<bits/stdc++.h>
#define i128 __int128
using namespace std;
const int N=1e5+10;
i128 n,k;
i128 read(){
	i128 x=0;
	char ch=getchar();
	while(ch<'0'||ch>'9')ch=getchar();
	while(ch>='0'&&ch<='9')x=x*10+ch-'0',ch=getchar();
	return x;
}
void write(i128 x){
	if(x<0)putchar('-'),x=-x;
	if(x>9)write(x/10);
	putchar(x%10+'0');
}
i128 l[N],r[N];
int dep;
void init(){
	dep=0;
	for(i128 i=1;i<=n;i*=k){
		dep++;
		l[dep]=i;
		r[dep]=min(n,i*k-1);
	}
}
i128 a[N];//分解
i128 dfn(i128 x){
	int len=0;
	while(x){
		a[++len]=x%k;
		x/=k;
	}
	for(int i=1;i<=len/2;i++)swap(a[i],a[len-i+1]);
	i128 sum=0,now=0;
	for(int i=1;i<=len;i++){
		now=now*k+a[i];
		sum+=min(now,r[i])-l[i]+1;
	}
	for(int i=len+1;i<=dep;i++){
		now=now*k;
		sum+=min(now-1,r[i])-l[i]+1;
	}
	return sum;
}
void solve(){
	n=read();k=read();
	init();
	i128 ans=0;
	for(int i=1;i<=dep;i++){
		i128 L=l[i],R=r[i];
		i128 ans1=0,ans2=0;
		while(L<=R){
			i128 mid=(L+R)>>1;
			i128 tmp=dfn(mid)-mid;
			if(tmp==0) ans1=mid;
			if(tmp<0) L=mid+1;
			else R=mid-1;
		}
		if(ans1==0)continue;
		L=l[i],R=r[i];
		while(L<=R){
			i128 mid=(L+R)>>1;
			i128 tmp=dfn(mid)-mid;
			if(tmp==0) ans2=mid;
			if(tmp>0) R=mid-1;
			else L=mid+1;
		}
		if(ans1==0)continue;
		ans+=ans2-ans1+1;
	}
	write(ans);
	putchar('\n');
}
int main(){
	int T;
	cin>>T;
	while(T--)solve();
}