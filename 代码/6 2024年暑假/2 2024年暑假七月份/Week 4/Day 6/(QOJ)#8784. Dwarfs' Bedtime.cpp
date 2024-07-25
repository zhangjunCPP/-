#include<bits/stdc++.h>
using namespace std;
const int N=1e4;
bool query(int time,int pos) {
	cout<<"at ";
	int hour=time/60,minute=time%60;
	if(hour<10)cout<<"0";cout<<hour<<":";
	if(minute<10)cout<<"0";cout<<minute<<" ";
	cout<<"check "<<pos<<"\n";
	string ans;
	cin>>ans;
	return ans=="awake";
}
bool sleep[N];
bool vis[N];
vector<int>need[N];
int ans[N];
void report(int x) {
	int hour=ans[x]/60,minute=ans[x]%60;
	if(hour<10)cout<<"0";cout<<hour<<":";
	if(minute<10)cout<<"0";cout<<minute<<"\n";
}
int main() {
	int n;
	cin>>n;
	for(int i=1;i<=n;i++)sleep[i]=query(0,i);
	for(int i=1,sum=0;i<=19;i++) {
		sum+=49-i;
		if(sum>=720)sum=719;
		for(int j=1;j<=n;j++) {
			if(vis[j])continue;
			bool now=query(sum,j);
			if(now!=sleep[j]) {
				vis[j]=true;
				for(int k=sum-(49-i)+1+720;k<=sum+720;k++)need[k].push_back(j);
			}
		}
	}
	for(int i=1;i<=n;i++)if(!vis[i])ans[i]=(sleep[i]?720:0);
	memset(vis,false,sizeof vis);
	for(int i=720;i<=1440-1;i++) {
		for(int j:need[i]) {
			if(vis[j])continue;
			bool now=query(i,j);
			if(now==sleep[j]) {
				if(now)ans[j]=i-720;
				else ans[j]=i;
				vis[j]=true;
			}
		}
	}
	puts("answer");
	for(int i=1;i<=n;i++)report(i);
}