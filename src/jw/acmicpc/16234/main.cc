#include <stdio.h>
#include <vector>
#include <unordered_map>

int n, l, r;

int arr[51][51];

class Solver {
 public:
  class Processor {
   public:
    int edge[51][51][4]; // l, r, u, d
    int visited[51][51];
    int rem = n * n;
    int sum, n_mem;
    void dfs(int y, int x) {
      if (visited[y][x]) return;
      visited[y][x] = 1;
      sum += arr[y][x];
      n_mem++;

      if (edge[y][x][0]) 
        dfs(y, x - 1);
      if (edge[y][x][1]) 
        dfs(y, x + 1);
      if (edge[y][x][2]) 
        dfs(y - 1, x);
      if (edge[y][x][0]) 
        dfs(y + 1, x);
    }
    void modify(int y, int x) {}
    bool try_open(int y, int x, int dy, int dx) {
      int Y = y + dy;
      int X = x + dx;
      if (Y < 0 || Y >= n || X < 0 || X >= n) return false;
      int diff = arr[Y][X] - arr[y][x];
      if (diff < 0) diff*=-1;
      if (l <= diff && diff <= r) return true;
      return false;
    }
    void gate()  {
      for (int i = 0 ; i < n ; i++) {
        for (int j = 0 ; j < n ; j++) {
          if (try_open(i, j, 0, -1)) 
            edge[i][j][0] = 1;
          if (try_open(i, j, 0, 1)) 
            edge[i][j][1] = 1;
          if (try_open(i, j, -1, 0)) 
            edge[i][j][2] = 1;
          if (try_open(i, j, 1, 0)) 
            edge[i][j][3] = 1;
        }
      }
    }
    void process() {
      for (int i = 0 ; i < n ; i++) {
        for (int j = 0 ; j < n ; j++) {
          if (rem <= 0) return;
          if (visited[i][j]) continue;
          sum = n_mem = 0;
          dfs(i, j);
          modify(i, j);
        }
      }
    }
  };
  Solver() : cnt(0) {}
  ~Solver() {}
  int solve() {
    while(1) {
      Processor pc;
      pc.gate();
      pc.process();
      cnt++;
    }
    return cnt - 1;
  }
  int cnt;
};

int main () {
  scanf("%d %d %d", &n, &l, &r);
  for (int i = 0 ; i < n ; i++) {
    for (int j = 0 ; j < n ; i++) {
      int tmp;
      scanf("%d", &tmp);
      arr[i][j] = tmp;
    }
  }

  Solver sv;
  printf("%d\n", sv.solve());

  return 0;
}
