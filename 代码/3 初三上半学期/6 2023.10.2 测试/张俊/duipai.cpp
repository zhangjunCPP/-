#include<bits/stdc++.h>
using namespace std;
int main(){
	system("g++ data.cpp -std=c++14 -O2 -o data.exe");
	system("g++ b.cpp -std=c++14 -O2 -o b.exe");
	system("g++ my2.cpp -std=c++14 -O2 -o my2.exe");
	for(int i=1;i<=1000;i++) {
		cout<<i<<"\n";
		system("data.exe");
		system("b.exe");
		system("my2.exe");
		if(system("fc my2.out b.out")){
			puts("WA");
			return 0;
		}
	}
	puts("AC");
	system("start cmd");
}
