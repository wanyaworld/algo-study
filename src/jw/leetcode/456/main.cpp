class Solution {
public:
    bool find132pattern(vector<int>& nums) {
        int n = nums.size();
        int min = nums[0];
        
        for (int i = 1 ; i < n - 1 ; i++) {
            for (int j = i + 1 ; j < n ; j++) {
                if (nums[i] > nums[j] && min < nums[j]) return true;
            }
            if (nums[i] < min) min = nums[i];
        }
        return false;
    }
};
