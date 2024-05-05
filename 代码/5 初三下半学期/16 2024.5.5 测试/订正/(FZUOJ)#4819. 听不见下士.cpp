#include<bits/stdc++.h>
#define int long long
using namespace std;
double p[15];
signed main(){
	double pc;
	cin>>pc;
	double sum=1;
	for(int i=1;i<=10;i++)cin>>p[i],sum*=(1-p[i]);
	double no=0;
	//全都听得见
	no+=(1-pc)*sum;
	for(int i=1;i<=10;i++){
		//只有i听不见
		double tmp=1;
		for(int j=1;j<=10;j++)if(j!=i)tmp*=(1-p[j]);
		tmp*=p[i];
		no+=(1-pc)*tmp;
		for(int j=i+1;j<=10;j++){
			//只有i,j听不见
			tmp=1;
			for(int k=1;k<=10;k++)if(k!=i&&k!=j)tmp*=(1-p[k]);
			tmp*=p[i]*p[j];
			no+=(1-pc)*tmp;
		}
	}
	printf("%.10lf\n%.10lf",no,(1-no)*(1-no));
}
/*
T2
最开始题没读懂……
第一个数要求你输出对于单次，不被批评的概率no
第二个数要求你输出两次都被批评的概率，也就是(1-no)*(1-no)
不被批评当且仅当下士听得见，且最多两个学长听不见
因此，直接枚举哪两个听不见即可
*/