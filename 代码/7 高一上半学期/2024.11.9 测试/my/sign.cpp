#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=5e5+10;
int n,id;
int a[N];
int sta[N],top;
pair<int,int> val[N];
void solve(){
	top=0;
	int q;
	cin>>q;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		while(top>1&&(__int128)(a[i]-a[sta[top]])*(sta[top]-sta[top-1])>(__int128)(a[sta[top]]-a[sta[top-1]])*(i-sta[top]))top--;
		sta[++top]=i;
		val[i]={a[sta[top-1]]-a[i],(i-sta[top-1])};
	}
	int sum=0;
	int lastpos=1;
	int last=0;
	while(q--){
		int k;
		cin>>k;
		if(id)k=(k^(last%(k+1)));
		sum+=k;
		while(lastpos<top&&val[sta[lastpos+1]].first<sum*val[sta[lastpos+1]].second)lastpos++;
		last=a[sta[lastpos]]+sta[lastpos]*sum;
		cout<<last<<"\n";
	}
}
signed main(){
	freopen("sign.in","r",stdin);
	freopen("sign.out","w",stdout);
	ios::sync_with_stdio(false);cin.tie(nullptr),cout.tie(nullptr);
	int T;
	cin>>T>>n>>id;
	while(T--)solve();
}