#include<bits/stdc++.h>
#define int long long
#define PII pair<int,int>
using namespace std;
const int N=3e5+5;
int n,m;
map<PII,bool> mp;
int pre[N],nex[N];
int read(){
    int x=0,f=1; char ch=getchar();
    while(!isdigit(ch)) {if(ch=='-') f=-1; ch=getchar();}
    while(isdigit(ch)) {x=x*10+(ch-'0'); ch=getchar();}
    return x*f;
}
signed main(){
    n=read(),m=read();
    for(int i=1;i<=m;i++) {
        int u,v;
        u=read(),v=read();
        if(u>v) swap(u,v);
        mp[{u,v}]=1;
    }
    bool same=true;
    bool flag=(mp.find({1,2})!=mp.end());
    int x=2;//分割点
    nex[1]=2;
    pre[2]=1;
    int End=2;
    for(int i=3;i<=n;i++){
        if(same){
            nex[x]=i;
            pre[i]=x;
            if((mp.find({x,i})!=mp.end())!=flag)same=false;
            else x=i;
            End=i;
            continue;
        }
        else {
            if((mp.find({x,i})!=mp.end())==flag){
                int b=nex[x];
                pre[b]=i;
                nex[i]=b;
                pre[i]=x;
                nex[x]=i;
                if((mp.find({b,i})!=mp.end())==flag)x=b;
                else x=i;
                if(nex[x]==0) {
                    same=true;
                    flag=(mp.find({b,i})!=mp.end());
                    x=b;
                }
            }
            else {
                int a=pre[x];
                pre[i]=a;
                nex[i]=x;
                pre[x]=i;
                nex[a]=i;
                if((mp.find({a,i})!=mp.end())==flag)x=i;
                else x=a;
                if(pre[x]==0){
                    same=true;
                    flag=(mp.find({a,i})!=mp.end());
                    x=End;
                }
            }
        }
    }
    cout<<"1 ";
    for(int i=nex[1];i;i=nex[i]) cout<<i<<" ";
    return 0;
}