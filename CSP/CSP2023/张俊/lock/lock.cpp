#include<bits/stdc++.h>
using namespace std;
int a[10][10];
bool f[10][10];
int zj[10];
int main(){
	freopen("lock.in","r",stdin);
	freopen("lock.out","w",stdout);
    int n;
    cin>>n;
    f[1][2]=1,f[2][3]=1,f[3][4]=1,f[4][5]=1;
    for(int i=1;i<=n;i++) for(int j=1;j<=5;j++) cin>>a[i][j];
    int ans=0;
    for(zj[1]=0;zj[1]<10;zj[1]++){
        for(zj[2]=0;zj[2]<10;zj[2]++){
            for(zj[3]=0;zj[3]<10;zj[3]++){
                for(zj[4]=0;zj[4]<10;zj[4]++){
                    for(zj[5]=0;zj[5]<10;zj[5]++){
                        bool flag=true;
                        for(int i=1;i<=n;i++) {
                            int tmp=0;
                            for(int j=1;j<=5;j++) {
                                if(zj[j]!=a[i][j])tmp++;
                            }
                            if(tmp>2) {flag=false;break;}
                            if(tmp==0) {flag=false;break;}
                            if(tmp==1) {
                                continue;
                            }
                            int x=0,y=0;
                            for(int j=1;j<=5;j++) {
                                if(zj[j]!=a[i][j]) {
                                    if(x) y=j;
                                    else x=j;
                                }
                            }
                            if(x>y) swap(x,y); 
                            if(!f[x][y]) {flag=false;break;}
                            int delta1=0;
                            int delta2=0;
                            int now=zj[x];
                            while(now!=a[i][x]) {
                            	delta1++;
                            	now++;
                            	if(now==10) now=0;
							}
							now=zj[y];
							while(now!=a[i][y]) {
                            	delta2++;
                            	now++;
                            	if(now==10) now=0;
							}
                            bool flag1=(delta1==delta2);
                            delta1=0,delta2=0;
                            now=zj[x];
                            while(now!=a[i][x]) {
                            	delta1++;
                            	now--;
                            	if(now==-1) now=9;
							}
							now=zj[y];
                            while(now!=a[i][y]) {
                            	delta2++;
                            	now--;
                            	if(now==-1) now=9;
							}
                            bool flag2=(delta1==delta2);
                            if(flag1||flag2) {
                            	continue;
							}
							else {
								flag=false;
								break;
							}
                        }
                        ans+=flag;
                    }
                }
            }
        }
    }
    cout<<ans;
    return 0;
}
