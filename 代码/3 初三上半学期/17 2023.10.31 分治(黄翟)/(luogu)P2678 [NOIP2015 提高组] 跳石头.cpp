#include <bits/stdc++.h>
using namespace std;
long long  a[50005],L,N,M;
int check(int dis) {
	int cnt=0,start=0;                  //cnt���ƶ�ʯͷ�� startÿ���ƶ���ʼλ��(��һ�������0)
	for(int i=1; i<=N+1; i++) {			 //N+1��Ϊ�����յ�
		if(a[i]-start<dis) cnt++;	    //���뾡���ܳ�,С��ҪŲ��
		else start=a[i];			    //���ڼ���������,����������
	}
	if(cnt>M) return 0;
	else return 1;
}
int main() {
	cin>>L>>N>>M;
	for(int i=1; i<=N; i++) {
		cin>>a[i];
	}
	a[N+1]=L;							//�յ��ʯͷ
	long long l=0,r=L,ans;
	while(l<=r) {
		long long mid=(l+r)/2;
		if(check(mid)) {
			ans=mid;
			l=mid+1;
		} else r=mid-1;
	}
	cout<<ans;
	return 0;
}