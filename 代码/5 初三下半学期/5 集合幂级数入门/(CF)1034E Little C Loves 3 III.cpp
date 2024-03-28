#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=(1<<21);
int a[N],b[N];
int c[2][2]={{1,0},{1,1}};//Or
int ic[2][2]={{1,0},{-1,1}};//Or
int n;
void FWT(int *A,int C[2][2]){
    for(int len=1;len<n;len*=2){
        for(int st=0;st<n;st+=len*2){
            for(int i=st;i<st+len;i++){
                int tmp=A[i];
                A[i]=C[0][0]*A[i]+C[0][1]*A[i+len];
                A[i+len]=C[1][0]*tmp+C[1][1]*A[i+len];
            }
        }
    }
}
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr),cout.tie(nullptr);
    string s,t;
    cin>>n>>s>>t;
    n=(1<<n);
    for(int i=0;i<n;i++){
        a[i]=(s[i]&15ll)<<(__builtin_popcount(i)<<1);
        b[i]=(t[i]&15ll)<<(__builtin_popcount(i)<<1);
    }
    FWT(a,c),FWT(b,c);
    for(int i=0;i<n;i++)a[i]*=b[i];
    FWT(a,ic);
    for(int i=0;i<n;i++)putchar((a[i]>>(__builtin_popcount(i)<<1)&3)|48);
}