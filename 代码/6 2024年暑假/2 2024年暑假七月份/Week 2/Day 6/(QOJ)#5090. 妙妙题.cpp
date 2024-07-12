#include "tmp.h"
#include<bits/stdc++.h>
using namespace std;
const int M=1e5+10;
const double pi=acos(-1),eps=1e-6;
double Cos[M],Sin[M];
int n;
void init (int N, bool Type, int p) {
	n=N;
	for(int i=1;i<N;i++) {
		Cos[i]=cos(2*pi*i/N);
		Sin[i]=sin(2*pi*i/N);
	}
}
bool guess (unsigned long long A, int x) {
	double sinn=0,coss=0;
	bool sum=false;
	for(unsigned long long i=1;(int)i<n;i++) {
		if((A>>(i-1))&1ull) {
			coss+=Cos[i];
			sinn+=Sin[i];
			sum^=1;
		}
	}
	if(fabs(sinn)<eps)return fabs(coss)>=eps;
	return sum^(sinn>0);
}
