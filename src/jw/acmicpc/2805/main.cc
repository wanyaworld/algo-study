#include <stdio.h>
#include <vector>
#include <algorithm>
#include <functional>

using namespace std;

unsigned int N{}, M{}, tmp{};
vector<unsigned int> trees{};

unsigned int cut(unsigned int height) {
	unsigned int ret{}, start = 0, end = N - 1;
	for (int i = start ; i <= end ; i++) {
		if (trees[i] >= height) ret += (trees[i] - height);
	}
	return ret;
}

unsigned int solve(unsigned s, unsigned int e) {
	unsigned int m = (s + e) / 2;
	if (e - s <= 1) {
		for (int i = trees[s - 1] ; ; i--) {
			if (cut(i) >= M) return i;
		}
	}
	
	unsigned int cut_res = cut(trees[m]);

	if (cut_res == M) return trees[m];

	else if (cut_res < M) return solve(m + 1, e);

	else return solve(s, m);
}

unsigned int solve2(int s, int e) {
	int m = (s+e)/2;
	if (s==e) {
		for (int i = trees[i] ; ; i--) {
			if (cut(i) >= M) return i;
		}
	}
	if (cut(trees[m]) == M) return trees[m];
	else if (cut(trees[m]) > M) return solve2(s, m);
	else return solve2(m + 1, e);
}

int main() {
	scanf("%d %d", &N, &M);
	for (int i = 0 ; i < N ; i++) {
		scanf("%d", &tmp);
		trees.push_back(tmp);
	}
	
	sort(trees.begin(), trees.end(), greater<unsigned int>());

	printf("%d\n", solve(0, N - 1));

	return 0;
}
