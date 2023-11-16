#include<bits/stdc++.h>
using namespace std;

int main(){
	system("g++ data.cpp -O2 -std=c++14 -o data");
	system("g++ cut.cpp -O2 -std=c++14 -o cut");
	system("g++ bf.cpp -O2 -std=c++14 -o bf");
	for(int i=1;i<=1000;i++) {
		system("data.exe");
		system("bf.exe");
		system("cut.exe");
		if(system("fc cut.out bf.out")) {
			puts("WA");
			system("start cmd");
			return 0;
		}
	}

	puts("AC");
	return 0;
}

