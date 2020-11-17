#include <stdio.h>
#include <algorithm>
#include <bits/stdc++.h>

int N_COINS, total;
int cache[10001][100] = {};
int coins[100] = {};

int solve(int remaining, int coin_idx) {
	int old_rem = remaining;
	int ret;
	unsigned int total_min = -1;
	int used = 0;

	if (cache[remaining][coin_idx]) return cache[remaining][coin_idx];
	if (coin_idx == N_COINS - 1) {
		if (remaining % coins[coin_idx] == 0)
			ret = remaining / coins[coin_idx];
		else
			ret = -1;
		
		goto term;
	}
	while (1) {
		ret = solve(remaining, coin_idx + 1);
		if ((unsigned int)ret + used < total_min && ret != -1) {
			total_min = ret + used;
		}
		remaining -= coins[coin_idx];
		used++;
		if (remaining < 0) break;
	}

	ret = total_min;
term:
	cache[old_rem][coin_idx] = ret;
	return ret;

}

int main() {
	scanf("%d %d", &N_COINS, &total);
	for (int i = 0 ; i < N_COINS ; i++)
		scanf("%d", &(coins[i]));
	std::sort(coins, coins + N_COINS, std::greater<int>());
	printf("%d\n", solve(total, 0));
	return 0;
}

