class Solution {
public:
    bool canJump(vector<int>& nums) {
        int n = nums.size();
        int steps = nums[0];
        int cur = 0;
        
        while (steps && cur < n - 1) {
            cur++;
            if (steps - 1 > nums[cur]) steps = steps - 1;
            else steps = nums[cur];
        }
        return cur == n - 1;
    }
};
