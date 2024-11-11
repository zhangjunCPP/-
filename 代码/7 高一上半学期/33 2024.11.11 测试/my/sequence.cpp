#include<bits/stdc++.h>
using namespace std;
const int N=5e5+10;
int a[N],tmp[N];
int sum[N];
int last[N];
int main(){
	int n,k;
	cin>>n>>k;
	for(int i=1;i<=n;i++)cin>>a[i],tmp[i]=a[i];
	int tot=n;
	sort(tmp+1,tmp+tot+1);
	tot=unique(tmp+1,tmp+tot+1)-tmp-1;
	for(int i=1;i<=n;i++)a[i]=lower_bound(tmp+1,tmp+tot+1,a[i])-tmp;
	long long ans=0;
	if(n<=5000){
		for(int i=1;i<=n;i++){
			for(int j=1;j<=n;j++)sum[j]=0;
			int flag=0;
			for(int j=i;j<=n;j++){
				sum[a[j]]++;
				if(sum[a[j]]>k)break;
				if(sum[a[j]]==1)flag++;
				if(sum[a[j]]==k)flag--;
				if(!flag)ans++;
			}
		}
		cout<<ans;
		return 0;
	}
	if(k==1){
		int l=1;
		for(int i=1;i<=n;i++){
			l=max(l,last[a[i]]+1);
			ans+=(i-l+1);
			last[a[i]]=i;
		}
		cout<<ans;
		return 0;
	}
}