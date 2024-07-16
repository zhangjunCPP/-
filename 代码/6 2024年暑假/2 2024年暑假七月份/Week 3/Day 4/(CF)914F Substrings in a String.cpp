#include <bits/stdc++.h>
using namespace std;
const int N=1e5+10;
bitset<N> a[30],ans;
int main() {
	string s;
	int q;
	cin>>s>>q;
	for(int i=0;i<s.size();i++)a[s[i]-'a'][i]=true;
	while(q--) {
		int opt;
		cin>>opt;
		if(opt==1) {
			int x;char c;
			cin>>x>>c;
			x--;
			a[s[x]-'a'][x]=false;
			s[x]=c;
			a[s[x]-'a'][x]=true;
		}
		else {
			int l,r;
			string t;
			cin>>l>>r>>t;
			l--,r--;
			int n=t.size();
			if(r-l+1<n){puts("0");continue;}
			ans.set();
			for(int i=0;i<n;i++)ans&=a[t[i]-'a']>>i;
			cout<<(ans>>l).count()-(ans>>(r-n+2)).count()<<"\n";
		}
	}
}