#include<bits/stdc++.h>
using namespace std;
const int N=1e5+10;
int n;
int random(int l,int r){return rand()%(r-l+1)+l;}
int ask[N];
int get_ask(int x,int y){
    cout<<"? "<<ask[x]<<" "<<ask[y]<<endl;
    int tmp;
    cin>>tmp;
    return tmp;
}
int get_val(int id){
    int ans=(1<<20)-1;
    for(int i=1;i<=20;i++){
        int tmp=random(1,n);
        while(tmp==id)tmp=random(1,n);
        ans&=get_ask(id,tmp);
    }
    return ans;
}
int ans[N];
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr),cout.tie(nullptr);
    srand(time(NULL));
    cin>>n;
    for(int i=1;i<=n;i++)ask[i]=i;
    for(int i=1;i<=n;i++){
        int x=random(1,n),y=random(1,n);
        while(x==y)x=random(1,n),y=random(1,n);
        swap(ask[x],ask[y]);
    }
    int id=1,now=get_val(1);
    for(int i=2;i<=n;i++)if(get_ask(id,i)==now)id=i,now=get_val(i);
    for(int i=1;i<=n;i++){
        if(i==id)ans[ask[i]]=0;
        else ans[ask[i]]=get_ask(i,id);
    }
    cout<<"! ";
    for(int i=1;i<=n;i++)cout<<ans[i]<<" ";
    cout<<endl;
    return 0;
}