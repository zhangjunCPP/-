#include<bits/stdc++.h>
using namespace std;
const int N=1e5+10;
int a[N];
int last[N],b[N];
void solve(){
    int n,q,c;
    cin>>n>>q>>c;
    for(int i=1;i<=n;i++)cin>>a[i],last[i]=i,b[i]=0;
    for(int i=1;i<=q;i++){
        int x,y;
        cin>>x>>y;
        x++;
        last[y]=min(last[y],x);
        b[y]=1;
    }
    for(int i=n,j=n+1;i>=1;i--){
        if(j<=i){
            if(b[i]){puts("-1");return;}
            b[i]=-1;
        }
        j=min(j,last[i]);
    }
    int p=0;
    int Max=0;
    for(int i=1;i<=n;i++){
        if(b[i]==-1){
            if(a[i]==0)a[i]=1;
            else if(Max<a[i]){
                if(p==0){puts("-1");return;}
                a[p]=a[i];
            }
        }
        if(b[i]==0&&!a[i])a[i]=1,p=i;
        if(b[i]==1&&!a[i])a[i]=Max+1,p=i;
        Max=max(Max,a[i]);
    }
    for(int i=1,Max=0;i<=n;i++){
        if(b[i]==-1&&Max<a[i]){puts("-1");return;}
        if(b[i]==1&&Max>=a[i]){puts("-1");return;}
        Max=max(Max,a[i]);
        if(Max>c){puts("-1");return;}
    }
    for(int i=1;i<=n;i++)cout<<a[i]<<" ";
    cout<<"\n";
}
int main(){
    int T;
    cin>>T;
    while (T--)solve();
}