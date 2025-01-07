#include<bits/stdc++.h>
using namespace std;
void solve(){
	int a,b,c,d;
	string s;
	cin>>a>>b>>c>>d>>s;
	int n=s.length();
	int tmp1=0,tmp2=0;
	for(int i=0;i<n;++i)if(s[i]=='A')++tmp1;else ++tmp2;
	if(!(tmp1==a+c+d&&tmp2==b+c+d)){
		puts("NO");
		return;
	}
	int sum=0;
	vector<int> ans1,ans2;
	for(int i=0;i<n;){
		int j=i+1;
		while(j<n&&s[j]!=s[j-1])++j;
		int len=j-i;
		if(len==1){
			i=j;
			continue;
		}
		if(len&1)sum+=len/2;
		else{
			len/=2;
			if(s[i]=='A')ans1.push_back(len);
			else ans2.push_back(len);
		}
		i=j;
	}
	sort(ans1.begin(), ans1.end());
	sort(ans2.begin(), ans2.end());
	for (int i: ans1) { //ABABABAB
		if(c>=i)c-=i;
		else{
			i-=c+1;
			c=0;
			d-=min(d,i);
		}
	}
	for(int i:ans2){ //BABABABA
		if(d>=i)d-=i;
		else{
			i-=d+1;
			d=0;
			c-=min(c,i);
		}
	}
	puts(sum>=c+d?"Yes":"No");
}
int main(){
	int T;
	cin>>T;
	while(T--)solve();
}