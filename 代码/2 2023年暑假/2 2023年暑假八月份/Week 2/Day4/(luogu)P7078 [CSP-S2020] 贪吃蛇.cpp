#include<bits/stdc++.h>
#define int long long
using namespace std;
int a[100000000];
int n;
signed main() {
    int t;
    cin>>t;
    for(int time=1; time<=t; time++) {
        if(time==1) {
            cin>>n;
            for(int i=1; i<=n; i++)cin>>a[i];
        } else {
            int k;
            cin>>k;
            int x,y;
            for(int i=1; i<=k; i++) {
                cin>>x>>y;
                a[x]=y;
            }
        }
        int ans=0;
        deque<pair<int,int> > q1,q2;
        for(int i=1; i<=n; i++)q1.push_back(make_pair(a[i],i));
        while(1) {
            if(q1.size()+q2.size()==2) {
                ans=1;
                break;
            }
            int x,y,id;
            y=q1.front().first,q1.pop_front();
            if(q2.empty()||(!q1.empty()&&q1.back()>q2.back())) x=q1.back().first,id=q1.back().second,q1.pop_back();
            else x=q2.back().first,id=q2.back().second,q2.pop_back();
            pair<int,int> now(x-y,id);
            if(q1.empty()||q1.front()>now) {
                ans=q1.size()+q2.size()+2;
                int cnt=0;
                while(1) {
                    cnt++;
                    if(q1.size()+q2.size()+1==2) {
                        if(cnt%2==0)ans--;
                        break;
                    }
                    int x,id;
                    if(q2.empty()||(!q1.empty()&&q1.back()>q2.back())) x=q1.back().first,id=q1.back().second,q1.pop_back();
                    else x=q2.back().first,id=q2.back().second,q2.pop_back();
                    now= {x-now.first,id};
                    if((q1.empty()||now<q1.front())&&(q2.empty()||now<q2.front()));
                    else {
                        if(cnt%2==0)ans--;
                        break;
                    }
                }
                break;
            } else q2.push_front(now);
        }
        cout<<ans<<"\n";
    }
    return 0;
}