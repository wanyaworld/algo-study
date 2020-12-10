#include <string>
#include <iostream>
#include <vector>
#include <cstring>
#include <unordered_map>

using namespace std;

class Solution {
	public:
		string str{};
		vector<string> vec{};
		int N;
		unordered_map<int, unsigned long long int> cache{};
		Solution() {
			for (char c = 'A' ; c <= 'Z' ; c++) {
				vec.push_back(to_string(c - 'A' + 1));
			}
		}
		vector<string> getStringsStartWith(string s) {
			vector<string> v;
			for (auto it = vec.begin() ; it != vec.end() ; it++) {
				if (!strncmp((char*)it->c_str(), (char*)s.c_str(), s.size()))
					v.push_back(*it);
			}
			return v;
		}
		unsigned long long int dfs(int idx) {
			if (idx >= N) return 0;
			if (idx == N - 1) {
				if (str[idx] >= '1' && str[idx] <= '9') return 1;
				return 0;
			}
			if (cache.find(idx) != cache.end()) return cache[idx];	
			unsigned long long int ret{};
			if (str[idx] != '0')
				ret += dfs(idx + 1);
			string tmp = str.substr(idx, 2);
			if (getStringsStartWith(tmp).size() >= 1 && str[idx + 2] != '0') {
				unsigned long long int sub = dfs(idx + 2);
				if (sub == 0 && idx == N - 2) sub = 1;
				ret += sub;
			}
			cache[idx] = ret;
			return ret;
		}
		unsigned long long int numDecodings(string s) {
			str = s;
			N = str.size();
			return dfs(0);
		}
};

int main() {
	Solution s;
	cout << s.numDecodings((string)"2101") << endl;
	return 0;
}
