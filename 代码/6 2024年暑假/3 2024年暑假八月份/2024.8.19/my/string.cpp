#include <bits/stdc++.h>
using namespace std;
const int N=1e7+10;
bitset<N> s;
int main() {
	freopen("string.in","r",stdin);
	freopen("string.out","w",stdout);
	ios::sync_with_stdio(false);
	cin.tie(nullptr),cout.tie(nullptr);
	int n;
	cin>>n>>s;
	vector<pair<string,int>>v;
	for(int i=1;i<(1<<n);i++) {
		string tmp;
		for(int j=n-1;j>=0;j--)tmp+=(i>>j)&1?'1':'0';
		while(!tmp.empty()&&tmp.back()=='0')tmp.pop_back();
		reverse(tmp.begin(), tmp.end());
		v.push_back({tmp,i});
	}
	sort(v.begin(), v.end());
	cout<<v[s.to_ullong()-1].first;
}