#include <iostream>
unsigned int N{};
char **data{};

void dfs(int y, int x, int len) {
  if (len == 0) return;
  if (len == 1) { std::cout << data[y][x]; return; }

  char tmp = data[y][x];
  bool flag = true;

  for (int i = y ; i < y + len ; i++) {
    for (int j = x ; j < x + len ; j++) {
      if (tmp != data[i][j]) {
        flag = false;
      }
    }
  }

  if (flag) {
    std::cout << tmp;
    return;
  }
  
  len /= 2;

  std::cout << "(";
  
  dfs(y, x, len);
  dfs(y, x + len, len);
  dfs(y + len, x, len);
  dfs(y + len, x + len, len);
  
  std::cout << ")";
}

int main() {
  std::cin >> N;
  data = new char*[N]();

  for (int i = 0 ; i < N ; i++)
    data[i] = new char[N]();
  
  for (int i = 0 ; i < N ; i++) {
    for (int j = 0 ; j < N ; j++) {
      std::cin >> data[i][j];
    }
  }

  dfs(0, 0, N);

  for (int i = 0 ; i < N ; i++) {
    delete[] data[i];
  }
  delete[] data;

  return 0;
} 
