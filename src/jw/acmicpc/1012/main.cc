#include <stdio.h>
#include <iostream>
#include <memory>

unsigned int T;

class Solver {
public:
  Solver() : found(0), worms(0), arr(nullptr) {}
  ~Solver() {
    for (int i = 0 ; i < N ; i++)
      delete[] arr[i];
    delete arr;
  }
  void solve();
  void dfs(bool is_root, int y, int x);
  unsigned int M, N, K;
  unsigned int found;
  unsigned int worms;
  char **arr;
};

void Solver::solve() {
  for (int i = 0 ; i < M ; i++) {
    for (int j = 0 ; j < N ; j++) {
      dfs(true, j, i);
    }
  }
  std::cout << worms << std::endl;
}

void Solver::dfs(bool is_root, int y, int x) {
  if (y >= N || x >= M || y < 0 || x < 0) return;
  if (found >= K) return;
  if (arr[y][x] == false) return;

  found++;
  arr[y][x] = false;

  if (is_root)
    worms++;

  dfs(false, y + 1, x);
  dfs(false, y, x - 1);
  dfs(false, y - 1, x);
  dfs(false, y, x + 1);
}

int main() {
  scanf("%d", &T);

  for (int i = 0 ; i < T ; i++) {
    class Solver sv;
    scanf("%d %d %d", &sv.M, &sv.N, &sv.K);
    sv.arr = new char*[sv.N]();
    for (int j = 0 ; j <  sv.N ; j++)
      sv.arr[j] = new char[sv.M]();
    for (int j = 0 ; j < sv.K ; j++) {
      int x, y;
      scanf("%d %d\n", &x, &y);
      sv.arr[y][x] = 1;
    }
    sv.solve();
  }
  return 0;
}
