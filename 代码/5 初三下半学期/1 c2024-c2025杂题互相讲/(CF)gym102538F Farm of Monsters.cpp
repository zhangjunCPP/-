#include <bits/stdc++.h>
#define int long long
using namespace std;
priority_queue<int> q;
signed main(){
    int n,a,b;
    cin>>n>>a>>b;
    int ans=0,now=0;
    for(int i=1;i<=n;i++){
        int x;
        cin>>x;
        int bi=ceil(1.0*x/b);
        int ai=ceil(1.0*((x-1)%b+1)/a);
        q.push(ai+1);
        ans++;
        now+=bi-ai-1;
        if(now<-1){
            ans--;
            now+=q.top();
            q.pop();
        }
    }
    cout<<ans;
}