#include <bits/stdc++.h> 
using namespace std;
int n , m , len[110000] , ans[110000] , B = 330 , nex[110000];
int fail[110000] , son[26][110000] , num[110000] , p[110000] , las[110000] , tot;
char s[110000] , qqq[110000];
string t[110000];
vector< int > id[400];
queue< int > q;
int kmp( int n , int m )
{
	nex[0] = -1; int it = -1 , ans = 0;
	for(int i = 1 ; i < m ; i++ ) 
	{
		while(~it && qqq[it + 1] != qqq[i]) it = nex[it];
		if(qqq[it + 1] == qqq[i]) it++;
		nex[i] = it;
	}
	it = -1;
	for(int i = 0 ; i < n ; i++ )
	{
//		cerr << 11111 << endl;
		while(~it && qqq[it + 1] != s[i]) it = nex[it];
		if(qqq[it + 1] == s[i]) it++;
		if(it == m - 1)
		{
			ans++; it = -1;
		}
	}
	return ans;
}
void insert( int j )
{
	int u = 1;
	for(int i = 0 ; i < t[j].size() ; i++ )
	{
		if(!son[t[j][i] - 'a'][u]) 
		{
			son[t[j][i] - 'a'][u] = ++tot;
			for(int j = 0 ; j < 26 ; j++ ) son[j][tot] = 0;
		}
		u = son[t[j][i] - 'a'][u];
	}
	p[j] = u;
}
void getfail()
{
	q.push(1);
	while(!q.empty())
	{
		int u = q.front(); q.pop();
		for(int i = 0 ; i < 26 ; i++ )
		{
			if(son[i][u]) fail[son[i][u]] = son[i][fail[u]] , q.push(son[i][u]);
			else son[i][u] = son[i][fail[u]];
		}
	}
}
void solve( int len )
{
	int u = 1;
	for(int i = 0 ; i < n ; i++ )
	{
		u = son[s[i] - 'a'][u];
		if(i - las[u] >= len) num[u]++ , las[u] = i;
	}
}
int main()
{
//	freopen("language.in" , "r" , stdin);
//	freopen("language.out" , "w" , stdout);
	scanf("%s" , s); scanf("%d" , &m); n = strlen(s);
	for(int i = 1 ; i <= m ; i++ ) 
	{
		scanf("%s" , qqq); len[i] = strlen(qqq); t[i] = qqq;
		if(len[i] <= B) id[len[i]].push_back(i);
		else ans[i] = kmp(n , len[i]);
//		cerr << i << endl;
	}
	for(int i = 1 ; i <= B ; i++ )
	{
		memset(num , 0 , sizeof(num)); memset(p , 0 , sizeof(p)); 
		memset(las , -0x7f / 3 , sizeof(las));
		fail[1] = 0; 
		for(int j = 0 ; j < 26 ; j++ ) son[j][0] = 1 , son[j][1] = 0;
		tot = 1;
		for(auto j : id[i]) insert(j);
		getfail();
		solve(i); 
		for(auto j : id[i]) ans[j] = num[p[j]];
	}
	for(int i = 1 ; i <= m ; i++ ) printf("%d\n" , ans[i]);
	return 0;
}