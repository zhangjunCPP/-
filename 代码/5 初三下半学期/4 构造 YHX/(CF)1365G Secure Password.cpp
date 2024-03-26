#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e5+10;
int cnt[N];
int id[N],tot;
int ans[N];
signed main(){
    int n;
    cin>>n;
    for(int i=1;i<N;i++) cnt[i]=cnt[i>>1]+(i&1);
    for(int i=0;i<(1<<13);i++)if(cnt[i]==6)id[++tot]=i;
    for(int i=0;i<13;i++){
        int num=0;
        for(int j=1;j<=n;j++)if(id[j]&(1<<i))num++;
        if(num!=0){
            cout<<"? "<<num<<" ";
            for(int j=1;j<=n;j++) if(id[j]&(1<<i)) cout<<j<<" ";
            cout<<endl;
            cin>>ans[i];
        }
    }
    cout<<"! ";
    for(int i=1;i<=n;i++){
        int tmp=0;
        for(int j=0;j<13;j++)if(!(id[i]&(1<<j))) tmp|=ans[j];
        cout<<tmp<<" ";
    }
}