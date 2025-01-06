#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int N=2e5+10;
int n,l,q;
struct node{
    int v,nex;
    int val1,val2;
}a[N*2];
int first[N],cnt;
void add(int u,int v,int val1,int val2){
    a[++cnt]={v,first[u],val1,val2};
    first[u]=cnt;
}
struct matrix{//min+
    ll a[2][2];
    matrix(){memset(a,0x3f,sizeof a);}
    void init(){a[0][0]=a[1][1]=0;}
    matrix operator*(const matrix&oth)const{
        matrix ans;
        for(int i=0;i<2;i++)for(int j=0;j<2;j++)for(int k=0;k<2;k++)ans.a[i][j]=min(ans.a[i][j],a[i][k]+oth.a[k][j]);
        return ans;
    }
}up[N][20],down[N][20];
int fa[N][20],dep[N];
void dfs(int u,int dad){
    dep[u]=dep[dad]+1;
    fa[u][0]=dad;
    for(int i=1;i<20;i++){
        fa[u][i]=fa[fa[u][i-1]][i-1];
        up[u][i]=up[u][i-1]*up[fa[u][i-1]][i-1];
        down[u][i]=down[fa[u][i-1]][i-1]*down[u][i-1];
    }
    for(int i=first[u];i;i=a[i].nex){
        int v=a[i].v,val1=a[i].val1,val2=a[i].val2;
        if(v==dad)continue;
        up[v][0].a[0][0]=val1;up[v][0].a[0][1]=l+val1-val2;
        up[v][0].a[1][0]=val1;up[v][0].a[1][1]=val1-val2;
        down[v][0].a[0][0]=val1;down[v][0].a[0][1]=l+val1+val2;
        down[v][0].a[1][0]=val1;down[v][0].a[1][1]=val1+val2;
        dfs(v,u);
    }
}
matrix LCA(int x,int y){
    //因为是从x->y,且矩阵乘法不具有交换律，所以不能交换x,y
    matrix Up,Down;Up.init(),Down.init();
    for(int i=19;i>=0;i--)if(dep[fa[x][i]]>=dep[y])Up=Up*up[x][i],x=fa[x][i];
    for(int i=19;i>=0;i--)if(dep[fa[y][i]]>=dep[x])Down=down[y][i]*Down,y=fa[y][i];
    if(x==y)return Up*Down;
    for(int i=19;i>=0;i--){
        if(fa[x][i]!=fa[y][i]){
            Up=Up*up[x][i],Down=down[y][i]*Down;
            x=fa[x][i],y=fa[y][i];
        }
    }
    Up=Up*up[x][0];Down=down[y][0]*Down;
    return Up*Down;
}
int main(){
    ios::sync_with_stdio(false);cin.tie(nullptr),cout.tie(nullptr);
    cin>>n>>l>>q;
    for(int i=1;i<n;i++){
        int u,v,val1,val2,opt;
        cin>>u>>v>>val1>>val2>>opt;
        add(u,v,val1,opt?-val2:val2);
        add(v,u,val1,opt?val2:-val2);
    }
    dfs(1,0);
    while(q--){
        int x,y;
        cin>>x>>y;
        matrix ans;
        ans.a[0][0]=0,ans.a[0][1]=l;
        ans=ans*LCA(x,y);
        cout<<min(ans.a[0][0],ans.a[0][1])<<"\n";
    }
}