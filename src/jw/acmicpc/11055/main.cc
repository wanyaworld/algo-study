#include <vector>
#include <stdio.h>
#include <unordered_map>

using namespace std;

int n;
vector<int> nums{};
unordered_map<int, unsigned long long int> cache{};

unsigned long long int solve (int idx) { 
	if (cache.find(idx) != cache.end()) return cache[idx];
	if (idx >= n - 1) {
		cache[idx] = nums[idx];
		return nums[idx];
	}
	unsigned long long int ret = 0;
	for (int i = idx + 1 ; i < n ; i++) {
		unsigned long long int cand = solve(i);
		if (nums[idx] < nums[i]) cand += nums[idx];
		else {
			if (nums[idx] > cand) cand = nums[idx];
		}
		if (cand > ret) ret = cand;
	}
	cache[idx] = ret;
	return ret;
}

int main () {
	scanf("%d", &n);
	for (int i = 0 ; i < n ; i++) {
		int t;
		scanf("%d", &t);
		nums.push_back(t);
	}
	printf("%lld\n", solve(0));
	return 0;
}
