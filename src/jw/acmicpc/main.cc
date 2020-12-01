#include <stdio.h>

int solve(int l, int p, int v) {
	int ret = 0;
	ret += (v/p) * l;
	int bonus = v % p;
	if (l < bonus) bonus = l;
	ret += bonus;
	return ret;
}
int main() {
	int n = 0;
	while (1) {
		int l, p, v;
		scanf("%d %d %d", &l, &p, &v);
		if (l == 0 && p == 0 && v == 0) break;
		printf("Case %d: %d\n", (++n), solve(l, p, v));
	}
	return 0;
}
