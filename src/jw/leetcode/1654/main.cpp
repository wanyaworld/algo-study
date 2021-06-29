class Solution {
public:
    int visited[2][2000001];
    
    unordered_map<int, int> forb{};
    
    int thr = 10000000;
    int dfs(vector<int>& forbidden, int a, int b, int x, int cur, bool prv_was_back) {
        if (cur == x) return 0;
        if (cur > 100000 || cur < 0) return thr;
        if (forb.find(cur) != forb.end()) return thr;
        if (visited[(int)prv_was_back][cur]) return thr;
        visited[(int)prv_was_back][cur] = 1;
        if (prv_was_back) return dfs(forbidden, a, b, x, cur + a, false) + 1;
        return min(dfs(forbidden, a, b, x, cur + a, false), 
                   dfs(forbidden, a, b, x, cur - b, true)) + 1;
    }
    int minimumJumps(vector<int>& forbidden, int a, int b, int x) {
        for (auto it = forbidden.begin() ; it != forbidden.end() ; it++) {
            forb[*it] = 1;
        }
        auto ret = dfs(forbidden, a, b, x, 0, false);
        if (ret >= thr) return -1;
        return ret;
    }
};
