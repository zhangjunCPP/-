#include<bits/stdc++.h>
using namespace std;
const int N=2e6+10;
int dp1[N];//存放第一个能消除的位置
int dp2[N];
int sum[30];
int pre[N],nex[N];
int main(){
	freopen("game.in","r",stdin);
	freopen("game.out","w",stdout);
	int clo=clock();
	int n;
	cin>>n;
	string s="$";
	string tmp;
	cin>>tmp;
	s+=tmp;
	dp1[n]=0;
	dp1[n-1]=(s[n]==s[n-1]?n:0);
	for(int l=1;l<=n;l++){
		memset(sum,0,sizeof sum);
		int tmp1=0,tmp2=0;
		for(int r=l;r<=n;r++) {
			int now=s[r]-'a'+1;
			sum[now]++;
			if(sum[now]>2&&(sum[now]&1)) tmp1--;
			else if(sum[now]%2==0)tmp1++;
			if(sum[now]==1) tmp2++;
			if(tmp1==tmp2){//开始判断 （链表）
				pre[l]=0;
				nex[l]=l+1;
				for(int j=l+1;j<r;j++) {
					pre[j]=j-1;
					nex[j]=j+1;
				}
				pre[r]=r-1;
				nex[r]=0;
				int last=-1;
				int ans=0;
				for(int i=l;i;){
					if(last==-1) {
						last=s[i]-'a'+1;
						i=nex[i];
						continue;
					}
					if(s[i]-'a'+1==last) {
						int pr=pre[pre[i]];
						int ne=nex[i];
						ans+=2;
						if(pr==0){
							last=-1;
							pre[ne]=0;
							i=ne;
							continue;
						}
						else if(ne==0){i=0;continue;}
						else {
							nex[pr]=ne;
							pre[ne]=pr;
							i=pr;
							last=-1;
							continue;
						}
					}
					else{last=s[i]-'a'+1;i=nex[i];continue;}
				}
				if(ans==r-l+1){
					dp1[l]=r;
					break;
				}
			}
		}
	}
	for(int i=n;i>=1;i--) {
		if(dp1[i]) {
			dp2[i]=1+dp2[dp1[i]+1];
		}
	}
	int ansss=0;
	for(int i=1;i<=n;i++){
		ansss+=dp2[i];
	}
	cout<<ansss;
}
