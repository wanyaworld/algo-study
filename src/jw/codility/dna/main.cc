// you can use includes, for example:
#include <algorithm>
#include <vector>
#include <string>
#include <iostream>
#include <tuple>
#include <unordered_map>

using namespace std;

// you can write to stdout for debugging purposes, e.g.
// cout << "this is a debug message" << endl;
/*
func(a, b) = min(sigma(func(x, y))) 
*/
int n;
vector<int> dna(100000);
unordered_map<unsigned long long int, int> cache{};

unsigned long long int getKey(int s, int e) {
	unsigned long long int ret = s;
	ret = (ret << 31);
	ret += e;
	return ret;
}
int min(int a, int b) {
	if (a < b) return a;
	else return b;
}

class SegTree {
public:
	int val;
	int s, e;
	SegTree *l, *r;
	void build(int start, int end);
	int get(int start, int end);
};

void SegTree::build(int start, int end) {
	if (start >= end) {
		val = dna[start];
	}
	else {
		int mid = (start + end) / 2;
		l = new SegTree();
		r = new SegTree();
		l->build(start, mid);
		r->build(mid + 1, end);
		val = min(l->val, r->val);
	}
	s = start;
	e = end;
}
 
int SegTree::get(int start, int end) {
	unsigned long long int key = getKey(start, end);
	if (cache.find(key) != cache.end()) return cache[key];

	int sub_s, sub_e;
	int ret = -1;

	if (start >= end) {
		ret = dna[start];
		goto fin;
	}

	if (start <= l->e) {
		sub_s = start;
		sub_e = end;
		if (sub_e > l->e) sub_e = l->e;
		ret = l->get(sub_s, sub_e);
	}

	if (end >= r->s) {
		sub_s = start;
		sub_e = end;
		if (sub_s < r->s) sub_s = r->s;
		int tmp;
		tmp = r->get(sub_s, sub_e);
		if (ret == -1) ret = tmp;
		else if (tmp != -1) {
			if (tmp < ret)
				ret = tmp;
		}
	}

fin:
	cache[key] = ret;
	return ret;
}
	
int valFromDna(int dna) {
	switch (dna) {
		case ('A'):
			return 1;
		case ('C'):
			return 2;	
		case ('G'):
			return 3;
		case ('T'):
			return 4;	
		default:
			return -1;
	}
	return -1;
}

vector<int> solution(string &S, vector<int> &P, vector<int> &Q) {
    // write your code in C++14 (g++ 6.2.0)
	vector<int> v{};
	for (unsigned int i = 0 ; i < S.size() ; i++) {
		dna[i] = valFromDna(S[i]);
	}
	n = S.size();
	SegTree st;
	st.build(0, n - 1);
	for (int i = 0 ; i < P.size() ; i++) 
		v.push_back(st.get(P[i], Q[i]));
	return v;
	
}

int main() {
	string s = {"ACGT"};
	vector<int> p{0, 1, 0};
	vector<int> q{1, 2, 3};
	vector<int> ans = solution(s, p, q);
	for (auto it = ans.begin() ; it != ans.end() ; it++)
		cout << *it << endl;	
	return 0;
}

