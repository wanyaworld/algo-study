#include <iostream>
#include <memory.h>
#include <stdio.h>
#include <unordered_map>

using namespace std;

unsigned int N{}, cnt{};
char adv_mat[101][101];
unordered_map<int, bool> visited_node{};

bool is_adj(int i, int j) {
  if (adv_mat[i][j] || adv_mat[j][i]) return true;
  return false;
}

void dfs(int cur) {
  if (visited_node[cur] == true) return;
  visited_node[cur] = true;
  cnt++;

  for (int i = 1 ; i < 101 ; i++) {
    if (is_adj(i, cur))
      dfs(i);
  }
}


int main() {
  cin >> N;
  cin >> N;
  memset(adv_mat, 0, 101*101);
  for (int i = 0 ; i < N ; i++) {
    int y, x;
    cin >> y; cin >> x;
    adv_mat[y][x] = adv_mat[x][y] = 1;
  }

  dfs(1);
  printf("%d", cnt - 1);

  return 0;
}

