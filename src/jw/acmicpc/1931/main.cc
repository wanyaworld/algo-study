#include <stdio.h>
#include <vector>
#include <tuple>
#include <algorithm>

using namespace std;

bool sortBySec(const tuple<int, int>& a, const tuple<int, int>& b) {
	return (get<1>(a) < get<1>(b));
}
bool sortByFir(const tuple<int, int>& a, const tuple<int, int>& b) {
	return (get<0>(a) < get<0>(b));
}

vector<tuple<int, int>> vec{};
vector<tuple<int, int>> use_vec{};
int last = 0;

#define if_ndebug 1
#include <unistd.h>
#include <time.h>

int main() {
	int N;
	int ret{};
#if if_ndebug
	scanf("%d", &N);
	for (int i = 0 ; i < N ; i++) {
		int a, b;
		scanf("%d %d", &a, &b);
		vec.push_back(tuple<int, int>(a, b));
	}
#else
	srand(time(NULL));
	N = 100000;
	for (int i = 0 ; i < N ; i++) {
		unsigned int a, b;
		a = rand(); b = rand();
		a = b =0;
		vec.push_back(tuple<int, int>(a, b));
	}
#endif	
	sort(vec.begin(), vec.end(), sortByFir);
	sort(vec.begin(), vec.end(), sortBySec);
	for (auto it = vec.begin() ; it != vec.end() ; it++) {
		if (get<0>(*it) >= last) {
			ret++;
			last = get<1>(*it);
		}
	}
	printf("%d\n", ret);
	return 0;
}
