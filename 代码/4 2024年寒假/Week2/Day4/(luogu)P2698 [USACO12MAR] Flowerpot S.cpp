#include<bits/stdc++.h>
using namespace std;
const int N=1e5+10;
struct node{int x,y;}a[N];
bool cmp(node x,node y){return x.y<y.y;}
multiset<int>st;
int main(){
    int n,d;
    cin>>n>>d;
    for(int i=1;i<=n;++i)cin>>a[i].x>>a[i].y,st.insert(a[i].x);
    sort(a+1,a+1+n,cmp);
    int ans=0x3f3f3f3f;
    int tmp=1;
    for(int i=1;i<=n;++i){
        while(tmp<=n&&a[tmp].y<a[i].y+d) {st.erase(st.find(a[tmp].x));tmp++;}
        auto it=st.lower_bound(a[i].x);
        if(it!=st.end())ans=min(ans,*it-a[i].x);
        it=st.upper_bound(a[i].x-1);
        if(it!=st.begin())ans=min(ans,a[i].x-*(--it));
    }
    if(ans==0x3f3f3f3f) ans=-1;
    cout<<ans;
    return 0;
}