#include <vector>
#include <stdio.h>
using namespace std;

int n;

int dnc(vector<int> &A, int s, int e, float& avr) {
  if (s + 1 >= e) {
    avr = (float)(A[s] + A[s + 1]) / 2;
    return s;
  }
  
  int mid = (s + e) / 2;
  float l_val, r_val, val;
  int l_idx, r_idx, idx;

  l_idx = dnc(A, s, mid, l_val);
  r_idx = dnc(A, mid, e, r_val);
  //r_idx = dnc(A, mid + 1, e, r_val);

  if (l_val < r_val) {
    val = l_val;
    idx = l_idx;
  }

  else {
    val = r_val;
    idx = r_idx;
  }

  int i = mid, j = mid + 1;
  int sum = A[i] + A[j];
  int n_elem = j - i + 1;
  if ((float)sum / n_elem < val) {
    val = (float)sum / n_elem;
    idx = i;
  }

  while (1) {
    if (i <= s && j >= e) break;
    else if (j >= e || (i > s && A[i - 1] <= A[j + 1])) {
      i--;
      sum += A[i];
    }
    else if (i <= s || (j < e && A[i - 1] >= A[j + 1])) {
      j++;
      sum += A[j];
    }
    else printf("Exception!\n");
    
    n_elem++;

    if ((float)sum / n_elem < val) {
      val = (float)sum / n_elem;
      idx = i;
    }
  }

  avr = val;
  return idx;
}

  
int solution(vector<int> &A) {
  n = A.size();
  float sum{};
  return dnc(A, 0, n - 1, sum);
}

int main() {
  vector<int> v {10, 10, -1, 2, 4, -1, 2, -1};
  solution(v);
  return 0;
}
