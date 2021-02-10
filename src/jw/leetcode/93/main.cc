class Solution {
public:
    vector<string> ret{};
    string parts[4];
    void dfs(string s, int idx, int slot) {
        if (idx > s.size() || slot > 4) return;
        if (slot == 4) {
            if (idx <= s.size() - 1) return;
            string cand{};
            for (int i = 0 ; i < 4 ; i++)
                cand += parts[i] + '.';
            cand.pop_back();
            ret.push_back(cand);
            return;
        }

        /* consume 0, 1, 2, 3 digit(s) here */
        for (int i = 0 ; i < 3 ; i++) {
            if (s.begin() + idx + i > s.end()) break;
            string tmp = string(s.begin() + idx, s.begin() + idx + i + 1);
            int dec;
            if ((dec = atoi(tmp.c_str())) > 255) continue;
            if (to_string(dec) != tmp) continue;
            parts[slot] = tmp;
            dfs(s, idx + i + 1, slot + 1);
        }
    }
    vector<string> restoreIpAddresses(string s) {
        dfs(s, 0, 0);
        return ret;
    }
};
