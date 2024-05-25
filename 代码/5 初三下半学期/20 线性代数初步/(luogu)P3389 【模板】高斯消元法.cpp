#include <bits/stdc++.h>

using namespace std;
const double eps=1e-8;
double a[1005][1005];

int main(){
	int n;
	cin>>n;
	for(int i=1;i<=n;i++)for(int j=1;j<=n+1;j++)cin>>a[i][j];
	for(int i=1;i<=n;i++){
		for(int j=i;j<=n;j++){
			if(fabs(a[j][i])>eps){
				swap(a[i],a[j]);
				break;
			}
		}
		for(int j=1;j<=n;j++){
			if(i==j) continue;
			double tmp=a[j][i]/a[i][i];
			for(int k=i;k<=n+1;k++)a[j][k]-=a[i][k]*tmp;
		}
	}
	bool flag=false;
	for(int i=1;i<=n;i++)if(fabs(a[i][i])<eps)flag=true;
	if(flag)puts("No Solution");
	else for(int i=1;i<=n;i++)printf("%.2lf\n",a[i][n+1]/a[i][i]);
	return 0;
}