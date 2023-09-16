#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e5+10;
int a[N];
pair<int,int> change1[N];
vector<pair<int,int> > change2[N];
vector<pair<double,int> > change3;
int opt[N];
bool cmp1(const pair<int,int> &x,const pair<int,int> &y){return x>y;}
bool cmp2(const pair<double,int> &x,const pair<double,int> &y){return x>y;}
bool cmp3(const pair<double,int> &x,const pair<double,int> &y){return opt[x.second]<opt[y.second];}
signed main() {
    int k,n,m;
    cin>>k>>n>>m;
    for(int i=1;i<=k;i++) cin>>a[i];
    for(int i=1;i<=n;i++){
        int id,val;
        cin>>opt[i]>>id>>val;
        if(opt[i]==1)change1[id]=max(change1[id],{val,i});
        else if (opt[i]==2)change2[id].push_back({val,i});
        else change3.push_back({val,i});
    }
    for(int i=1;i<=k;i++){
        if(change1[i].first<a[i]) continue;
        change2[i].push_back({change1[i].first-a[i],change1[i].second});
    }
    for(int i=1;i<=k;i++){
        sort(change2[i].begin(), change2[i].end(), cmp1);
        int tmp=a[i];
        for(auto j:change2[i]){
            change3.push_back({1.0l*(tmp+j.first)/tmp,j.second});
            tmp+=j.first;
        }
    }
    sort(change3.begin(), change3.end(),cmp2);
    int tmp=0;
    m=min(m,(long long)change3.size());
    sort(change3.begin(), change3.begin()+m,cmp3);
    cout<<m<<"\n";
    for(auto now:change3){
        if(tmp==m) return 0;
        cout<<now.second<<" ";
        tmp++;
    }
}