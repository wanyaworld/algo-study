#include <memory>
#include <stdio.h>
#include <iostream>
#include <tuple>
#include <map>
#include <time.h>
#include <unistd.h>

using namespace std;

#define if_debug 0
#define if_random_input 0
#define if_max_depth_check 1

class Solver {
  public:
    Solver() : cheez(0), epoch(0) {}
    int N, M;
    int data[100][100];
    int sur[100][100];
    int cheez;
    int epoch;
    int solve();
    bool dfs(int y, int x, map<tuple<int, int>, bool> &visited);
    bool dfs_2(int depth, int y, int x, map<tuple<int, int>, bool> &visited);
    bool dfs_2_debug(int *max_depth, int depth, int y, int x, map<tuple<int, int>, bool> &visited);
    void update_sur();
    bool can_melt(int y, int x);
    void melt();
};

bool Solver::dfs(int y, int x, map<tuple<int, int>, bool> &visited){
  if (y < 0 || x < 0 || y >= N || x >= M) return false;
  if (data[y][x]) return true;
  if (y <= 0 || x <= 0 || y >= N - 1 || x >= M - 1) return false;
  if (visited.find(tuple<int, int>(y, x)) != visited.end()) return true;
  visited[tuple<int, int>(y, x)] = true;

  int y_disp[] = {-1, 0, 1};
  int x_disp[] = {-1, 0, 1};

  for (int *dy = &y_disp[0] ; dy < &y_disp[2] + 1 ; dy++) {
    for (int *dx = &x_disp[0] ; dx < &x_disp[2] + 1 ; dx++) {
      if (*dy + *dx != 1 && *dy + *dx != -1) continue;
      if (dfs(y + *dy , x + *dx, visited) == false) return false;
    }
  }
  return true;
}

bool Solver::dfs_2(int depth, int y, int x, map<tuple<int, int>, bool> &visited){
  if (y < 0 || x < 0 || y >= N || x >= M) {
    if (depth > 0 ) return false;
  }
  if (data[y][x]) return true;
  if (visited.find(tuple<int, int>(y, x)) != visited.end()) return true;
  visited[tuple<int, int>(y, x)] = true;

  int y_disp[] = {-1, 0, 1};
  int x_disp[] = {-1, 0, 1};

  for (int *dy = &y_disp[0] ; dy < &y_disp[2] + 1 ; dy++) {
    for (int *dx = &x_disp[0] ; dx < &x_disp[2] + 1 ; dx++) {
      if (*dy + *dx != 1 && *dy + *dx != -1) continue;
      dfs_2(depth + 1, y + *dy , x + *dx, visited);
    }
  }
  return true;
}

bool Solver::dfs_2_debug(int *max_depth, int depth, int y, int x, map<tuple<int, int>, bool> &visited){
  if (depth > *max_depth) *max_depth = depth;
  if (y < 0 || x < 0 || y >= N || x >= M) {
    if (depth > 0 ) return false;
  }
  if (data[y][x]) return true;
  if (visited.find(tuple<int, int>(y, x)) != visited.end()) return true;
  visited[tuple<int, int>(y, x)] = true;

  int y_disp[] = {-1, 0, 1};
  int x_disp[] = {-1, 0, 1};

  for (int *dy = &y_disp[0] ; dy < &y_disp[2] + 1 ; dy++) {
    for (int *dx = &x_disp[0] ; dx < &x_disp[2] + 1 ; dx++) {
      if (*dy + *dx != 1 && *dy + *dx != -1) continue;
      dfs_2_debug(max_depth, depth + 1, y + *dy , x + *dx, visited);
    }
  }
  return true;
}

void Solver::update_sur() {
  for (int i = 0 ; i < N ; i++) {
    for (int j = 0 ; j < M ; j++) {
      sur[i][j] = 0;
    }
  }

  for (int i = 0 ; i < N ; i++) {
    for (int j = 0 ; j < M ; j++) {
      map<tuple<int, int>, bool> visited;
      if (sur[i][j]) continue;
      if (dfs(i, j, visited)) {
        for (auto it = visited.begin() ; it != visited.end() ; it++)
          sur[get<0>(it->first)][get<1>(it->first)] = 1;
      }
    }
  }
}

