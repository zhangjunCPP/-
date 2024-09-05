#include <bits/stdc++.h> 
using namespace std;
int n , id[550000] , it = 1;
long long ans = -1 , p[550000];
set< int > s;
set< int >::iterator sit;
bool cmp( int x , int y )
{
	return p[x + 1] - p[x] > p[y + 1] - p[y];
}
int main()
{
//	freopen("contest.in" , "r" , stdin);
//	freopen("contest.out" , "w" , stdout);
	scanf("%d" , &n);
	for(int i = 1 ; i <= n ; i++ ) scanf("%lld" , &p[i]);
	sort(p + 1 , p + n + 1); 
//	for(int i = 1 ; i <= n ; i++ ) cerr << p[i] << ' '; cerr << endl;
	for(int i = 1 ; i < n ; i++ ) id[i] = i , s.insert(i);
	sort(id + 1 , id + n , cmp);
	for(int l = n - 2 ; l >= 5 ; l-- )
	{
		while(p[id[it] + 1] - p[id[it]] >= p[l] && it < n)
		{
			s.erase(id[it]);
			it++;
		}
		if(s.empty()) break;
		long long sum = p[l - 1] + p[l - 2] + p[l - 3] + p[l - 4];
		int rp = lower_bound(p + 1 , p + n + 1 , sum - p[l]) - p - 1;
		sit = s.upper_bound(rp);
		if(sit == s.begin()) continue;
		int r = *(--sit);
//		cerr << rp << ' ' << r << endl;
//		cerr << l << ' ' << r << endl;
		if(l >= r) continue;
		int s = lower_bound(p + 1 , p + n + 1 , p[l] + p[r]) - p - 1;
		ans = max(ans , sum + p[r] + p[l] + p[s]);
//		cerr << l << ' ' << sum << ' ' << p[l] + p[r] << ' ' << p[s] << endl;
	}
	printf("%lld" , ans);
	return 0;
}