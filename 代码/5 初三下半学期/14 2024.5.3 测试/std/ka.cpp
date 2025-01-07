#include <cstdio>
#include <cstring>
#include <cmath>
#include <iostream>
#include <unordered_map>
#define F(i,a,b) for(int (i) = (a); (i) <= (b); ++(i))
using namespace std;

int useless, t, n;
struct player {
	string name;
	int card[7], num[17], col[7], sum, niu, tieban, maxx, bomb, idd;
	long long score;
	/*
		card：记每个牌的点数
		num：记每种点数出现在的牌的数量
		col：记每张牌的花色 
		sum：记所有牌点数的和 
		niu：记牌的类型
			niu=0-10 无牛、牛一至九、牛牛 
		tieban：记录铁板的点数，如果没有铁板则记为0。 
		maxx：记录所有牌中最大的点数
		bomb：记录炸弹的点数，如果没有炸弹则记为0. 
	*/
}a[100007];
unordered_map<string, int> hashmap;

inline void cle(int id) {
	memset(a[id].card, 0, sizeof(a[id].card));
	memset(a[id].num, 0, sizeof(a[id].num));
	memset(a[id].col, 0, sizeof(a[id].col));
	a[id].sum = a[id].niu = a[id].tieban = a[id].maxx = a[id].bomb = a[id].idd = 0;
}
inline void premission(int t3) {
	F(i, 1, 5) {
		string cards;
		cin >> cards;
		if(cards[1] == '1' && cards[2] == '0')	a[t3].card[i] = 10;
		else if(cards[1] == 'A')	a[t3].card[i] = 1;
		else	a[t3].card[i] = cards[1] - '0';
		a[t3].sum += a[t3].card[i];
		a[t3].num[a[t3].card[i]]++;
		if(cards[0] == 'a')	a[t3].col[i] = 4;
		if(cards[0] == 'b')	a[t3].col[i] = 3;
		if(cards[0] == 'c')	a[t3].col[i] = 2;
		if(cards[0] == 'd')	a[t3].col[i] = 1;
		if(a[t3].card[i] > a[t3].maxx) {
			a[t3].maxx = a[t3].card[i];
			a[t3].idd = a[t3].col[i]; 
		} else if(a[t3].card[i] == a[t3].maxx && a[t3].col[i] > a[t3].idd)
			a[t3].idd = a[t3].col[i];
	}
	F(i, 1, 5) {
		if(a[t3].num[a[t3].card[i]] == 4) {
			a[t3].bomb = a[t3].card[i];
			break;
		}
		if(a[t3].num[a[t3].card[i]] == 3) {
			a[t3].tieban = a[t3].card[i];
			if(!((a[t3].sum - a[t3].card[i] * 3) % 10))	a[t3].niu = 10;
			else	a[t3].niu = (a[t3].sum - a[t3].card[i] * 3) % 10;
		}
		F(j, 1, 5) {
			if(i == j)	continue;
			if((a[t3].card[i] + a[t3].card[j]) % 10 == a[t3].sum % 10) {
				int p = a[t3].niu;
				if(!((a[t3].card[i] + a[t3].card[j]) % 10))	a[t3].niu = 10;
				else	a[t3].niu = max(a[t3].niu, (a[t3].card[i] + a[t3].card[j]) % 10);
				if(a[t3].niu > p)	a[t3].tieban = 0;
			}
		}
	}
}
inline void pk(int id1, int id2) {
	int difen = 10, sf = 0;
	if(a[id1].bomb > a[id2].bomb) {
		sf = 1;
		difen *= 10;
	} else if(a[id1].bomb < a[id2].bomb) {
		sf = 2;
		difen *= 10;
	} else if(!a[id1].bomb && !a[id2].bomb) {
		if(a[id1].niu > a[id2].niu) {
			if(a[id1].niu == 10)
				difen *= 3;
			else if(a[id1].niu >= 7 && a[id1].niu <= 9)
				difen *= 2;
			else
				difen *= 1;
			if(a[id1].tieban)	difen *= 2;
			sf = 1;
		} else if(a[id1].niu < a[id2].niu) {
			if(a[id2].niu == 10)
				difen *= 3;
			else if(a[id2].niu >= 7 && a[id2].niu <= 9)
				difen *= 2;
			else
				difen *= 1;
			if(a[id2].tieban)	difen *= 2;
			sf = 2;
		} else if(a[id1].niu == a[id2].niu && a[id1].niu) {
			if(a[id1].tieban > a[id2].tieban) {
				if(a[id1].niu == 10)	difen *= 3;
				else if(a[id1].niu >= 7 && a[id1].niu <= 9)	difen *= 2;
				else	difen *= 1;
				difen *= 2;
				sf = 1;
			} else if(a[id1].tieban < a[id2].tieban){
				if(a[id2].niu == 10)	difen *= 3;
				else if(a[id2].niu >= 7 && a[id2].niu <= 9)	difen *= 2;
				else	difen *= 1;
				difen *= 2;
				sf = 2;
			} else if(a[id1].tieban == a[id2].tieban) {
				if(a[id1].maxx > a[id2].maxx)
					sf = 1;
				else if(a[id1].maxx < a[id2].maxx)
					sf = 2;
				if(sf == 1) {
					if(a[id1].niu == 10)	difen *= 3;
					else if(a[id1].niu >= 7 && a[id1].niu <= 9)	difen *= 2;
					else 	difen *= 1;
					if(a[id1].tieban)	difen *= 2;
				} else if(sf == 2) {
					if(a[id2].niu == 10)	difen *= 3;
					else if(a[id2].niu >= 7 && a[id2].niu <= 9)	difen *= 2;
					else	difen *= 1;
					if(a[id2].tieban)	difen *= 2;
				}
				else {
					if(a[id1].idd > a[id2].idd) {
						sf = 1;
						if(a[id1].niu == 10)	difen *= 3;
						else if(a[id1].niu >= 7 && a[id1].niu <= 9)	difen *= 2;
						else	difen *= 1;
						if(a[id1].tieban)	difen *= 2;
					}
					else if(a[id1].idd < a[id2].idd) {
						sf = 2;
						if(a[id2].niu == 10)	difen *= 3;
						else if(a[id2].niu >= 7 && a[id2].niu <= 9)	difen *= 2;
						else	difen *= 1;
						if(a[id2].tieban)	difen *= 2;
					}
				}
			}
		} else if(!a[id1].niu && !a[id2].niu) {
			if(a[id1].maxx > a[id2].maxx)
				sf = 1;
			else if(a[id1].maxx < a[id2].maxx)
				sf = 2;
			else {
				if(a[id1].idd > a[id2].idd)
					sf = 1;
				else if(a[id1].idd < a[id2].idd)
					sf = 2;
			}
		}
	} 
	if(sf == 1)	a[id1].score += difen, a[id2].score -= difen;
	else	a[id1].score -= difen, a[id2].score += difen;
}

int main() {
	freopen("ka.in","r",stdin);
	freopen("ka.out","w",stdout);
	scanf("%d%d%d", &useless, &t, &n);
	F(i, 1, n) {
		cin >> a[i].name;
		hashmap[a[i].name] = i;
	}
	while(t--) {
		string s1, s2, s3;
		int t1, t2, t3;
		cin >> s1; t1 = hashmap[s1];
		premission(t1);
		cin >> s2; t2 = hashmap[s2];
		premission(t2);
		cin >> s3; t3 = hashmap[s3];
		premission(t3);
		pk(t1, t2);
		pk(t1, t3);
		pk(t2, t3);
		cle(t1), cle(t2), cle(t3);
	}
	F(i, 1, n) {
		cout << a[i].name;
		printf(" %lld\n", a[i].score);
	}
	return 0;
}
