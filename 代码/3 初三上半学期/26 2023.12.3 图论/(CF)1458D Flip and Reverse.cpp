#include<bits/stdc++.h>
#define int long long
using namespace std;
const int lim=5e5+10;
const int N=1e7+10;
int cnt[N][2];
void solve() {
    string s;
    cin>>s;
    int n=s.size();
    int now=0;
    for(int i;i<n;i++) {
        cnt[now+lim][s[i]-'0']++;
        if(s[i]=='0') now--;
        else now++;
    }
    now=0;
    for(int i=0;i<n;i++){
        if(cnt[now+lim][0]&&cnt[now-1+lim][1]) {
            cnt[now+lim][0]--;
            now--;
            putchar('0');
        }
        else if(cnt[now+lim][1]) {
            cnt[now+lim][1]--;
            now++;
            putchar('1');
        }
        else {
            cnt[now+lim][0]--;
            now--;
            putchar('0');
        }
    }
    putchar('\n');
}
signed main(){
    int T;
    cin>>T;
    while(T--) solve();
    return 0;
}