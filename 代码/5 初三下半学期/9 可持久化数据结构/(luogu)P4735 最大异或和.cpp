#include<bits/stdc++.h>
using namespace std;
const int N=3e7+10;
int ch[N][2];
int tot;
int cnt[N];
int rt[N],top;
void insert(int x){
    tot++;
    rt[++top]=tot;
    int k1=rt[top],k2=rt[top-1];
    for(int i=24;i>=0;i--){
        int tmp=(x>>i)&1;
        ch[k1][!tmp]=ch[k2][!tmp];
        ch[k1][tmp]=++tot;
        k1=ch[k1][tmp],k2=ch[k2][tmp];
        cnt[k1]=cnt[k2]+1;
    }
}
int query(int l,int r,int x){
    int ans=0;
    int k1=rt[l],k2=rt[r];
    for(int i=24;i>=0;i--){
        int tmp=(x>>i)&1;
        if(cnt[ch[k2][!tmp]]>cnt[ch[k1][!tmp]])ans+=(1<<i),k1=ch[k1][!tmp],k2=ch[k2][!tmp];
        else k1=ch[k1][tmp],k2=ch[k2][tmp];
    }
    return ans;
}
int main(){
    int n,m;
    cin>>n>>m;
    int sum=0;
    insert(0);
    for(int i=1;i<=n;i++){
        int x;
        cin>>x;
        sum^=x;
        insert(sum);
    }
    while(m--){
        string opt;
        cin>>opt;
        if(opt=="A"){
            int x;
            cin>>x;
            sum^=x;
            insert(sum);
        }
        else{
            int l,r,x;
            cin>>l>>r>>x;
            cout<<query(l-1,r,x^sum)<<"\n";
        }
    }
}