#include <vector>
#include <stdio.h>
#include <unordered_map>

#define if_random 1
using namespace std;

unsigned int n, w;
vector<unsigned int> weight;
vector<unsigned int> value;
unordered_map<unsigned long long int, unsigned int> cache{};

unsigned int solve(unsigned int idx, unsigned int rem) {
  printf("%d\n", idx);
  unsigned long long int key;
  key = rem;
  key = key << (sizeof(unsigned int) * 8);
  key += idx;
  if (cache.find(key) != cache.end()) return cache[key];

  unsigned int ret, ret1, ret2, cur;
  if (idx >= n || rem < 0) {
    ret = 0;
    goto end;
  }
  
  ret1 = solve(idx + 1, rem);
  ret2 = solve(idx + 1, rem - weight[idx]);

  cur = value[idx];
  if (rem < weight[idx]) ret2 = cur = 0;

  if (ret1 > ret2 + cur) {
    ret = ret1;
    goto end;
  }
  else {
    ret = ret2 + cur;
    goto end;
  }
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
  w = 100000;
  weight.empty();
  for (int i = 0 ; i < n ; i++)
    weight.push_back(1);
#endif
  printf("%d\n", solve(0, w));
  return 0;
}