bool Solver::can_melt(int y, int x) { 
  int y_disp[] = {-1, 0, 1};
  int x_disp[] = {-1, 0, 1};
  int cnt = 0;

  for (int *dy = &y_disp[0] ; dy < &y_disp[2] + 1 ; dy++) {
    for (int *dx = &x_disp[0] ; dx < &x_disp[2] + 1 ; dx++) {
      if ( *dy + *dx != 1  && *dy + *dx != -1) continue;
      int new_y = y + *dy;
      int new_x = x + *dx;
      if (new_y < 0 || new_x < 0 || new_y >= N || new_x >= M) {
        continue;
      }
      if (!data[new_y][new_x] && !sur[new_y][new_x]) cnt++;
    }
  }
  if (cnt >= 2) return true;
  return false;
}

void Solver::melt() {
#if if_debug
  cout << "sur: ";
  for (int i = 0 ; i < N  ; i++) {
    for (int j = 0 ; j < M ; j++) {
      if (sur[i][j]) {
        cout << "[" << i << ", " << j << "] ";
      }
    }
  }
  cout << endl;
#endif
  map<tuple<int, int>, bool> visited_aggr;
  map<tuple<int, int>, bool> will_be_melt;
  for (int i = 0 ; i < N ; i++) {
    for (int j = 0 ; j < M ; j++) {
      if (!data[i][j]) continue; // no cheese
      if (can_melt(i, j)) {
        will_be_melt[tuple<int, int>(i, j)] = true;
        cheez--;
      }
    }
  }
#if if_debug
  cout << "being melted: ";
#endif
  for (auto it = will_be_melt.begin() ; it != will_be_melt.end() ; it++) {
    data[get<0>(it->first)][get<1>(it->first)] = 0;
#if if_debug
    cout << "[" << get<0>(it->first) << ", " << get<1>(it->first) << "] ";
#endif
  }
#if if_debug
  cout << endl;
#endif
  for (auto it = will_be_melt.begin() ; it != will_be_melt.end() ; it++) {
    int y = get<0>(it->first);
    int x = get<1>(it->first);
    map<tuple<int, int>, bool> visited;
#if if_max_depth_check
    int max_depth = 0;
    dfs_2_debug(&max_depth, 0, y, x, visited);
    printf("[%d, %d]: max_depth: %d\n", y, x, max_depth);
#elif
    dfs_2(0, y, x, visited);
#endif
    for (auto it = visited.begin() ; it != visited.end() ; it++){
      int y = get<0>(it->first);
      int x = get<1>(it->first);
      if(1) {
        //if(sur[y][x]) {
        visited_aggr[tuple<int, int>(y, x)] = true;
      }
      }
    }
#if if_debug
    cout << "sur removed: ";
#endif
    for (auto it = visited_aggr.begin() ; it != visited_aggr.end() ; it++) {
      sur[get<0>(it->first)][get<1>(it->first)] = 0;
#if if_debug
      cout << "[" << get<0>(it->first) << ", " << get<1>(it->first) << "] ";
#endif
    }
#if if_debug
    cout << endl;
#endif

  }


  int Solver::solve() {
    while (1) {
#if if_debug
      for (int i = 0 ; i < N ; i++) {
        for (int j = 0 ; j < M ; j++) {
          printf("%d", data[i][j]);
        }
        printf("\n");
      }
      printf("\n");
#endif
      if (epoch >= 50) return -1;
      if (cheez == 0) return epoch;
      melt();
      epoch++;
    }
  }

  Solver sv;

  int main() {
    scanf("%d %d", &sv.N, &sv.M);
    for (int i = 0 ; i < sv.N ; i++) {
      for (int j = 0 ; j < sv.M ; j++) {
        scanf("%d", &sv.data[i][j]);
        if (sv.data[i][j]) { 
          sv.cheez++;	
        }
      }
    }
#if if_random_input
    sv.N = sv.M = 100;
    //srand(time(NULL));
    for (int i = 0 ; i < sv.N ; i++) {
      for (int j = 0 ; j < sv.M ; j++) {
        unsigned int num = rand() % 10;
        if (num < 8) num = 0;
        else num = 1;
        sv.data[i][j] = num;
        if (sv.data[i][j]) { 
          sv.cheez++;	
        }
      }
    }
#endif
    sv.update_sur();
    cout << sv.solve() << endl;
    return 0;
  }
