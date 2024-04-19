#include<bits/stdc++.h>
using namespace std;
const int N=1e5+10;
int a[N];
bool vis1[N],vis2[N];
void solve(){
    memset(vis2,false,sizeof vis2);
    int k,q;
    cin>>k>>q;
    for(int i=1;i<=k;i++)cin>>a[i],vis2[a[i]]=true;
    while(q--){
        memset(vis1,false,sizeof vis1);
        int n;
        cin>>n;
        int num=n;
        while(true){
            int tmp=0,tot=0;
            for(int i=1;i<=n;i++){
                if(!vis1[i]){
                    tot++;
                    if(vis2[tot])vis1[i]=true,tmp++,num--;
                }
            }
            if(!tmp)break;
        }
        cout<<num<<" ";
    }
    cout<<"\n";
}
int main(){
    int T;
    cin>>T;
    while(T--)solve();
}