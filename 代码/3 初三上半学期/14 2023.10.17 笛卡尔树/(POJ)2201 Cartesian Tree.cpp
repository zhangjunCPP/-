#include<iostream>
#include<algorithm>
#define int long long
using namespace std;
const int N=1e5+10;
int n;
struct node{int k,w;int id;}a[N];
int ls[N],rs[N],fa[N];
int q[N],top;
void build(){
    q[1]=1,top=1;
    for(int i=2;i<=n;i++) {
        while(top&&a[q[top]].w>a[i].w) top--;
        if(top==0) ls[i]=q[1];
        else{ls[i]=rs[q[top]];rs[q[top]]=i;}
        q[++top]=i;
    }
}
int tmp[N];
bool cmp(const node &x,const node &y){return x.k<y.k;}
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);
    cin>>n;
    for(int i=1;i<=n;i++) {
        cin>>a[i].k>>a[i].w;
        a[i].id=i;
    }
    sort(a+1,a+n+1,cmp);
    for(int i=1;i<=n;i++) tmp[a[i].id]=i;
    build();
    for(int i=1;i<=n;i++) {
        fa[a[ls[i]].id]=a[i].id;
        fa[a[rs[i]].id]=a[i].id;
    }
    cout<<"YES\n";
    for(int i=1;i<=n;i++) cout<<fa[i]<<" "<<a[ls[tmp[i]]].id<<" "<<a[rs[tmp[i]]].id<<"\n";
    return 0;
}