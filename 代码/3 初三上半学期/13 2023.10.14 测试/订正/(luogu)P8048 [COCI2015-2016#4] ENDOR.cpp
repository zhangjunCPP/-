#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e5+10;
int n,k,l;
double ans[50];
double cnt[50];
double tmp[50];

struct node{
	int d,col;
	char ch;
}a[N];
bool cmp(const node &x,const node &y){return x.d<y.d;}
signed main(){
	cin>>n>>k>>l;
	int last=0,sum=0;
	for(int i=1;i<=n;i++) cin>>a[i].d>>a[i].col>>a[i].ch;
	sort(a+1,a+n+1,cmp);
	for(int i=1;i<=n;i++) {	
		if(a[i].ch=='D') {
			ans[a[i].col]+=l-a[i].d;
			for(int j=0;j<k;j++) tmp[j]=cnt[j];
			for(int j=0;j<k;j++) cnt[(j+a[i].col)%k]=tmp[j];
			cnt[a[i].col]+=(a[i].d-last)/2.0;
			last=a[i].d;
			sum+=a[i].col;
		}
		else{
			ans[a[i].col]+=(a[i].d-last)/2.0;
			ans[(a[i].col+sum)%k]+=a[i].d/2.0;
			for(int j=0;j<k;j++) ans[(j+a[i].col)%k]+=cnt[j]; 
		}
	}
	for(int i=0;i<k;i++) {
		printf("%.1lf\n",ans[i]);
	}
	return 0;
}