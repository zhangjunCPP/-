#include <bits/stdc++.h>
using namespace std;
const int N=1e3+10;
double C[N][N];
void init() {
    for(int i=0;i<N;i++) C[i][0]=C[i][i]=1;
    for(int i=1;i<N;i++)for(int j=1;j<N;j++) C[i][j]=(C[i-1][j]+C[i-1][j-1]);
}   
double dp1[N][N],dp2[N][N];
int main(){
    init();
    int n,d,r;
    cin>>n>>d>>r;
    dp1[n][n]=1,dp2[n][n]=r;
    for(int j=n+1;j<=n+d;j++) {
        for(int i=1;i<=n;i++) {  //最上边一行的个数
            for(int k=i;k<=n;k++) { //第二行的个数
                dp1[i][j]+=dp1[k][j-i]*C[k][i];
                dp2[i][j]+=(dp2[k][j-i]+min(i,r)*dp1[k][j-i])*C[k][i];
            }
        }
    }
    double sum1=0,sum2=0;
    for(int i=1;i<=n;i++) sum1+=dp2[i][n+d],sum2+=dp1[i][n+d];
    printf("%.10lf",sum1/sum2);
    return 0;
}