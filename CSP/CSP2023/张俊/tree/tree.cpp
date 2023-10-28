#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e5+10;
int a[N],b[N],c[N];
int u[N],v[N];
signed main(){
	freopen("tree.in","r",stdin);
	freopen("tree.out","w",stdout);
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	int n;
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i]>>b[i]>>c[i];
	}
	for(int i=1;i<n;i++) {
		cin>>u[i]>>v[i];
	}
	int ans=n;
	for(int i=1;i<=n;i++) {
		int tmp=0;
		int now=max(b[i]+i*c[i],1ll);
		while(now<a[i]) {
			tmp++;
			now+=max(b[i]+(i+tmp)*c[i],1ll);
		}
		ans=max(ans,i+tmp);
	}
	cout<<ans;
}

/*

���Ե��ʼ30����д�꣬һ�벻�

��Ŀȫ�������ˡ�

�о���ε�T1��ȫ��CCF�����ƣ�����100�֡�����ȥ�꣬T1��Ҫ���㷨��

������ġ����е����⡣

# T1

lock.cpp lock.in lock.out

�ܷ�����Ϊ $10^5$ ,ö��ÿһ��������ڱ����ж��Ƿ����

�жϷ�ʽ�ܼ򵥣��ҳ�������״̬��ͬ��λ����λ��Ϊ1��˵��ֻת����1�������򣬾Ϳ�ת���ķ����Ƿ���ͬ���ɡ�

ʱ�临�Ӷȣ� $O(10^5n)$

������Ƿ��ˣ�����Ϊ��n��������������ͬ�ķ�ʽ�������Ұ��Сʱ

# T2

���˿����ݷ�Χ��

�����ڶ����Ǿ���� $2\times 10^5$ ,�ɴ��Ʋ⣬��һ����ʱ�临�Ӷ�ӦΪ $nlogn$��

�������һ����ֱ�ӱ�� $2\times 10^6$ ��������� $nlogn$�����Եò�̫�����ˣ�����Ŀ����� $n\sqrt n$���ɴ˹�֮��������Ī���㷨��

���ҿ��˿����������Ī������ȷʵͦ����ġ�

��ô�������ڶ���Ӧ�ò��� $nlogn$ �����ܸ��ߡ�

# T3

��ģ�� or ���ݽṹ��

��Ŀ�����˰��졣

�е��ɡ�

�ò��ַ�

# T4

�ò��ַ֡�


*/ 
