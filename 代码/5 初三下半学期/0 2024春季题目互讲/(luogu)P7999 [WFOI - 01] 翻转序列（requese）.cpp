#include <bits/stdc++.h>
using namespace std;
const int N=1e6+10;
int a[N];
vector<pair<int,int>> ans;
void rev(int l,int r){
	reverse(a+l,a+r+1);
	ans.push_back({l,r});
}
void print(){
	cout<<ans.size()<<"\n";
	for(auto it:ans)cout<<it.first<<" "<<it.second<<"\n";
}
int main(){
	int n;
	cin>>n;
	for(int i=1;i<=n;i++)cin>>a[i];
	if(n<=4){
		cout<<3<<"\n";
		for(int i=1;i<n;i++){
			int pos;
			for(int j=i;j<=n;j++)if(a[j]==i)pos=j;
			while((pos-i)%3)rev(pos-1,pos),pos--;
			while(pos>i)rev(pos-3,pos),pos-=3;
		}
		print();
		return 0;
	}
	int x=n>>2;
	if(!(x&1))x--;
	int y=(x+1)>>1;
	cout<<x<<"\n";
	for(int i=n;i>(n/2);i--){
		int pos;
		for(int j=i;j;j--)if(a[j]==i)pos=j;
		while(pos+x<=i)rev(pos,pos+x),pos+=x;
		if(i==pos)continue;
		if((i-pos)&1)rev(pos-x,pos),pos-=x;
		int tmp=i-x;
		rev((pos+tmp)/2-y+1,(pos+tmp)/2+y);
		rev(tmp,tmp+x);
	}
	for(int i=1;i<=(n/2);i++){
		int pos;
		for(int j=i;j<=n;j++)if(a[j]==i)pos=j;
		while(pos-x>=i)rev(pos-x,pos),pos-=x;
		if(i==pos)continue;
		bool flag=false;
		if((pos-i)&1)rev(pos,pos+x),pos+=x,flag=true;
		int tmp=i+x;
		rev((pos+tmp)/2-y+1,(pos+tmp)/2+y);
		rev(i,i+x),rev(i+1,i+x-1);
		rev((pos+tmp)/2-y+1,(pos+tmp)/2+y);
		if(flag)rev(pos-x,pos);
	}
	print();
}