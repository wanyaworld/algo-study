class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        int n = s.size();
        int i{}, j{}, ret{};
        unordered_map<char, bool> dict{};
        
        while (i <= n - 1 && j <= n - 1) {
            if (dict.find(s[j]) == dict.end()) {
                dict[s[j++]] = true;
                if (dict.size() > ret) {
                    ret = dict.size();
                }
            }
            else {
                dict.erase(s[i++]);
            }
        }
        return ret;
    }
};
