#include<bits/stdc++.h>
#define int long long
#define abs(x) ((x)>0?(x):-(x))
using namespace std;
int T,n,k;
int d[2005];
bitset<1005>bs[1005];
char ch;
void cls(){
	for(int i=1;i<=n;++i)
		for(int j=1;j<=n;++j)
			bs[i][j]=0;
	return;
}
void mymain1(){
	cin>>n;
	for(int i=1;i<=n;++i)
		for(int j=1;j<=n;++j){
			cin>>ch;
			if(ch=='1')bs[i][j]=1;
			else bs[i][j]=0;
		}
	int mn=3e18,mx=-1;
	for(int i=1;i<=n;++i){
		for(int j=1;j<=n;++j){
			if(i==j and bs[i][j]){cout<<"No\n";goto asdf;}
			if(bs[i][j]+bs[j][i]==1){cout<<"No\n";goto asdf;}
			if(bs[i][j] and (bs[i]&bs[j]).count()){cout<<"No\n";goto asdf;}
		}
		mx=max(mx,(int)bs[i].count());
		mn=min(mn,(int)bs[i].count());
	}
	if(mx==mn)cout<<"Yes"<<'\n';
	else cout<<"No"<<'\n';
	asdf:cls();
	return;
}
bool case0(){
	int r=n;
	while(r){
		if(r%10==3 or r%10==9)
			return cout<<"Nope"<<'\n',1;
		r/=10;
	}
	return 0;
}
void case1(){
	cout<<n/2<<'\n';
	for(int i=1;i<=n;++i){
		for(int j=1;j<=n;++j)
			if(i<=n/2 and j>n/2 or i>n/2 and j<=n/2)cout<<1;
			else cout<<0;
		cout<<'\n';
	}
	return;
}
void case2(){
	if(n==1)cout<<"0\n0\n";
	else cout<<"0\n000\n000\n000\n";
	return;
}
bool ck(int x,int y){
	if(x==-1 or y==-1)return 0;
	if(abs(x-y)==1)return 1;
	if(x==1 and y==5 or x==5 and y==1)return 1;
	return 0;
}
int db[7];
void mk(){
	int l=1;
	for(int i=1;i<=n;++i)d[i]=-1;
	for(int i=1;i<=5;++i)
		while(db[i])d[l]=i,++l,--db[i];
	for(int i=1;i<=n;++i)
		for(int j=1;j<=n;++j)
			bs[i][j]=ck(d[i],d[j]);
	return;
}
void print(){
	for(int i=1;i<=n;++i){
		for(int j=1;j<=n;++j)
			cout<<bs[i][j];
		cout<<'\n';
	}
	return;
}
void case3(){
	for(int i=1;i<=5;++i)db[i]=k;
	mk();print();
	return;
}
void case4(){
	db[1]=k-1;db[2]=db[5]=k,db[3]=db[4]=k+1;
	mk();
	for(int i=2*k;i<=3*k;++i)bs[i][i+k+1]=bs[i+k+1][i]=0;
	print();
	return;
}
void case5(){
	for(int i=1;i<=7;++i)
		bs[i][i==1?7:i-1]=bs[i][i==7?1:i+1]=1;
	print();
	return;
}
void case6(){
	db[1]=k-2;db[2]=db[5]=k;db[3]=db[4]=k+2;
	mk();
	int l=0;
	for(int i=2*k-1;i<=3*k;++i){
		++l;if(l>k+2)l-=k+2;
		bs[i][l+3*k]=bs[l+3*k][i]=0;
		++l;if(l>k+2)l-=k+2;
		bs[i][l+3*k]=bs[l+3*k][i]=0;
	}
	print();
	return;
}
void mymain2(){
	k=n/5;
	if(case0());
	else if(n%2==0)case1();
	else if(n<5)case2();
	else {
		cout<<2*n/5<<'\n';
		if(n%5==0)case3();
		else if(n%5==1)case4();
		else if(n==7)case5();
		else case6();
	}
	cls();
	cout<<flush;
	return;
}
signed main(){
	cin.tie(0)->sync_with_stdio(0);
	cin>>T;
	while(T--)mymain1(),mymain2();
	return 0;
}