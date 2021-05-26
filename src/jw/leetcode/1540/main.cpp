class Solution {
public:
    int n_alph = 'z' - 'a' + 1;

    vector<int> getDiffs(string s, string t, int k) {
        vector<int> ret{};
        for (int i = 0 ; i < s.size() ; i++) {
            int diff = t[i] - s[i];
            if (diff < 0)
                diff = n_alph + diff;
            ret.push_back(diff);
        }
        return ret;
    }


    bool canConvertString(string s, string t, int k) {
        if (s.size() != t.size()) return false;

        vector<int> diffs = getDiffs(s, t, k);
        vector<int> moves(n_alph);
        for (int i = 0 ; i < n_alph ; i++) {
            moves[i] = k / n_alph;
            if (i < k % n_alph)
                moves[i]++;
        }
        for (auto it = diffs.begin() ; it != diffs.end() ; it++){
            if (*it == 0) continue;
            if (--moves[*it - 1] < 0)
              return false;
        }

        return true;
    }
};
