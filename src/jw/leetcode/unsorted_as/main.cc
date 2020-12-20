#include <vector>
#include <iostream>

using namespace std;

class Solution {
	public:
		int findLoc(vector<int>& nums, int target, int s, int e) {
			for (int i = s ; i <= e ; i++) {
				if (target <= nums[i]) return i;
			}
			return e + 1;
		}
		void dfs(vector<int>& nums, int idx, int& s, int &e, int &min, bool& flag) {
			if (idx >= (int)nums.size() - 1) {
				flag = false;
				return ;
			}
			dfs(nums, idx + 1, s, e, min, flag);
			if(!flag) {
				if (nums[idx] <= nums[idx + 1]) return;
				e = findLoc(nums, nums[idx], idx + 1, nums.size() - 1);
				e--;
				s = idx;
				min = nums[idx + 1];
				flag = true;
				return;
			}
			if (idx + 1 == s) {
				if (nums[idx] <= min) {
					min = nums[idx];
					return ;
				}
				s = idx;
				int i;
				if (e == nums.size() - 1) return;
				for (i = e + 1 ; i <= nums.size() - 1 ; i++) {
					if (nums[i] >= idx) break;
				}
				e = i;
				return;
			}
			else {
				if (nums[idx] <= nums[idx + 1]) {
					return ;
				}
				s = idx;
				min = nums[idx + 1];
			}
		}
		int findUnsortedSubarray(vector<int>& nums) {
			int s, e, min;
			bool flag;
			dfs(nums, 0, s, e, min, flag);
			if (flag)
				return (e - s + 1);
			return 0;
		}
};

int main() {
	Solution sl;
	vector<int> vec = {5,4,3,2,1};
	cout << sl.findUnsortedSubarray(vec) << endl;
	return 0;
}
