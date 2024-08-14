#include <bits/stdc++.h>
using namespace std;
const int N=5e5+10;
int a[N];
void solve() {
	int n;
	cin>>n;
	for(int i=1;i<=n;i++)cin>>a[i];
	bool flag=true;
	for(int i=1;i<=n;i++)if(a[i]!=i){flag=false;break;}
	if(flag){puts("0");return;}//0次
	int Max=-1;
	for(int i=1;i<=n;i++) {//1次
		if(a[i]==i&&Max<a[i]){puts("1");return;}
		Max=max(Max,a[i]);
	}
	if(a[1]==n&&a[n]==1)puts("3");//3次
	else puts("2");
}
int main() {
	freopen("p.in","r",stdin);
	freopen("p.out","w",stdout);
	int T;
	cin>>T;
	while(T--)solve();
}