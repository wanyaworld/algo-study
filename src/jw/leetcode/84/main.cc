#include <vector>
using namespace std;

class Solution {
public:
    int n;
    int min(int a, int b) {
        if (a < b) return a;
        return b;
    }
    int max(int a, int b) {
        if (a > b) return a;
        return b;
    }
    int dfs(vector<int>& vec, int s, int e) {
        if (s >= e) return vec[s];
        int mid = (s + e) / 2;
        int l_max = dfs(vec, s, mid);
        int r_max = dfs(vec, mid + 1, e);
        int ret = max(l_max, r_max);
        
        int i = mid, j = mid, min_h = vec[mid];
        
        while (i > s && j < e) {
            if (vec[i - 1] > vec[j + 1]) {
                if (vec[i - 1] < min_h) min_h = vec[i - 1];
                int cur = (j - (i - 1) + 1) * min_h;
                if (cur > ret) ret = cur;
                i--;
            }
            else {
                if (vec[j + 1] < min_h) min_h = vec[j + 1];
                int cur = (j + 1 - (i) + 1) * min_h;
                if (cur > ret) ret = cur;
                j++;
            }
        }
        
        while (i > s) {
            if (vec[i - 1] < min_h) min_h = vec[i - 1];
            int cur = (j - (i - 1) + 1) * min_h;
            if (cur > ret) ret = cur;
            i--;
        }
        
        while (j < e) {
            if (vec[j + 1] < min_h) min_h = vec[j + 1];
            int cur = (j + 1 - (i) + 1) * min_h;
            if (cur > ret) ret = cur;
            j++;
        }
        
        return ret;
    }
    int largestRectangleArea(vector<int>& heights) {
        n = heights.size();
        if (n <= 0) return 0;
        
        return dfs(heights, 0, n - 1);
    }
};

int main() {
	vector<int> input{4, 2, 0, 3, 2, 4, 3, 4};
	Solution sl;
	sl.largestRectangleArea(input);
	return 0;
}
