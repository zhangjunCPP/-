#include<bits/stdc++.h>
using namespace std;
const int N=1e6+10;
int opt[N];
bool check(int x,int y){
	if(x==0&&y==1) return true;
	if(x==1&&y==2) return true;
	if(x==2&&y==0) return true;
	return false;
}
int main(){
	freopen("botbox.in","r",stdin);
	freopen("botbox.out","w",stdout);
	int n,k;
	cin>>n>>k;
	string s;
	cin>>s;
	for(int i=0;i<n;i++) opt[i+1]=s[i]-'A';
	queue<int> q;
	int winner=1;
	for(int i=2;i<=n;i++) q.push(i);
	for(int i=1;i<=k;i++){
		int now=q.front();
		q.pop();
		if(check(opt[now],opt[winner])){
			q.push(winner);
			winner=now;
		}
		else q.push(now);
	}
	cout<<char(opt[winner]+'A'); 
	while(!q.empty()){
		int now=q.front();
		q.pop();
		cout<<char(opt[now]+'A');
	}
	

	return 0;
}

/*
暴力分是比较好拿的 
*/
 
