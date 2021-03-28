class Solution {
public:
    const int N = 10;
    unordered_map<string, int> cache{};
    vector<string> findRepeatedDnaSequences(string s) {
        vector<string> ret{};
        for (auto it = s.begin() ; it + N <= s.end() ; it++) {
            string e(it, it + N);
            if (cache.find(e) != cache.end()) (cache[e])++;
            else cache[e] = 1;
        }
        for (auto it = cache.begin() ; it != cache.end() ; it++) {
            if (it->second >= 2) ret.push_back(it->first);
        }
        return ret;
    }
};
