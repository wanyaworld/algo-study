// you can use includes, for example:
// #include <algorithm>
#include <unordered_map>
#include <vector>
using namespace std;
// you can write to stdout for debugging purposes, e.g.
// cout << "this is a debug message" << endl;

int solution(vector<int> &A) {
    // write your code in C++14 (g++ 6.2.0)
    unordered_map<int, int> dict{};
    for (auto it = A.begin() ; it != A.end() ; it++) {
        if (dict.find(*it) == dict.end()) dict[*it] = 0;
        else (dict[*it])++;
    }
    for (int i = 0 ; i < (int)A.size() ; i++) {
        if (dict[i + 1] != 1) return 0;
    }
    return 1;
}

int main() {
	vector<int> v {4, 1, 3, 2};
	solution(v);
	return 0;
}
