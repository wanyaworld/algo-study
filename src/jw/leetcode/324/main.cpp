class Solution {
public:
    void wiggleSort(vector<int>& nums) {
        vector<int> tmp(nums);
        std::sort(tmp.begin(), tmp.end());
        
        int i, j{};
        if (nums.size() % 2 == 0) {
            for (i = 0 ; i < nums.size() / 2 ; i++) {
                nums[j++] = tmp[-i + nums.size() / 2 - 1];
                nums[j++] = tmp[nums.size() - 1 - i];
            }
        }
        else{
            int n = nums.size() - 1;
            nums[0] = tmp[tmp.size() / 2];
            for (i = 0 ; i < n / 2 ; i++) {
                nums[j++ + 1] = tmp[n - 1 - i + 1];
                nums[j++ + 1] = tmp[-i + n / 2 - 1 ];
                
            }
        }
    }
};
