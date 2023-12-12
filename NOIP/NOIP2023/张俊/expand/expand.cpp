#include<bits/stdc++.h>
using namespace std;
const int N=1e5+10;
int x[N],y[N];
int tmpx[N],tmpy[N];
int main(){
    freopen("expand.in","r",stdin);
    freopen("expand.out","w",stdout);
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);
    int c,n,m,q;
    cin>>c>>n>>m>>q;
    if(c!=1&&c!=2) {cout<<0;while(q--)cout<<0; return 0;}
    for(int i=1;i<=n;i++) cin>>x[i];
    for(int i=1;i<=m;i++) cin>>y[i];
    if(c==1) {
        if(x[1]!=y[1]) cout<<1;
        else cout<<0;
    }
    if(c==2) {
        if(n==1) {
            if(m==1) {
                if(x[1]!=y[1]) cout<<1;
                else cout<<0;
            }
            else if(m==2) {
                int tmp1=y[1]-x[1],tmp2=y[2]-x[1];
                if(tmp1>0&&tmp2>0) cout<<1;
                else if(tmp1<0&&tmp2<0) cout<<1;
                else cout<<0;
            }
        }
        if(n==2) {
            if(m==1) {
                int tmp1=y[1]-x[1],tmp2=y[1]-x[2];
                if(tmp1>0&&tmp2>0) cout<<1;
                else if(tmp1<0&&tmp2<0) cout<<1;
                else cout<<0;
            }
            else if(m==2) {
                if(x[1]<y[1]&&x[2]<y[2]) cout<<1;
                else if(x[1]>y[1]&&x[2]>y[2]) cout<<1;
                else cout<<0;
            }
        }
    }
    while(q--) {
        for(int i=1;i<=n;i++) tmpx[i]=x[i];
        for(int i=1;i<=m;i++) tmpy[i]=y[i]; 
        int kx,ky;
        cin>>kx>>ky;
        for(int i=1;i<=kx;i++) {
            int p,v;
            cin>>p>>v;
            tmpx[p]=v;
        }
        for(int i=1;i<=ky;i++) {
            int p,v;
            cin>>p>>v;
            tmpy[p]=v;
        }
        if(c==1) {
            if(tmpx[1]!=tmpy[1]) cout<<1;
            else cout<<0;
        }
        if(c==2) {
            if(n==1) {
                if(m==1) {
                    if(tmpx[1]!=tmpy[1]) cout<<1;
                    else cout<<0;
                }
                else if(m==2) {
                    int tmp1=tmpy[1]-tmpx[1],tmp2=tmpy[2]-tmpx[1];
                    if(tmp1>0&&tmp2>0) cout<<1;
                    else if(tmp1<0&&tmp2<0) cout<<1;
                    else cout<<0;
                }
            }
            if(n==2) {
                if(m==1) {
                    int tmp1=tmpy[1]-tmpx[1],tmp2=tmpy[1]-tmpx[2];
                    if(tmp1>0&&tmp2>0) cout<<1;
                    else if(tmp1<0&&tmp2<0) cout<<1;
                    else cout<<0;
                }
                else if(m==2) {
                    if(tmpx[1]<tmpy[1]&&tmpx[2]<tmpy[2]) cout<<1;
                    else if(tmpx[1]>tmpy[1]&&tmpx[2]>tmpy[2]) cout<<1;
                    else cout<<0;
                }
            }
        }
    
    }
    return 0;
}