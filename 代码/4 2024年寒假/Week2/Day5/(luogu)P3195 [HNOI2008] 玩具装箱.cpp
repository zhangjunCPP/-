#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N=5e5+10;
int n,L;
int c[N];
int s[N];
int dp[N];
int Y(int x){return dp[x]+(s[x]+L)*(s[x]+L);}
int X(int x){return s[x];}
double slope(int x,int y){return (1.0*(Y(x)-Y(y)))/(1.0*(X(x)-X(y)));}
int q[N],l,r;
signed main(){
    cin>>n>>L;
    L++;
    for(int i=1;i<=n;i++)cin>>c[i];
    for(int i=1;i<=n;i++)s[i]=s[i-1]+c[i]+1;
    l=1,r=1;
    q[1]=0;
    for(int i=1;i<=n;i++){
        while(l<r&&slope(q[l],q[l+1])<=2*s[i])l++;
        int j=q[l];
        dp[i]=dp[j]+(s[i]-s[j]-L)*(s[i]-s[j]-L);
        while(l<r&&slope(q[r-1],q[r])>=slope(q[r],i))r--;
        q[++r]=i;
    }
    cout<<dp[n];
    return 0;
}