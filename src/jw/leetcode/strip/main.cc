// you can use includes, for example:
// #include <algorithm>
#include <unordered_map>
#include <vector>
// you can write to stdout for debugging purposes, e.g.
// cout << "this is a debug message" << endl;
using namespace std;

unordered_map<int, int> numSet{};

void add(int n) {
    if (numSet.find(n) == numSet.end()) numSet[n] = 1;
    else (numSet[n])++;
}
int solution(vector<int> &A, vector<int> &B) {
    // write your code in C++14 (g++ 6.2.0)
    for (unsigned int i = 0 ; i < A.size() ; i++) {
        int num = A[i];
        add(num);
        if (B[i] != num)
            add(num);
    }

    int ret{};
    for (auto it = numSet.begin() ; it != numSet.end() ; it++) {
        int cand = it->second;
        if (cand > ret) ret = cand;
    }

    return ret;
}

int main() {
	vector<int> A = {2, 3, 2, 3, 5};
	vector<int> B = {3, 4, 2, 4, 2};

	int ret = solution(A, B);
	return 0;
}
