#include <bits/stdc++.h>
using namespace std;
int main(){
	system("g++ jump_data.cpp -std=c++14 -o jump_data");
	system("g++ jump.cpp -std=c++14 -lm -O2 -static -o jump");
	system("g++ jump2.cpp -std=c++14 -lm -O2 -static -o jump2");
	for(int T=1;T<=100;T++){
		system("clear");
		cout<<T<<"\n";
		system("./jump_data");
		cout<<"jump1:\n";
		system("\\time -p ./jump");
		cout<<"\n\njump2:\n";
		system("\\time -p ./jump2");
		if(system("diff jump.out jump2.out -Z -s")){
			puts("WA");
			return 0;
		}
	}

}