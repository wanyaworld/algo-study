// you can use includes, for example:
// #include <algorithm>
#include <algorithm>
#include <vector>
// you can write to stdout for debugging purposes, e.g.
// cout << "this is a debug message" << endl;

using namespace std;

int n;

int min(int a, int b) {
    if (a < b) return a;
    return b;
}
int sigma(vector<int> &A, int s, int e) {
    int ret{};
    for (int i = s ; i <= e ; i++)
        ret += A[i];
    return ret;
}

int binSearch(vector<int> &A, int s, int e) {
    if (s >= e) return s;
    int mid = (s + e) / 2;
    int l_sum = sigma(A, s, mid);
    int r_sum = sigma(A, mid + 1, e);
    if (l_sum < r_sum) return binSearch(A, mid + 1, e);
    return binSearch(A, s, mid);
}
int dnc(vector<int> &A, int s, int e) {
    if( s >= e ) {
        if (A[s] < 0) return -1 * A[s];
        else return A[s];
    }
    int mid = binSearch(A, s, e);
		if (mid == e) mid = e - 1;
    int l_sum = sigma(A, s, mid);
    int r_sum = sigma(A, mid + 1, e);
    int ret = l_sum - r_sum;
    if (ret < 0) ret *= -1;
    int l = dnc(A, s, mid);
    int r = dnc(A, mid + 1, e);
    int cand = l - r;
		if (cand < 0) cand *= -1;
    ret = min(ret, cand);
    return ret;

}
int solution(vector<int> &A) {
    // write your code in C++14 (g++ 6.2.0)
    n = A.size();
    for (auto it = A.begin() ; it != A.end() ; it++) {
        if (*it < 0) (*it) *= -1;
    }
    sort(A.begin(), A.end());
    return dnc(A, 0, n - 1);
}

int main() {
	vector<int> v{ 1, 10 };
	solution(v);
	return 0;
}

