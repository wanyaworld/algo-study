#include <stdio.h>
#include <vector>
enum class Operator {Add, Sub, Mul, Div};
using namespace std;

vector<unsigned int> ops{0, 0, 0, 0};
vector<unsigned int> nums{};
int n;

long long int calc(long long int a, int b, Operator op) {
  if (op == Operator::Add) return a + b;
  else if (op == Operator::Sub) return a - b;
  else if (op == Operator::Mul) return a * b;
  else if (op == Operator::Div) return a / b;
  else { printf("exception\n"); return -1; }
}

void solve(int idx, long long int sum, long long int *min_arg, long long int *max_arg) {
  if (idx == n) {
    *min_arg = sum;
    *max_arg = sum;
    return ;
  }
  long long int min{}, max{};
  bool flag = false;
  for (int i = 0 ; i < 4 ; i++) {
    if (ops[i] == 0) continue;
    Operator op = (Operator)i;
    long long int cur = calc(sum, nums[idx], op);
    long long int cur_min{}, cur_max{};
    (ops[i])--;
    solve(idx + 1, cur, &cur_min, &cur_max);
    (ops[i])++;
    if (!flag) {
      min = cur_min;
      max = cur_max;
      flag = true;
    }
    else {
      if (cur_min < min) min = cur_min;
      if (cur_max > max) max = cur_max;
    }
  }
  *min_arg = min;
  *max_arg = max;
}

int main () {
  scanf("%d\n", &n);
  for (int i = 0 ; i < n ; i++) {
    int tmp;
    scanf("%d\n", &tmp);
    nums.push_back(tmp);
  }
  for (int i = 0 ; i < 4 ; i++) {
    int tmp;
    scanf("%d\n", &tmp);
    ops[i] = tmp;
  }

  long long int min = nums[0], max = nums[0];
  solve(1, nums[0], &min, &max);
  printf("%lld\n%lld\n", max, min);
  return 0;
}
