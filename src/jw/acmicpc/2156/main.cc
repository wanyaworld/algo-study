#include <stdio.h>
#include <unordered_map>

int N;
int arr[10001];

using namespace std;

unordered_map<unsigned long long int, int> cache{}; // {pos, drunk} --> value

int solve(int cur_pos, int drunk) {
	if (cur_pos >= N) return 0;

  unsigned long long int key{};
  key += drunk;
  key += (cur_pos << sizeof(int));

  if (cache.find(key) != cache.end()) return cache[key];
	
  int cand1 = solve(cur_pos + 1, 0);
	int cand2;
	drunk++;
	if (drunk >=3) {
		drunk = 0;
		cand2 = 0;
	}
	else cand2 = solve(cur_pos + 1, drunk) + arr[cur_pos];

  int ret; 
	if (cand1 > cand2) ret = cand1;
	else ret = cand2;

  cache[key] = ret;

  return ret;
}

int main() {
	scanf("%d", &N);
	for (int i = 0 ; i < N ; i++)
		scanf("%d", &arr[i]);
  printf("%d\n", solve(0, 0));
	return 0;
}
