#include <vector>
#include <stdio.h>
#include <algorithm>

using namespace std;

vector<int> adj[100001];
int visited[100001];
int n{}, m{};

void mfs(int idx) {
  if (visited[idx]) return;
  visited[idx] = true;
  printf("%d ", idx);

  vector<int> cand{};
  for (int i = 0 ; i < adj[idx].size() ; i++) {
    int v = (adj[idx])[i];
    if (!visited[v]) {
      cand.push_back(v);
    }
  }

  while (1) {
    sort(cand.begin(), cand.end());
    cand.erase(unique(cand.begin(), cand.end()), cand.end());
    
    cand.erase(remove_if(cand.begin(), cand.end(), 
         [](const int &i) { return visited[i]; }),
       cand.end());
    
    if (cand.size() == 0) return;
    int dest{};

    if (cand.size() % 2)
      dest = cand.size() / 2;
    else
      dest = 0;

    mfs(cand[dest]);
    cand.erase(cand.begin() + dest);
  }
}

int main() {
  scanf("%d %d", &n, &m);
  for (int i = 0 ; i < m ; i++) {
    int y, x;
    scanf("%d %d", &y, &x);
    adj[y].push_back(x);
    adj[x].push_back(y);
  }
  mfs(1);
  return 0;
}
