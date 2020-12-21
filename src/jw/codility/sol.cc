#include <vector>
#include <unordered_map>
#include <iostream>

using namespace std;

int n;
unordered_map<int, int> cache{};

void build(vector<int> &fib) {
  while (1) {
    int e = fib.size() - 1;
    if (fib[e] >= 2*n + 1) return;
    fib.push_back(fib[e] + fib[e - 1]);
  }
}

int getLastFibIdx(vector<int> &fib, int limit) {
  for (int i = 0 ; ; i++) {
    if (fib[i] > limit) return i;
  }
  return -1;
}

int dp(vector<int> &A, vector<int> &fib, int cur) {
  if (cache.find(cur) != cache.end()) return cache[cur];
  int ret = -1, e, cand;
  bool flag = false;
  if (cur == n) {
    ret = 0;
    goto fin;
  }

  else if (cur == -1) flag = true;

  else if (cur > n) {
    ret = -1;
    goto fin;
  }

  else if (!flag) {
    if (A[cur] == 0) {
      ret = -1;
      goto fin;
    }
  }

  e = getLastFibIdx(fib, n - cur);

  for (int i = 0 ; i <= e ; i++) {
    cand = dp(A, fib, cur + fib[i]);
    if (cand == -1) continue;
    else if (ret == -1) ret = cand + 1;
    else if (cand + 1 < ret) ret = cand + 1;
  }

fin:
  cache[cur] = ret;
  return ret;
}

int solution(vector<int> &A) {
  n = A.size();
  if (n <= 2) return 1;
  A.push_back(1);

  vector<int> fib{};

  fib.push_back(1);
  fib.push_back(1);

  build(fib);

  return dp(A, fib, -1);
}

