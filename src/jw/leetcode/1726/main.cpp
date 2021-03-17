class Solution {
public:
    int p(int a, int b) {
        int ret = 1;
        for (int i = 0 ; i < b ; i++) {
            ret *= (a - i);
        }
        return ret;
    }
    int tupleSameProduct(vector<int>& nums) {
        int ret{};
        int n = nums.size();
        unordered_map<int, int> dict{};
        for (int i = 0 ; i <= n - 2 ; i++) {
            for (int j = i + 1 ; j <= n - 1 ; j++) {
                int prod = nums[i] * nums[j];
                if (dict.find(prod) == dict.end()) dict[prod] = 1;
                else dict[prod]++;
            }
        }
        for (auto it = dict.begin() ; it != dict.end() ; it++) {
            if (it->second > 1) ret += p(it->second, 2) * 4;
        }
        return ret;
    }
};
