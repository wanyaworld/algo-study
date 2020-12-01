#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <map>

using namespace std;

unsigned int N{}, M{};
vector<string> strs{};

void func(int x, int y){}
int main() {
	void (*fp)(int, int);
	fp = &func;
	fp(1, 2);
	string ret = "";
	scanf("%d %d", &N, &M);
	for (int i = 0 ; i < N ; i++) {
		string tmp;
		cin >> tmp;
		strs.push_back(tmp);
	}

	for (int i = 0 ; i < M ; i++) {
		map<char, unsigned int> dict{};
		vector<char> words = {'A', 'C', 'G', 'T'};
		for (auto it = words.begin() ; it != words.end() ; it++)
			dict[*it] = 0;

		for (int j = 0 ; j < N ; j++) {
			char c = strs[j][i];
			(dict[c])++;
		}
		unsigned int max{};
		char cand{};
		for (auto it = dict.begin() ; it != dict.end() ; it++) {
			if (it->first == 'A') {
				max = it->second;
				cand = it->first;
				break;
			}
		}
		for (auto it = dict.begin() ; it != dict.end() ; it++) {
			if (it->second > max) {
				max = it->second;
				cand = it->first;
			}
		}
		ret += cand;
	}	
	unsigned int dist{};
	for (int i = 0 ; i < N ; i++) {
		for (int j = 0 ; j < M ; j++) {
			if (strs[i][j] != ret[j]) dist++;
		}
	}
	cout << ret << endl;
	cout << dist << endl;
	return 0;
}
