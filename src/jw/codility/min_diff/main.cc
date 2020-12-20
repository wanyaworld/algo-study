#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;
// you can use includes, for example:
// #include <algorithm>

// you can write to stdout for debugging purposes, e.g.
// cout << "this is a debug message" << endl;

int sum(vector<int> &A, int s, int e) {
    int ret{};
    for (int i = s ; i <= e ; i++)
        ret += A[i];
    return ret;
}

int solution(vector<int> &A) {
    int p = 1;
    int n = A.size();
    int min{}, val{};
    for ( ; p <= n - 1 ; p++) {
        if(p == 1) {
            int l = sum(A, 0, p - 1);
            int r = sum(A, p, n - 1);
            val = l - r;
            min = l - r;
            if (min < 0) min *= -1;
            continue;
        }
        val += 2 * A[p - 1];
        int abs = val;
        if (abs < 0) abs *= -1;
        if (abs < min) min = abs;
    }
    return min;
}

int main() { 
	//vector<int> v {3, 1, 2, 4, 3};
	//vector<int> v {-1, -2, -3, -4, -5};
	vector<int> v {-2, -2};
	cout << solution(v) << endl;
	return 0;
}
