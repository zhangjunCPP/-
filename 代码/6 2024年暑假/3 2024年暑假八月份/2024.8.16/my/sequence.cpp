#include<bits/stdc++.h>
using namespace std;
const int N=5e5+10;
int a[N];
int main() {
	freopen("sequence.in","r",stdin);
	freopen("sequence.out","w",stdout);
	int n,k;
	cin>>n>>k;
	bool flag=true;
	for(int i=1;i<=k;i++)cin>>a[i],flag&=(a[i]==i);
	if(flag) {
		for(int i=1;i<=n;i++) {
			if(i<=k)puts("1");
			else puts("0");
		}
		return 0;
	}
	if(k==1) {
		for(int i=1;i<=n;i++) {
			if(i<=a[1])puts("1");
			else puts("0");
		}
		return 0;
	}
	for(int i=1;i<=n;i++)puts("1");
	return 0;
}