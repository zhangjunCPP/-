#include <bits/stdc++.h> 
using namespace std;
int n , m , x , y , vis[220000] , siz[220000];
int fst[220000] , nex[440000] , v[440000] , tot;
long double dis[220000] , minn[220000] , sum[220000];
long double f14[220000] , f34 , f32 = (long double)3 / 2;
struct item
{
	long double num; int id;
	bool operator < ( const item &x ) const
	{
		return num > x.num;
	}
};
priority_queue< item > q;
void add( int a , int b )
{
	nex[++tot] = fst[a]; fst[a] = tot;
	v[tot] = b;
}
void dij()
{
	for(int i = 1 ; i < n ; i++ ) dis[i] = 1e18;
	memset(vis , 0 , sizeof(vis)); memset(siz , 0 , sizeof(siz)); 
	dis[n] = 0; q.push((item){dis[n] , n});
	while(!q.empty())
	{
		int u = q.top().id; q.pop();
		if(vis[u]) continue;
		vis[u] = 1;
//		cerr << u << ' ' << dis[u] << endl;
		for(int i = fst[u] ; i ; i = nex[i] )
		{
//			cerr << dis[v[i]] << endl;
			if(dis[u] < dis[v[i]])
			{
//				cerr << u << ' ' << v[i] << endl;
				if(!siz[v[i]]) sum[v[i]] = f34 * dis[u] + 1 , minn[v[i]] = dis[u];
				else sum[v[i]] += f14[siz[v[i]]] * (f34 * dis[u] + 1);
				siz[v[i]]++;
//				cerr << u << ' ' << v[i] << ' ' << siz[v[i]] << ' '
//				 << (f34 * dis[v[i]] + 1) << ' ' << f34 * f14[1] * (minn[v[i]] + 2) << endl;
				if(dis[v[i]] > sum[v[i]] + f14[siz[v[i]]] * (minn[v[i]] + 2)) 
				{
					dis[v[i]] = sum[v[i]] + f14[siz[v[i]]] * (minn[v[i]] + 2);
					q.push((item){dis[v[i]] , v[i]});
				}
			}
		}
	}
}
int main()
{
//	freopen("1.in" , "r" , stdin);
//	freopen("bridge.out" , "w" , stdout);
	f14[1] = (long double)1 / 4; f14[0] = 1; f34 = 1 - f14[1];
	for(int i = 2 ; i <= 200000 ; i++ ) f14[i] = f14[i - 1] * f14[1];
	scanf("%d%d" , &n , &m);
	for(int i = 1 ; i <= m ; i++ )
		scanf("%d%d" , &x , &y) , add(x , y) , add(y , x);
	dij();
	printf("%.12Lf" , dis[1]);
	return 0;
}
/*
*/