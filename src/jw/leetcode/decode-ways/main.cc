#include <string>
#include <iostream>
#include <vector>
#include <cstring>

using namespace std;

class Solution {
public:
    string str{};
    vector<string> vec{};
    Solution() : cnt(0) {
        for (char c = 'A' ; c <= 'Z' ; c++) {
            vec.push_back(to_string(c - 'A' + 1));
        }
    }
    int cnt;
    vector<string> getStringsStartWith(string s) {
        vector<string> v;
        for (auto it = vec.begin() ; it != vec.end() ; it++) {
            if (!strncmp((char*)it->c_str(), (char*)s.c_str(), it->size()))
                v.push_back(*it);
        }
        return v;
    }
    void dfs(std::string str) {
        if(str.size() == 0) {
            cnt++;
            return;
        }
        vector<string> v = getStringsStartWith(str);
        for (auto it = v.begin() ; it != v.end() ; it++) {
            dfs(str.substr(it->size(), str.size() - 1));
        }
        return ;
    }
    int numDecodings(string s) {
        str = s;
        dfs(str);
        return cnt;
    }
};

int main() {
  Solution s;
  s.numDecodings((string)"111111111111111111111111111111");
  cout << s.cnt << endl;
	return 0;
}
