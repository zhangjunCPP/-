#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdio>
#include <map>
const int N = 505, mod = 998244853, inv3 = 665496569;
typedef long long ll; 
using namespace std;

int n, c[N][4], pos[4], u[4], d[4], cnt, sum[N * N], nxt[N * N]; 
struct nd
{
	int u, r, d, l;
	nd(int a = 0, int b = 0, int c = 0, int e = 0) { u = a, r = b, d = c, l = e; }
	bool operator < (const nd &p) const
		{
			return u == p.u ? (r == p.r ? (d == p.d ? l < p.l : d < p.d) : (r < p.r)) : (u < p.u) ;
		}
}; 
map<nd, int> mp; 
int ans; 

template < typename T >
inline T read()
{
	T x = 0, w = 1; char c = getchar();
	while(c < '0' || c > '9') { if(c == '-') w = -1; c = getchar(); }
	while(c >= '0' && c <= '9') x = x * 10 + c - '0', c = getchar();
	return x * w; 
}

int main()
{
	
	 
	n = read <int> ();
	for(int i = 1; i <= n; i++)
	{
		c[i][0] = read <int> (), c[i][1] = read <int> (), c[i][2] = read <int> (), c[i][3] = read <int> (); 
		for(int n1, n2, n3, n4, j = 0; j < 4; j++)
		{
			n1 = c[i][j], n2 = c[i][(j + 1) % 4], n3 = c[i][(j + 2) % 4], n4 = c[i][(j + 3) % 4]; 
			if(mp.find(nd(n1, n2, n3, n4)) == mp.end()) mp[nd(n1, n2, n3, n4)] = ++cnt; 
			sum[pos[j] = mp[nd(n1, n2, n3, n4)]]++; 
		}
		for(int j = 0; j < 4; j++) nxt[pos[j]] = pos[(j + 1) % 4]; 
	}
	int res; 
	for(int x, i = 1; i <= n; i++)
		for(int j = i + 1; j <= n; j++)
		{
			x = mp.find(nd(c[i][0], c[i][1], c[i][2], c[i][3])) != mp.end() ? mp[nd(c[i][0], c[i][1], c[i][2], c[i][3])] : 0; 
			for(int k = 0; k < 4; k++) sum[x]--, x = nxt[x]; 
			x = mp.find(nd(c[j][0], c[j][1], c[j][2], c[j][3])) != mp.end() ? mp[nd(c[j][0], c[j][1], c[j][2], c[j][3])] : 0; 
			for(int k = 0; k < 4; k++) sum[x]--, x = nxt[x]; 
			if(i != j)
				for(int k = 0; k < 4; k++)
				{
					res = 1; 
					for(int l = 0; l < 4; l++) u[l] = c[i][l], d[l] = c[j][(4 - l + k) % 4]; 
					for(int t, x, s = 0; s < 4; s++)
					{
						t = (s + 3) % 4; x = (mp.find(nd(u[s], u[t], d[t], d[s])) != mp.end() ? mp[nd(u[s], u[t], d[t], d[s])] : 0); 
						res = 1ll * res * (sum[x] >= 0 ? sum[x] : 0) % mod; 
						for(int l = 0; l < 4; l++) sum[x]--, x = nxt[x]; 
					}
					ans = (ans + res) % mod; 
					for(int x, t, s = 0; s < 4; s++)
					{
						t = (s + 3) % 4; x = mp.find(nd(u[s], u[t], d[t], d[s])) != mp.end() ? mp[nd(u[s], u[t], d[t], d[s])] : 0; 
						for(int l = 0; l < 4; l++) sum[x]++, x = nxt[x]; 
					}
				}
			x = mp.find(nd(c[i][0], c[i][1], c[i][2], c[i][3])) != mp.end() ? mp[nd(c[i][0], c[i][1], c[i][2], c[i][3])] : 0; 
			for(int k = 0; k < 4; k++) sum[x]++, x = nxt[x]; 
			x = mp.find(nd(c[j][0], c[j][1], c[j][2], c[j][3])) != mp.end() ? mp[nd(c[j][0], c[j][1], c[j][2], c[j][3])] : 0; 
			for(int k = 0; k < 4; k++) sum[x]++, x = nxt[x];
		}
	printf("%d\n", 1ll * ans * inv3 % mod); 
	return 0; 
}
