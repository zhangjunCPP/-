#include<bits/stdc++.h>
using namespace std;
const int N=1000+10;
char up[N],down[N];
char L,R;
char mp[N];
char ans[N];
int main() {
	int n,m;
	cin>>n>>m;
	if(n==1) {
		char ch;
		cin>>ch;
		for(int i=1;i<=m;i++)cin>>up[i];
		cin>>ch;
		cin>>L;
		for(int i=1;i<=m;i++)cin>>mp[i];
		cin>>R;
		cin>>ch;
		for(int i=1;i<=m;i++)cin>>down[i];
		cin>>ch;
		for(int i=1;i<=m;i++) {
			if(mp[i]=='x') {
				if(up[i]!='.'||down[i]!='.'){puts("NO");return 0;}
				ans[i]='x';
			}
			else {
				if(up[i]!='.'&&down[i]!='.'&&up[i]!=down[i]){puts("NO");return 0;}
				if(up[i]=='.'&&down[i]=='.')ans[i]='@';
				else ans[i]=(up[i]=='.'?down[i]:up[i]);
			}
		}
		if(L!='.') {
			for(int i=1;i<=m;i++) {
				if(ans[i]=='@'){ans[i]=L;break;}
				if(ans[i]=='x')continue;
				if(ans[i]!=L){puts("NO");return 0;}
				break;
			}
		}
		if(R!='.') {
			for(int i=m;i>=1;i--) {
				if(ans[i]=='@'){ans[i]=R;break;}
				if(ans[i]=='x')continue;
				if(ans[i]!=R){puts("NO");return 0;}
				break;
			}
		}
		cout<<"YES\n";
		for(int i=1;i<=m;i++) {
			if(ans[i]=='@'||ans[i]=='x')ans[i]='.';
			cout<<ans[i];
		}
		return 0;
	}
}
/*
 *不给checker做个鬼
 */