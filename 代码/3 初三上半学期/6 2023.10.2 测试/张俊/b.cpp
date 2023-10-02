#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=5e6+10;
int a[N];
int s[N];
signed main(){
	freopen("b.in","r",stdin);
	freopen("b.out","w",stdout);
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int n;
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i];
	sort(a+1,a+n+1);
	for(int i=1;i<=n;i++) s[i]=s[i-1]+a[i];
	int ans=0;
	for(int i=1;i<=n;i++){
		int tmp=0;
		int lastid=0;
		double lastval=0;
		for(int j=i;j<=n;j++){
			int now=tmp+1;
			int sum=s[j]-s[i-1];
			int num=j-i+1;
			double val=sum*1.0/num;
			if(j==i){
				tmp=0,lastid=i+1,lastval=val;
				continue;
			}
			if(val>lastval) {
				for(int k=lastid;k<=j;k++){
					if(a[k]<=val) now--;
					else {
						lastid=k;
						break;
					}
				}
			}
			else if(val==lastval) {
				now--;
				lastid=j+1;
			}
			else if(val<lastval){
				for(int k=lastid-1;k>=i;k--){
					if(a[k]>val)now++;
					else{
						lastid=k+1;
						break;
					}
				}
			}
			ans=max(ans,now);
			tmp=now;
			lastval=val;
		}
	}
	cout<<ans;
}
