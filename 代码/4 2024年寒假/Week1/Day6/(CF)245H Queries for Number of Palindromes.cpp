#include <bits/stdc++.h>
using namespace std;
const int mod=10007;
const int N=5005;
int dp[N][N];
bool flag[N][N];
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);
    string s;
    cin>>s;
    int siz=s.size();
    for(int len=1;len<=siz;len++){
        for(int i=0;i+len-1<siz;i++){
            int j=i+len-1;
            if(s[i]!=s[j]) continue;
            if(len<=2||flag[i+1][j-1]) flag[i][j]=true;
        }
    }
    for(int i=0;i<siz;i++)dp[i][i]=1;

    for(int len=2;len<=siz;len++){
        for(int i=0;i+len-1<siz;i++){
            int j=i+len-1;
            dp[i][j]=dp[i][j-1]+dp[i+1][j]-dp[i+1][j-1];
            if(s[i]==s[j]) dp[i][j]=dp[i][j]+flag[i][j];
        }
    }
    int T;
    cin>>T;
    int tmp=0;
    while(T--) {
        int l,r;
        cin>>l>>r;
        cout<<dp[l-1][r-1]<<"\n";
    }
}