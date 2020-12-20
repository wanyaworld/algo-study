#include <vector>
#include <stdio.h>
#include <unordered_map>

#define if_random 1

using namespace std;

unsigned int n, w;
vector<unsigned int> weight;
vector<unsigned int> value;
unordered_map<unsigned long long int, unsigned int> cache{};

unsigned int max(unsigned int a, unsigned int b) {
  if (a > b) return a;
  return b;
}

unsigned int solve(unsigned int idx, unsigned int rem) {
  unsigned long long int key;
  key = rem;
  key = key << (sizeof(unsigned int) * 8);
  key += idx;
  if (cache.find(key) != cache.end()) {
		printf("%d %d\n", idx, rem); return cache[key]; }

  unsigned int ret, ret1, ret2, cur;
  if (idx >= n || rem < 0) {
    ret = 0;
    goto end;
  }
  
  ret = solve(idx + 1, rem);

  if (rem >= weight[idx])
    ret = max(ret, solve(idx + 1, rem - weight[idx]) + value[idx]);

end:
  cache[key] = ret;
  return ret;
}

int main() {
  scanf("%d %d", &n, &w);
  for (int i = 0 ; i < n ; i++) {
    unsigned int tmp;
    scanf("%d", &tmp);
    weight.push_back(tmp);
    scanf("%d", &tmp);
    value.push_back(tmp);
  }
#if if_random
  n = 100;
  w = 1000000;
  weight.empty();
  for (int i = 0 ; i < n ; i++)
    weight.push_back(1);
#endif
  printf("%d\n", solve(0, w));
  return 0;
}

