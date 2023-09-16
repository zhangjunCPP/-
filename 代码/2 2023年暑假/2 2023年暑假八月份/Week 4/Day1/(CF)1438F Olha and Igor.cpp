#include<bits/stdc++.h>
#define int long long
using namespace std;
int random(int l,int r){
	return (rand())%(r-l+1)+l;
}
int h; 
int sum[20000000];
signed main(){
	srand(time(NULL));
	cin>>h;
	int n=pow(2,h)-1;
	for(int i=1;i<=420;i++){
		int u=random(1,n),v=random(1,n),w=random(1,n);
		while(u==v||v==w||w==u)u=random(1,n),v=random(1,n),w=random(1,n);
		cout<<"? "<<u<<" "<<v<<" "<<w<<endl;
		int x;
		cin>>x;
		sum[x]++;
	}	
	int son1=0,son2=0;
	for(int i=1;i<=n;i++){
		if(sum[i]>sum[son1]) son2=son1,son1=i;
		else if(sum[i]>sum[son2]) son2=i;
	}
	for(int i=1;i<=n;i++){
		if(i==son1||i==son2) continue;
		cout<<"? "<<son1<<" "<<son2<<" "<<i<<endl;
		int x;
		cin>>x;
		if(x==i) {
			cout<<"! "<<i<<endl;
			return 0;
		}
	}
	return 0;
}

