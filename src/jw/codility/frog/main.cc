// you can use includes, for example:
#include <vector>
#include <iostream>
// you can write to stdout for debugging purposes, e.g.
// cout << "this is a debug message" << endl;
using namespace std;

int solution(int X, vector<int> &A) {
    // write your code in C++14 (g++ 6.2.0)
    vector<int> dict(X, 0);
		int x = X;
    for (int i = 0 ; i < (int)A.size() ; i++) {
        int pos = A[i];
        if (pos <= x) {
            if (dict[pos] == 0) {
                dict[pos] = 1;
                X--;
            }
        }
        if (X <= 0) return i;
    }

    return -1;
}

int main() {
	vector<int> v {1, 3, 1, 4, 2, 3, 5, 4};
	cout << solution(2, v) << endl;
	return 0;
}
