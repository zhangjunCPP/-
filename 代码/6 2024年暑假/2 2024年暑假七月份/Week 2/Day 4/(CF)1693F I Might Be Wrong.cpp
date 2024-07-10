#include <bits/stdc++.h>
using namespace std;
const int N=2e5+10;
int last[N];
void solve() {
	int n;
	string s;
	cin>>n>>s;
	if(s.find('0')==-1||s.find('1')==-1||s.find_last_of('0')==s.find_first_of('1')-1){puts("0");return;}
	int cnt0=0,cnt1=0;
	for(int i=0;i<n;i++)if(s[i]=='0')cnt0++;else cnt1++;
	if(cnt1>cnt0) {
		reverse(s.begin(), s.end());
		for(int i=0;i<n;i++)s[i]=(s[i]=='0'?'1':'0');
		swap(cnt0,cnt1);
	}
	memset(last,0,sizeof last);
	int sum=0;
	for(int i=0;i<n;i++) {
		sum+=s[i]=='0'?1:-1;
		if(sum>=0)last[sum]=i;
	}
	int d=cnt0-cnt1;
	int now=0;
	while(now<n&&s[now]=='0')now++;
	int ans=0;
	while(now<d) {
		ans++;
		now+=(last[now]+1-now)/2;
	}
	cout<<ans+1<<"\n";
}
int main() {
	int T;
	cin>>T;
	while(T--)solve();
}