#include <stdio.h>
#include <algorithm>
#include <bits/stdc++.h>

int N_COINS, total;
int cache[10001] = {};
int coins[100] = {};

int solve(int n) {
	if (n == 0) return 0;
	if (n < 0) return -1;
	if (cache[n]) return cache[n];
	int min = INT_MAX;
	for (int i = 0 ; i < N_COINS ; i++) {
		int tmp = solve(n - coins[i]) + 1;
		if (tmp == 0) continue;
		if (tmp < min) min = tmp;
	}
	if (min == INT_MAX) min = -1;
	cache[n] = min;
	return min;
}

int main() {
	scanf("%d %d", &N_COINS, &total);
	for (int i = 0 ; i < N_COINS ; i++)
		scanf("%d", &(coins[i]));
	//std::sort(coins, coins + N_COINS, std::greater<int>());
	std::sort(coins, coins + N_COINS);
	printf("%d\n", solve(total));
	return 0;
}

