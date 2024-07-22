#include<bits/stdc++.h>
#define IL inline
#define _ 2097152
#define __ 1000005
#define ll long long
using namespace std ;

#define mod 998244353
#define pr 3

int n,m,R,K,f[_],Ans,Fac[__],IFac[__],wn[30],f1[_],f2[_],nn,Len,rev[_],g[_],h[_] ;

IL int Pow(int ts , int js) {
	int al = 1 ;
	while(js) {
		if(js & 1) al = 1ll * al * ts % mod ;
		ts = 1ll * ts * ts % mod ; js >>= 1 ; 
	}return al ;
}
IL void Numb(int N) {
	for(int i = 0; i <= 25; i ++) wn[i] = Pow(pr , (mod - 1) / (1 << i)) ;
	Fac[0] = 1 ; for(int i = 1; i <= N; i ++) Fac[i] = 1ll * i * Fac[i - 1] % mod ;
	IFac[N] = Pow(Fac[N] , mod - 2) ;
	for(int i = N; i >= 1; i --) IFac[i - 1] = 1ll * i * IFac[i] % mod ;
	for(int i = 0; i <= N; i ++) Fac[i] = Pow(Fac[i] , R) , IFac[i] = Pow(IFac[i] , R) ; 
	return ;
}

IL void NTT(int *P , int op , int len) {
	int nl = 0 ; for(nn = 1; nn < len; nn <<= 1) ++ nl ;
	for(int i = 0; i < nn; i ++) rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (nl - 1)) ;
	for(int i = 0; i < nn; i ++) if(rev[i] > i) swap(P[i] , P[rev[i]]) ;
	for(int i = 1,id = 0; i < nn; i <<= 1) {
		++ id ;
		for(int j = 0,dt = (i << 1) ; j < nn; j += dt) {
			int w = 1 ;
			for(int k = 0; k < i; k ++ , w = 1ll * w * wn[id] % mod) {
				int X = P[j + k] , Y = 1ll * w * P[j + k + i] % mod ;
				P[j + k] = (X + Y) % mod ; P[j + k + i] = (X - Y + mod) % mod ; 
			}
		}
	}if(op < 0) {
		for(int j = 1; j < nn / 2; j ++) swap(P[j] , P[nn - j]) ;
		int INV = Pow(nn , mod - 2) ;
		for(int j = 0; j < nn; j ++) P[j] = 1ll * P[j] * INV % mod ; 
	}return ;
}
IL void Poly_Inv(int *a , int *b , int len) {
	if(len == 1) {b[0] = Pow(a[0] , mod - 2) ; return ; }
	Poly_Inv(a , b , len >> 1) ;
	for(int i = 0; i < len; i ++) f1[i] = a[i] , f2[i] = b[i] ;
	NTT(f1 , 1 , len << 1) ; NTT(f2 , 1 , len << 1) ;
	for(int i = 0; i < (len << 1); i ++) f1[i] = 1ll * f1[i] * f2[i] % mod * f2[i] % mod ;
	NTT(f1 , -1 , len << 1) ;
	for(int i = 0; i < len; i ++) b[i] = (2ll * b[i] % mod - f1[i] + mod) % mod ;
	for(int i = 0; i < (len << 1) ; i ++) f1[i] = f2[i] = 0 ; 
}

int main() {
	freopen("ghost.in", "r", stdin);
	freopen("ghost.out", "w", stdout);
	cin >> n >> R >> K ; m = (n - 1) / K ; 
	Numb(n) ;
	for(Len = 1; Len <= n; Len <<= 1) ;
	for(int i = 1; i <= m; i ++) g[i] = IFac[i * K] ; g[0] ++ ;
	Poly_Inv(g , h , Len) ;	
	g[0] -- ; for(int i = 1; i <= n; i ++) g[i] = mod - g[i] ;
	for(Len = 1; Len <= 2 * n; Len <<= 1) ;
	NTT(g , 1 , Len) ; NTT(h , 1 , Len) ;
	for(int i = 0; i < nn; i ++) f[i] = 1ll * g[i] * h[i] % mod ;
	NTT(f , -1 , Len) ;
	f[0] = 1 ;
	for(int i = 0; i <= m; i ++) Ans = (Ans + 1ll * f[i] * IFac[n - i * K] % mod) % mod ;
	Ans = 1ll * Ans * Fac[n] % mod ;
	if(m & 1) Ans = mod - Ans ; cout << Ans << endl ;
	return 0 ; 
}
