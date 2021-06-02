class Solution {
public:
    int max(int a, int b) {
        if (a > b) return a;
        return b;
    }
    int min(int a, int b) {
        if (a < b) return a;
        return b;
    }
    vector<vector<int>> merge(vector<vector<int>>& intervals) {
        list<vector<int>> l(intervals.begin(), intervals.end());
        retry:
        while (1) {
        for (auto it = l.begin() ; next(it) != l.end() ; it++) {
            for (auto jt = next(it) ; jt != l.end() ; jt++) {
                
                int x1 = (*it)[0];
                int y1 = (*it)[1];
                int x2 = (*jt)[0];
                int y2 = (*jt)[1];
                
                if (x1 <= y2 && x2 <= y1) {
                    int tmp0 = min(x1, x2);
                    int tmp1 = max(y1, y2);
                    
                    (*it)[0] = tmp0;
                    (*it)[1] = tmp1;
                    
                    l.erase(jt);
                    goto retry;
                }
                
            }
        }
        break;
        }
        vector<vector<int>> ret(l.begin(), l.end());
        return ret;
    }
};
