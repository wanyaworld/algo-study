class Solution {
public:
    struct int_lexio_compare {
        bool operator() (const int& l, const int& r) const {
            string left = to_string(l) + to_string(r);
            string right = to_string(r) + to_string(l);
            
            return left > right;
        }
    };
    string largestNumber(vector<int>& nums) {
        int max = -1;
        for (auto it = nums.begin() ; it != nums.end() ; it++) {
            if (*it > max) max = *it;
        }
        if (max == 0) return (string)"0";
        
        string ret ="";
        
        sort(nums.begin(), nums.end(), int_lexio_compare());
        
        for (auto it = nums.begin() ; it != nums.end() ; it++)
            ret += to_string(*it);
        
        return ret;
    }
};
