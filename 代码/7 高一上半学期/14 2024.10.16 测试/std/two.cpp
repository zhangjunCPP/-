#include<bits/stdc++.h>
using namespace std;
int x[55],y[55],n,k,b[155],b2[155];
int b3[305],tot3,sum[305][305];
int s1[55][3],s2[55][3];
inline void solve(){
	scanf("%d%d",&n,&k);
	int ans=1;
	int tot=0,tot2=0,tot3=0;
	for(int i=1;i<=k;i++){
		scanf("%d%d",&x[i],&y[i]);
		b[++tot]=x[i];
		b2[++tot2]=y[i];
		b3[++tot3]=x[i];
		b3[++tot3]=y[i];
		if(x[i]>1) b3[++tot3]=x[i]-1;
		if(x[i]<n) b3[++tot3]=x[i]+1;
		if(y[i]>1) b3[++tot3]=y[i]-1;
		if(y[i]<n) b3[++tot3]=y[i]+1;
	}
	sort(b+1,b+tot+1);
	sort(b2+1,b2+tot2+1);
	sort(b3+1,b3+tot3+1);
	tot=unique(b+1,b+tot+1)-(b+1);
	tot2=unique(b2+1,b2+tot2+1)-(b2+1);
	tot3=unique(b3+1,b3+tot3+1)-(b3+1);
	for(int i=1;i<=tot3;i++){
		for(int j=1;j<=tot3;j++){
			sum[i][j]=0;
			for(int g=1;g<=k;g++){
				if(x[g]<=b3[i] && y[g]<=b3[j]){
					if((x[g]+y[g])%2) sum[i][j]-=2;
					else sum[i][j]+=2;
				}
			}
		}
	}
	for(int i=1;i<=tot;i++){
		s1[i][0]=lower_bound(b3+1,b3+tot3+1,b[i])-b3;
		if(b[i]>1) s1[i][1]=lower_bound(b3+1,b3+tot3+1,b[i]-1)-b3;
		if(b[i]<n) s1[i][2]=lower_bound(b3+1,b3+tot3+1,b[i]+1)-b3;
	}
	for(int i=1;i<=tot2;i++){
		s2[i][0]=lower_bound(b3+1,b3+tot3+1,b2[i])-b3;
		if(b2[i]>1) s2[i][1]=lower_bound(b3+1,b3+tot3+1,b2[i]-1)-b3;
		if(b2[i]<n) s2[i][2]=lower_bound(b3+1,b3+tot3+1,b2[i]+1)-b3;
	}
	for(int i1=1;i1<=tot;i1++){
		for(int i2=i1;i2<=tot;i2++){
			for(int i3=1;i3<=tot2;i3++){
				for(int i4=i3;i4<=tot2;i4++){
					for(int czc=0;czc<16;czc++){
						int xl=b[i1],xr=b[i2],yl=b2[i3],yr=b2[i4];
						// cerr<<i1<<" "<<i2<<" "<<i3<<" "<<i4<<endl;
						// cerr<<xl<<" "<<xr<<" "<<yl<<" "<<yr<<endl;
						if(czc&1) xl--;
						if((czc>>1)&1) xr++;
						if((czc>>2)&1) yl--;
						if((czc>>3)&1) yr++;
						if(xl<1 || xr>n || yl<1 || yr>n) continue;
						int xll,xrr,yll,yrr;
						if(czc&1) xll=s1[i1][1];
						else xll=s1[i1][0];

						if((czc>>1)&1) xrr=s1[i2][2];
						else xrr=s1[i2][0];

						if((czc>>2)&1) yll=s2[i3][1];
						else yll=s2[i3][0];

						if((czc>>3)&1) yrr=s2[i4][2];
						else yrr=s2[i4][0];
						// int xll=lower_bound(b3+1,b3+tot3+1,xl)-b3;
						// int xrr=lower_bound(b3+1,b3+tot3+1,xr)-b3;
						// int yll=lower_bound(b3+1,b3+tot3+1,yl)-b3;
						// int yrr=lower_bound(b3+1,b3+tot3+1,yr)-b3;
						//黑色 1 白色 -1
						int s=0;
						if((xr-xl+1)%2 && (yr-yl+1)%2){
							if((xl+yl)%2) s++;
							else s--;
						}
						s+=sum[xrr][yrr]+sum[xll-1][yll-1]-sum[xrr][yll-1]-sum[xll-1][yrr];
						// for(int i=1;i<=k;i++){
						//	 if(xl<=x[i] && x[i]<=xr && yl<=y[i] && y[i]<=yr){
						//		 if((x[i]+y[i])%2) s-=2;
						//		 else s+=2;
						//	 }
						// }
						ans=max(ans,abs(s));
					}
				}
			}
		}
	}
	printf("%d\n",ans);
}
int main(){
	int T;
	scanf("%d",&T);
	while(T--){
		solve();
	}
	return 0;
}