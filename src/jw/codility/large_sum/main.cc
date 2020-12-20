// you can use includes, for example:
// #include <algorithm>
#include <vector>
#include <algorithm>
// you can write to stdout for debugging purposes, e.g.
// cout << "this is a debug message" << endl;
using namespace std;
int n;

int min(int a, int b) {
    if (a < b) return a;
    return b;
}
int sigma(vector<int> &A, int s, int e) {
    if (s > e) return 0;
    int ret{};
    for (int i = s ; i <= e ; i++)
        ret += A[i];
    return ret;
}

int findZero(vector<int> &A, int s, int e) {
		if (s >= e) return s;
    int mid = (s + e) / 2;
    int l_sum = sigma(A, 0, mid);
    int r_sum = sigma(A, mid + 1, n - 1);
    if (l_sum < r_sum) return findZero(A, mid + 1, e);
    return findZero(A, s, mid);
}
int binSearch(vector<int> &A, int s, int e, int k) {
    if (k <= 0 || s >= e) return sigma(A, s, e);
    int mid = findZero(A, s, e);
    int l = binSearch(A, s, mid, k - 1);
    int r = binSearch(A, mid + 1, e, k - 1);
    return min(l, r);
}

int solution(int K, int M, vector<int> &A) {
    // write your code in C++14 (g++ 6.2.0)
		sort(A.begin(), A.end());	
    n = A.size();
    return binSearch(A, 0, n - 1, K);
}

int main() {
	vector<int> v {1, 2, 3, 4, 5, 6};
	solution(3, 6, v);
	return 0;
}
